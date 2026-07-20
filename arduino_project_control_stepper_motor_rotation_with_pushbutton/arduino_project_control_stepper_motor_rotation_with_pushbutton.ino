#include<Stepper.h>
int stepsPerRevolutions = 2048;
Stepper myStepper(stepsPerRevolutions, 8, 10, 9, 11);

int buttonPin = 2;
int buttonVal;
int speed = 12;
int dt = 100;
int buttonOld = 0;
int state = 1;
void setup(){

  Serial.begin(9600);
  pinMode(buttonPin, INPUT);
  digitalWrite(buttonPin, HIGH);
  myStepper.setSpeed(speed);

}

void loop(){

  buttonVal = digitalRead(buttonPin);
  Serial.println(buttonVal);
  if(buttonVal != buttonOld){

    if(buttonVal == LOW){
      state = -state;
    }
    
    delay(dt);

  }
  myStepper.step(state);
  buttonOld = buttonVal;


}