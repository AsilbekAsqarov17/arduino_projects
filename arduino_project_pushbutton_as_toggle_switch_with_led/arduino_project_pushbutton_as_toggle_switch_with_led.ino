int ledPin =8;
int buttonPin = 12;
int val=0;
int old_val=0;
int state = 0;
void setup() {

  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);

}

void loop() {

  val=digitalRead(buttonPin);
  Serial.println(val);
  if(val != old_val){

    if(val == LOW){
    
      if(!state){
      digitalWrite(ledPin, HIGH);
      state = 1;
      }
    else{
      digitalWrite(ledPin, LOW);
      state = 0;
      }
    }
    delay(50);
  }
  old_val = val;

}
