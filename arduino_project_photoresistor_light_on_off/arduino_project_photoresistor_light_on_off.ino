int lightPin = A5;
int lightVal;
int greenLed = 8;
int redLed = 9;
int wt = 250;
void setup(){

  Serial.begin(9600);
  pinMode(lightPin, INPUT);
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);

}

void loop(){
  
  lightVal = analogRead(lightPin);
  Serial.println(lightVal);

  if(lightVal > 50){

    digitalWrite(redLed, LOW);
    digitalWrite(greenLed, HIGH);

  }
  else{

    digitalWrite(greenLed, LOW);
    digitalWrite(redLed, HIGH);
    
  }

  delay(wt);

}