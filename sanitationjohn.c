#include <Stepper.h>

const int stepsPerRevolution = 600;
Stepper myStepper = Stepper(stepsPerRevolution, 8, 9, 10, 11); // stepper init on pins 8-11

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
int sprayPin = 5;
int lightsPin= 6;
int stateToggle = 7;
int onButton = 8;
int trigPin = 12;
int echoPin = 13;

double duration, cm, prev_cm;

// called to change the state
// add variables to declaration if they are needed in the function
void updateState(State nextState);

void setup() {
  previousState = EMPTY;
  currentState = EMPTY;
  prev_cm = 150;

  myStepper.setSpeed(120); // set motor RPM
  
  // pin init
  pinMode(statusLED, OUTPUT);
  pinMode(sprayPin, OUTPUT);
  pinMode(lightsPin, OUTPUT);
  pinMode(stateToggle, INPUT_PULLUP);
  pinMode(onButton, INPUT_PULLUP);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.begin(9600);

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
    delay(500);
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
    myStepper.step(600);
    
    // delay(200);

    if (!digitalRead(onButton)) // override
    {
      updateState(EMPTY);
    } else 
    {
      updateState(RESET);
    }

    if (!digitalRead(stateToggle)) 
    {
      delay(150);
      updateState(RESET); // call when we reach endpoint
    }
  
  } else if (currentState == RESET) 
  {
    // move back to start along rail
    myStepper.step(-600);

    // delay(200);

    if (!digitalRead(onButton)) // override
    {
      updateState(EMPTY);
    } else 
    {
      updateState(WAITING);
    }
    
    if (!digitalRead(stateToggle)) 
    {
      delay(150);
      updateState(WAITING); // call when we reach start point
    }

  } else if (currentState == EMPTY) 
  {
    if (!digitalRead(onButton)) 
    {
      updateState(WAITING); // call when ON button pressed
      delay(500);
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

    digitalWrite(lightsPin, LOW); // reset lights
    digitalWrite(sprayPin, LOW); // disable spray bottle
    
  } else if (nextState == READY) 
  {
    Serial.println("Transitioning to state READY");

  } else if (nextState == CLEANING) 
  {
    Serial.println("Transitioning to state CLEANING");

    digitalWrite(lightsPin, HIGH); // enable lights
    digitalWrite(sprayPin, HIGH); // toggle/actuate spray bottle continuously

  } else if (nextState == RESET) 
  {
    Serial.println("Transitioning to state RESET");

    digitalWrite(sprayPin, LOW); // disable spray bottle

  } else if (nextState == EMPTY) 
  {
    Serial.println("Transitioning to state EMPTY");

    // disable everything
    digitalWrite(sprayPin, LOW); // disable spray bottle
    digitalWrite(lightsPin, LOW); // disable lights
    digitalWrite(trigPin, LOW); // disable ultrasonic sensor
    
  } else // something went wrong if here
  {
    previousState = currentState;
    currentState = EMPTY; // force empty state

    Serial.print("Error: Unknown state encountered when transitioning from state ");
    Serial.println(previousState, DEC);
  }
}
