int buzzPin = 8;
int potPin = A5;
int potVal;
int buzzTime;

void setup() {

  Serial.begin(9600);
  pinMode(buzzPin, OUTPUT);
  pinMode(potPin, INPUT);
}

void loop() {

  potVal = analogRead(potPin);
  Serial.println(potVal);

  buzzTime = (9940. / 1023.) * potVal + 60;

  digitalWrite(buzzPin, HIGH);
  delayMicroseconds(buzzTime);
  digitalWrite(buzzPin, LOW);
  delayMicroseconds(buzzTime);
}