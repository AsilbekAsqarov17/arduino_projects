int button1 = 7;
int button2 = 6;
int bVal1 = 0;
int bVal2 = 0;
int ledPin = 9;
int state = 0;
int wt = 250;


void setup(){

  Serial.begin(9600);
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(ledPin, OUTPUT);

}

void loop(){

  bVal1 = digitalRead(button1);
  bVal2 = digitalRead(button2);

  Serial.print(bVal1);
  Serial.print("       ");
  Serial.print(bVal2);
  Serial.print("       ");
  Serial.println(state);

  if(bVal1 == 0 && state < 255){
    state += 15;
    if(state > 255) state = 255;
    analogWrite(ledPin, state);

  }
  
  if(bVal2 == 0 && state > 0){
    state -= 15;
    if(state < 0) state = 0;
    analogWrite(ledPin, state);
  }

  delay(wt);

}