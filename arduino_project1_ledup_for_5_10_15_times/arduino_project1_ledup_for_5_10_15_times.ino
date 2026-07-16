void setup(){

pinMode(8, OUTPUT);

pinMode(9, OUTPUT);

pinMode(10, OUTPUT);


}

void loop(){

  for(int i = 0; i < 5; i++){
    digitalWrite(8,HIGH);
    delay(500);

    digitalWrite(8,LOW);
    delay(500);
  }

  for(int i = 0; i < 10; i++){
    digitalWrite(9,HIGH);
    delay(500);

    digitalWrite(9,LOW);
    delay(500);
  }

  for(int i = 0; i < 15; i++){
    digitalWrite(10,HIGH);
    delay(500);

    digitalWrite(10,LOW);
    delay(500);
  }

}