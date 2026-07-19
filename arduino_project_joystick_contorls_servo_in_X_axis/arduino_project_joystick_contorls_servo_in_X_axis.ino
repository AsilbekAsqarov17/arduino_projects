#include<Servo.h>
Servo servo;
int xPin = A0;
int yPin = A1;
int switchPin = 2;
int xVal;
int yVal;
int switchVal;
int servoPin = 10;
int xAngle = 0;
int dt = 250;

void setup() {

  Serial.begin(9600);
  pinMode(xPin,INPUT);
  pinMode(yPin,INPUT);
  pinMode(switchPin,INPUT);
  digitalWrite(switchPin, HIGH);
  servo.attach(servoPin);  

}

void loop() {

  xVal = analogRead(xPin);
  yVal = analogRead(yPin);
  switchVal = digitalRead(switchPin);
  Serial.print("X = ");
  Serial.print(xVal);
  Serial.print("Y = ");
  Serial.print(yVal);
  Serial.print("Switch = ");
  Serial.print(switchVal);

  xAngle = (180. / 1023.) * xVal;
  Serial.print("Angle: ");
  Serial.println(xAngle);
  servo.write(xAngle);

  delay(dt);


}