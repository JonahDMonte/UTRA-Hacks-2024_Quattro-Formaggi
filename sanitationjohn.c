typedef enum State {WAITING = 0, READY = 1, CLEANING = 2, RESET = 3, EMPTY = 4};
// WAITING - nothing is happenening, default state until sensor triggers
// READY - object/action detected, waiting for something before commencing cleaning (ex: hand leaves detection range
// CLEANING - disable sensors, trigger rail to move until detected at end point, spray bottle along way, toggle lights, etc...
// RESET - trigger rail to return to starting position, disable lights, bottle, etc..., enable sensors
// EMPTY - pseudo-null state, in case needed
// Should be rather one way: WAITING -> READY -> CLEANING -> RESET -> WAITING (...)


/* Robot features/sensors and when they are active:
  - "UV" Lights (CLEANING)
  - Spray Bottle with motors (CLEANING)
  - Rail movement based on set rotation amount (CLEANING and RESET)
  - 
  - Accelerometer available if needed
*/

State currentState;
State previousState; // might not be needed

int statusLED = 4;
int stateToggle = 7;
int onButton = 8;
int trigPin = 11;    // Trigger
int echoPin = 12;    // Echo

double duration, cm, prev_cm;

// called to change the state
// add variables to declaration if they are needed in the function
void updateState(State nextState);

void setup() {
  previousState = EMPTY;
  currentState = EMPTY;
  prev_cm = 150;

  Serial.begin(9600);
  
  // other init
  pinMode(stateToggle, INPUT_PULLUP);
  pinMode(onButton, INPUT_PULLUP);
  pinMode(statusLED, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  updateState(EMPTY); // enter FSM
}

// for constant code execution WHILE IN STATE
void loop() {

  if (currentState == EMPTY) 
  {
    digitalWrite(statusLED, LOW);
  } else 
  {
    digitalWrite(statusLED, HIGH);
  }

  if ((currentState != EMPTY) && (!digitalRead(onButton))) 
  {
    updateState(EMPTY);
    delay(300);
  }

  if (currentState == WAITING)
  {
    // ultrasonic sensor detection
    digitalWrite(trigPin, LOW);
    delayMicroseconds(5);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    duration = pulseIn(echoPin, HIGH);
    cm = ((double)duration/2.0) / 29.1;

    if (cm > 200) // error correction
    {
      cm = prev_cm;
    }  else 
    {
      prev_cm = cm;
    }

    // Serial.println(cm);
    
    // wait for sensor detection
    if ((cm < 30.0) || (!digitalRead(stateToggle))) 
    {
      updateState(READY); // call when sensor triggers
    }

    delay(150);

  } else if (currentState == READY) 
  {
    // ultrasonic sensor detection
    digitalWrite(trigPin, LOW);
    delayMicroseconds(5);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    duration = pulseIn(echoPin, HIGH);
    cm = ((double)duration/2.0) / 29.1;

    if (cm > 200) // error correction
    {
      cm = prev_cm;
    }  else 
    {
      prev_cm = cm;
    }

    // Serial.println(cm);
    
    // wait for some condition to trigger cleaning, maybe a timeout time, or another sensor detection
    if ((cm > 30.0) || (!digitalRead(stateToggle))) 
    {
      updateState(CLEANING); // call when condition met
    }

    delay(150);

  } else if (currentState == CLEANING) 
  {
    // move along rail until endpoint
    // toggle/actuate spray bottle continuously
    while (!digitalRead(stateToggle)) 
    {
      delay(300);
      updateState(RESET); // call when we reach endpoint    
    }
  

  } else if (currentState == RESET) 
  {
    // move along rail until start point
    while (!digitalRead(stateToggle)) 
    {
      delay(300);
      updateState(WAITING); // call when we reach start point
    }

  } else if (currentState == EMPTY) 
  {
    if (!digitalRead(onButton)) 
    {
      delay(300);
      updateState(WAITING); // call when ON button pressed
    }
  }

}

// for one time code execution ON STATE CHANGE
void updateState(State nextState) {
  previousState = currentState;
  currentState = nextState;
  
  if (nextState == WAITING) 
  {
    Serial.println("Transitioning to state WAITING");
    
    // maybe enable sensors or init them
  } else if (nextState == READY) 
  {
    Serial.println("Transitioning to state READY");

    // maybe init timeout timer
  } else if (nextState == CLEANING) 
  {
    Serial.println("Transitioning to state CLEANING");

    // maybe disable other sensors
    // turn on lights
  } else if (nextState == RESET) 
  {
    Serial.println("Transitioning to state RESET");

    // disable lights
  } else if (nextState == EMPTY) 
  {
    Serial.println("Transitioning to state EMPTY");
    
    // used if needed
  } else // something went wrong if here
  {
    previousState = currentState;
    currentState = EMPTY; // force empty state

    Serial.print("Error: Unknown state encountered when transitioning from state ");
    Serial.println(previousState, DEC);
  }
}
