int button1Pin = 9;
int button2Pin = 8;
int button1Val;
int button2Val;
int enablePin = 5;
int input1Pin = 4;
int input2Pin = 3;
int speed = 0;
int stepSize = 15;
int dt = 250;

void setup(){

  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);

  digitalWrite(button1Pin, HIGH);
  digitalWrite(button2Pin, HIGH);
  
  Serial.begin(9600);
  
  pinMode(enablePin, OUTPUT);
  pinMode(input1Pin, OUTPUT);
  pinMode(input2Pin, OUTPUT);

}

void loop(){

  button1Val = digitalRead(button1Pin);
  button2Val = digitalRead(button2Pin);
  Serial.print("Button 1: ");
  Serial.print(button1Val);
  Serial.print("   Button 2: ");
  Serial.print(button2Val);
  
  bool wasStopped = (speed == 0);

  if( button1Val == 0 && button2Val == 0){
  	
  }
  else if(button1Val == 0 && button2Val == 1){
    
    if(speed <= (255 - stepSize)){
      speed += stepSize;
      
      if(wasStopped) {
        digitalWrite(input1Pin, HIGH);
        digitalWrite(input2Pin, LOW);
        analogWrite(enablePin, 255);
        delay(200); 
      }

    }
    
  }
  else if(button1Val == 1 && button2Val == 0){
    if(speed >= -(255 - stepSize)){
      speed -= stepSize;
      
      if(wasStopped) {
        digitalWrite(input1Pin, LOW);
        digitalWrite(input2Pin, HIGH);
        analogWrite(enablePin, 255);
        delay(200);
      }

    }
  }
  
  
  if(speed == 0){

  	analogWrite(enablePin, speed);
    digitalWrite(input1Pin, LOW);
    digitalWrite(input2Pin, LOW);
    Serial.print("   Not Spinning!!!");

  }
  else if(speed > 0){
    
  	analogWrite(enablePin, speed);
    digitalWrite(input1Pin, HIGH);
    digitalWrite(input2Pin, LOW);
    Serial.print("   Forward!");

  }
  else if(speed < 0){

    analogWrite(enablePin, abs(speed));
    digitalWrite(input1Pin, LOW);
    digitalWrite(input2Pin, HIGH);
    Serial.print("   Reverse!");

  }

  Serial.print("   ");
  Serial.println(speed);
  
  delay(dt);
}