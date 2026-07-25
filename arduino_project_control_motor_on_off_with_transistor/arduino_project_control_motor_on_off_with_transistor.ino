const int motorPin = 9; 

void setup() {
  pinMode(motorPin, OUTPUT);
}

void loop() {
  digitalWrite(motorPin, HIGH); 
  delay(2000);                 
  
  digitalWrite(motorPin, LOW);
  delay(2000);                  

}