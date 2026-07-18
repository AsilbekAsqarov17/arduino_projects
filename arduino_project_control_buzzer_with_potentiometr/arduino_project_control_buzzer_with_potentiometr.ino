int potPin = A5;
int potVal;
int buzzPin = 8;
int wt = 2000;

void setup(){

 Serial.begin(9600);
 pinMode(potPin, INPUT);
 pinMode(buzzPin, OUTPUT);

}

void loop(){

  potVal = analogRead(potPin);
  Serial.println(potVal);
  if(potVal >= 1000){
    digitalWrite(buzzPin, HIGH);
    delay(wt);
  }
  else{
    digitalWrite(buzzPin, LOW);
  }
  delay(wt);

}