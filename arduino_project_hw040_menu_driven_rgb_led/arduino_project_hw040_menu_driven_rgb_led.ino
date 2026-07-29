#include <LiquidCrystal.h>

// HW-040 pins
int sw = 13;
int dt = 12;
int clk = 8;

int laststate;
int currentstate;
int position = 0;
int lastposition = -1;

// LCD pins (RS, E, D4, D5, D6, D7)
int rs = 7;
int e = 6;
int d4 = 5;
int d5 = 4;
int d6 = 3;
int d7 = 2;

LiquidCrystal lcd(rs, e, d4, d5, d6, d7);

// RGB LED pins
int redPin = 11;
int greenPin = 10;
int bluePin = 9;

int brightness = 255;
int selectedColor = 0;
const String menu[4] = {"Red", "Green", "Blue", "Brightness"};

void setColor(int red, int green, int blue);
void updateLED();

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);

  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  pinMode(sw, INPUT_PULLUP);
  pinMode(dt, INPUT);
  pinMode(clk, INPUT);

  laststate = digitalRead(clk);

  lcd.setCursor(0, 0);
  lcd.print("Menu-driven RGB");
  delay(2000);
  lcd.clear();

  updateLED();
}

void loop() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Menu: ");
  lastposition = -1;

  while (digitalRead(sw) == HIGH) {
    currentstate = digitalRead(clk);

    if (currentstate != laststate && currentstate == LOW) {
      if (digitalRead(dt) != currentstate) {
        position++;
      } else {
        position--;
      }
      delay(5); 
    }

    if (position > 3) position = 0;
    if (position < 0) position = 3;

    laststate = currentstate;

    if (position != lastposition) {
      lcd.setCursor(0, 1);
      lcd.print(menu[position]);
      lcd.print("      "); 
      lastposition = position;  
    }
  }

  delay(200);
  while (digitalRead(sw) == LOW) delay(10);

  if (position == 3) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Set Brightness:");
    
    int lastBrightness = -1;

    while (digitalRead(sw) == HIGH) {
      currentstate = digitalRead(clk);

      if (currentstate != laststate && currentstate == LOW) {
        if (digitalRead(dt) != currentstate) {
          brightness += 15;
        } else {
          brightness -= 15;
        }
        delay(5); 
      }

      if (brightness > 255) brightness = 255;
      if (brightness < 0)   brightness = 0;

      laststate = currentstate;

      if (brightness != lastBrightness) {
        lcd.setCursor(0, 1);
        lcd.print("Level: ");
        lcd.print(brightness);
        lcd.print(" / 255   ");
        lastBrightness = brightness;
        updateLED(); 
      }
    }

    delay(200);
    while (digitalRead(sw) == LOW) delay(10);

  } else {
    selectedColor = position;
    updateLED();

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Color Set To:");
    lcd.setCursor(0, 1);
    lcd.print(menu[selectedColor]);
    delay(1500);
  }
}

void updateLED() {
  if (selectedColor == 0)      setColor(brightness, 0, 0);   // Red
  else if (selectedColor == 1) setColor(0, brightness, 0);   // Green
  else if (selectedColor == 2) setColor(0, 0, brightness);   // Blue
}

void setColor(int red, int green, int blue) {
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}