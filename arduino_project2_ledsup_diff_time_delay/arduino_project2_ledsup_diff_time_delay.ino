int redLED = 8;
int red_led_dit = 50;

int greenLED = 9;
int green_led_dit = 250;

int blueLED = 10;
int blue_led_dit = 500;

int long_delay = 2000; 

void setup(){

pinMode(redLED, OUTPUT);
pinMode(greenLED, OUTPUT);
pinMode(blueLED, OUTPUT);

}

void loop(){

for(int i = 0; i < 5; i++){
  digitalWrite(redLED,HIGH);
  delay(red_led_dit);
  digitalWrite(redLED,LOW);
  delay(red_led_dit);
}

for(int i = 0; i < 5; i++){
  digitalWrite(greenLED,HIGH);
  delay(green_led_dit);
  digitalWrite(greenLED,LOW);
  delay(green_led_dit);
}

for(int i = 0; i < 5; i++){
  digitalWrite(blueLED,HIGH);
  delay(blue_led_dit);
  digitalWrite(blueLED,LOW);
  delay(blue_led_dit);
}

delay(long_delay);

}