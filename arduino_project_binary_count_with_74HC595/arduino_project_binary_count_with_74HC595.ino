int latchPin = 11;
int clockPin = 9;
int dataPin = 12;
byte count = 0x00;
int dt = 500;

void setup(){

  Serial.begin(9600);
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);

}



void loop(){

  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, count);
  digitalWrite(latchPin, HIGH);
  count++;
  delay(dt);

}