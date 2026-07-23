int triggerPin = 10;
int echoPin = 9;
float duration;
float distance;
float upperLimit = 30.0;
float lowerLimit = 2.0;
int dt = 200;
void setup() {

  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);

}

void loop() {

digitalWrite(triggerPin, LOW);
delayMicroseconds(10);
digitalWrite(triggerPin, HIGH);
delayMicroseconds(10);
digitalWrite(triggerPin, LOW);

duration = pulseIn(echoPin, HIGH);
distance = duration * 0.034 / 2;

Serial.print(distance);
Serial.print(",");
Serial.print(upperLimit);
Serial.print(",");
Serial.println(lowerLimit);

delay(dt);

}
