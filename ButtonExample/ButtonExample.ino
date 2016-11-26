#include <FiniteStateMachine.h>
#include <Button.h>                                        
#include <LED.h>
 
const byte NUMBER_OF_PRESS_STATES = 5;
const byte NUMBER_OF_HOLD_STATES = 2;
const int FADE_TIME = 500;
 
Button button = Button(12);
LED led1 = LED(13);
LED led2 = LED(2);
byte buttonPresses = 0;
byte buttonHolds = 0;

//utility functions
void led1On() {
  led1.on();
}

void led2On() {
  led2.on();
}

void led1Off() {
  led1.off();
}

void led2Off() {
  led2.off();
}

void fadeLed1In() {
  led1.fadeIn(FADE_TIME);
}

void fadeLed2In() {
  led2.fadeIn(FADE_TIME);
}

void fadeLed1Out() {
  led1.fadeOut(FADE_TIME);
}

void fadeLed2Out() {
  led2.fadeOut(FADE_TIME);
}

void allOff() {
  led1Off();
  led2Off();
}

void allOn() {
  led1On();
  led2On();
}

void fadeAllIn() {
  fadeLed1In();
  fadeLed2In();
}

void fadeAllOut() {
  fadeLed1Out();
  fadeLed2Out();
}


//initialize states
State led1OnState = State(led1On);
State led2OnState = State(led2On);
State allOffState = State(allOff);
State allOnState = State(allOn);
State fadeAllInState = State(fadeAllIn);
State fadeAllOutState = State(fadeAllOut);


FSM buttonPressStateMachine = FSM(allOffState);
FSM buttonHoldStateMachine = FSM(allOffState);
 
void setup(){
  button.pressHandler(onPress);
  button.clickHandler(onClick);
  button.releaseHandler(onRelease);
  button.holdHandler(onHold);
  led1.off();
  led2.off();
}
 
//poor example, but then again; it's just an example
void loop(){
  button.read();
}

void onClick(Button &btn) {
  Serial.println("clicked");
  
  //increment buttonPresses and constrain it to [ 0, 1, 2, 3 ]
  buttonPresses = ++buttonPresses % NUMBER_OF_PRESS_STATES;
  switch (buttonPresses){
    case 0: buttonPressStateMachine.transitionTo(led1OnState); break;
    case 1: buttonPressStateMachine.transitionTo(led2OnState); break;
    case 2: buttonPressStateMachine.transitionTo(allOffState); break;
    case 3: buttonPressStateMachine.transitionTo(fadeAllInState); break;
    case 4: buttonPressStateMachine.transitionTo(fadeAllOutState); break;
  }

  buttonPressStateMachine.update();
}

void onHold(Button &btn) {
  Serial.println("held");

  buttonHolds = ++buttonHolds % NUMBER_OF_HOLD_STATES;
  switch (buttonHolds){
    case 0: buttonHoldStateMachine.transitionTo(allOnState); break;
    case 1: buttonHoldStateMachine.transitionTo(allOffState); break;
  }

  buttonHoldStateMachine.update();
}

void onRelease(Button &btn) {
  Serial.println("released");
}

void onPress(Button &btn) {
  Serial.println("pressed");
}

