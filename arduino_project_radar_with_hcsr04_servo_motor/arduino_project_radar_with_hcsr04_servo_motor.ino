#include <Servo.h>

#define trigPin 10
#define echoPin 11
#define servoPin 12  // Changed from 11 to avoid pin conflict with echoPin

long duration;
int distance;

Servo myservo;

int calculateDistance()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // 30000 µs (30ms) timeout prevents pulseIn from hanging if no echo returns
  duration = pulseIn(echoPin, HIGH, 30000); 
  distance = duration * 0.034 / 2;
  return distance;
}

void setup()
{
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  myservo.attach(servoPin); // Connected to Pin 12
  Serial.begin(9600);
}

void loop()
{
  int i;
  
  // Sweep forward: 15 to 165 degrees
  for (i = 15; i <= 165; i++)
  {
    myservo.write(i);
    delay(30); // 30ms gives the motor enough time to physical reach each angle
    calculateDistance();
    Serial.print(i);
    Serial.print(",");
    Serial.print(distance);
    Serial.print(".");
  }
  
  // Sweep backward: 165 down to 15 degrees
  for (i = 165; i >= 15; i--)
  {
    myservo.write(i);
    delay(30);
    calculateDistance();
    Serial.print(i);
    Serial.print(",");
    Serial.print(distance);
    Serial.print(".");
  }
}