#include<Servo.h>
int servoPin = 9;
int servoPos;
Servo myServo;
int resPin = A5;
int resVal;
int dt =250;
void setup(){

  Serial.begin(9600);
  myServo.attach(servoPin);

}

void loop(){

  resVal = analogRead(resPin);
  Serial.println(resVal);

  if (resVal > 900) resVal = 900;
  if (resVal < 0)   resVal = 0;

  servoPos = (180. / 900.) * resVal;

  myServo.write(servoPos);
  delay(dt);

}
