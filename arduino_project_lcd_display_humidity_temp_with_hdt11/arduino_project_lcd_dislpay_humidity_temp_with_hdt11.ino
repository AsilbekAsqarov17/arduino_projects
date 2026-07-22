#include<LiquidCrystal.h>
#include<DHT.h>
#define Type DHT11
int rs = 7;
int e = 8;
int d4 = 9;
int d5 = 10;
int d6 = 11;
int d7 = 12;
LiquidCrystal lcd(rs, e, d4, d5, d6, d7);

int sensePin = 2;
DHT ht(sensePin, Type);

float humidity;
float tempC;
float tempF;
int dt = 2000;

void setup(){

  Serial.begin(9600);
  lcd.begin(16, 2);
  ht.begin();
  delay(dt);

}

void loop(){

  humidity = ht.readHumidity();
  tempC = ht.readTemperature();

  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Humidity: ");
  lcd.print(int(humidity));
  lcd.print("%");

  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  lcd.print(int(tempC));
  lcd.print(" C");
  
  delay(dt);

}