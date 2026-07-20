int enablePin = 5;
int input1 = 4;
int input2 = 3;
int x = A0;
int xVal;
int y = A1;
int yVal;
int forward;
int reverse;
bool isMotorStopped = true;
void setup(){

  Serial.begin(9600);
  pinMode(y, INPUT);
  pinMode(x, INPUT);

  pinMode(enablePin, OUTPUT);
  pinMode(input1, OUTPUT);
  pinMode(input2, OUTPUT);

}

void loop(){

  yVal = analogRead(y);
  Serial.print(yVal);
  Serial.print("   ");
  
  
  if(yVal >=0 && yVal <=495){
    
  	digitalWrite(input1, HIGH);
    digitalWrite(input2, LOW);
    
    forward = (255. / -495.) * (yVal - 495);

    if(isMotorStopped){
      analogWrite(enablePin, 255);
      delay(100);
      isMotorStopped = false;
    }

    analogWrite(enablePin, forward);
    Serial.print("Forward: ");
    Serial.println(forward);
    
  }
  else if(yVal >=515 && yVal <=1023){
    
  	digitalWrite(input1, LOW);
    digitalWrite(input2, HIGH);
    
    reverse = (255. / 508.) * (yVal - 515);

    if(isMotorStopped){
      analogWrite(enablePin, 255);
      delay(100);
      isMotorStopped = false;
    }

    analogWrite(enablePin, reverse);
    Serial.print("Reverse: ");
    Serial.println(reverse);
    
  }
  else{
    analogWrite(enablePin, 0);
    digitalWrite(input1, LOW);
    digitalWrite(input2, LOW);
    isMotorStopped = true;
  	Serial.println("Not Working!!!");
  }

  delay(30);
  
}