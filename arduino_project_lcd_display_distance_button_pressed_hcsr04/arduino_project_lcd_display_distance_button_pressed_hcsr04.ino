#include<LiquidCrystal.h>
//lcd pins
int rs = 12;
int e = 11;
int d4 = 10;
int d5 = 9;
int d6 = 8;
int d7 = 7;
LiquidCrystal lcd(rs, e, d4, d5, d6, d7);

//hc-sr04 pins
int triggerPin = 5;
int echoPin = 4;

//pushbutton pin
int buttonPin = 2;
int buttonVal;

float duration;
float distance;
int dt = 5000;

void setup() {

  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);

}

void loop() {

  buttonVal = digitalRead(buttonPin);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Place the Target");
  lcd.setCursor(0, 1);
  lcd.print("Press to measure");

  while(buttonVal == 1){
    buttonVal = digitalRead(buttonPin);
  }

  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Target Distance:");
  lcd.setCursor(0, 1);
  lcd.print(distance);
  lcd.print(" sm");
  delay(dt);
  
}
