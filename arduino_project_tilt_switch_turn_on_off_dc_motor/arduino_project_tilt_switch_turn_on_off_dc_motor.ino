int tiltPin = 8;
int tiltVal;
int enablePin = 5;
int input1 = 4;
int input2 = 3;

void setup(){

  Serial.begin(9600);
  pinMode(tiltPin, INPUT);
  digitalWrite(tiltPin, HIGH);

}

void loop(){

  tiltVal = digitalRead(tiltPin);
  Serial.println(tiltVal);

  digitalWrite(input1, HIGH);
  digitalWrite(input2, LOW);  

  if(tiltVal == 0){
    analogWrite(enablePin, 255);
  }
  else{
    analogWrite(enablePin, 0);
  }
}