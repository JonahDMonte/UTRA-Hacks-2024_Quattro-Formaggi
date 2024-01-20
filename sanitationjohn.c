typedef enum State {WAITING = 0, READY = 1, CLEANING = 2, RESET = 3, EMPTY = 4};
// WAITING - nothing is happenening, default state until sensor triggers
// READY - object/action detected, waiting for something before commencing cleaning (ex: hand leaves detection range
// CLEANING - disable sensors, trigger rail to move until detected at end point, spray bottle along way, toggle lights, etc...
// RESET - trigger rail to return to starting position, disable lights, bottle, etc..., enable sensors
// EMPTY - pseudo-null state, in case needed
// Should be rather one way: WAITING -> READY -> CLEANING -> RESET -> WAITING (...)

State currentState;
State previousState; // might not be needed

int inPin = 7;

// called to change the state
// add variables to declaration if they are needed in the function
void updateState(State nextState);

void setup() {
  previousState = EMPTY;
  currentState = EMPTY;
  
  // other init
  pinMode(inPin, INPUT);

  updateState(WAITING); // enter FSM
}

// for constant code execution WHILE IN STATE
void loop() {
  
  if (currentState == WAITING)
  {
    // wait for sensor detection
    while (!digitalRead(inPin)) 
    {
      delay(100);
    }

    updateState(READY); // call when sensor triggers
  } else if (currentState == READY) 
  {
    // wait for some condition to trigger cleaning, maybe a timeout time, or another sensor detection
    while (!digitalRead(inPin)) 
    {
      delay(100);
    }

    updateState(CLEANING); // call when condition is met and we need to begin cleaning
  } else if (currentState == CLEANING) 
  {
    // move along rail until endpoint
    // toggle/actuate spray bottle continuously
    while (!digitalRead(inPin)) 
    {
      delay(100);
    }
  
    updateState(RESET); // call when we reach endpoint
  } else if (currentState == RESET) 
  {
    // move along rail until start point
    while (!digitalRead(inPin)) 
    {
      delay(100);
    }

    updateState(WAITING); // call when we reach start point
  } else if (currentState == EMPTY) 
  {
    // used if needed
  }

}

// for one time code execution ON STATE CHANGE
void updateState(State nextState) {
  previousState = currentState;
  currentState = nextState;
  
  if (nextState == WAITING) 
  {
    Serial.print("Transitioning to state ");
    Serial.println(nextState, DEC);
    
    // maybe enable sensors or init them
  } else if (nextState == READY) 
  {
    Serial.print("Transitioning to state ");
    Serial.println(nextState, DEC);

    // maybe init timeout timer
  } else if (nextState == CLEANING) 
  {
    Serial.print("Transitioning to state ");
    Serial.println(nextState, DEC);

    // maybe disable other sensors
    // turn on lights
  } else if (nextState == RESET) 
  {
    Serial.print("Transitioning to state ");
    Serial.println(nextState, DEC);

    // disable lights
  } else if (nextState == EMPTY) 
  {
    Serial.print("Transitioning to state ");
    Serial.println(nextState, DEC);
    
    // used if needed
  } else // something went wrong if here
  {
    previousState = currentState;
    currentState = EMPTY; // force empty state

    Serial.print("Error: Unknown state encountered when transitioning from state ");
    Serial.println(previousState, DEC);

  }
}
