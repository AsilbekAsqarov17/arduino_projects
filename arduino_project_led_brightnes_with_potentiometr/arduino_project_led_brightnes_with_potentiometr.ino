int potPin = A5;
int greenLed = 3;
int potVal = 0;
float ledVal;
int waitTime = 1000;

void setup() {

  Serial.begin(9600);
  pinMode(greenLed, OUTPUT);
  pinMode(potPin, INPUT);

}

void loop() {

  potVal = analogRead(potPin);
  ledVal = (255./1023.) * potVal;
  analogWrite(greenLed, ledVal);
  Serial.print("Pot Val:");
  Serial.print(potVal);
  Serial.print("   Led Val: ");
  Serial.println(ledVal);
  delay(waitTime);

}
