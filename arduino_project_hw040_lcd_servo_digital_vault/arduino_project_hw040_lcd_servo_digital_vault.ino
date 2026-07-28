#include <LiquidCrystal.h>
#include <Servo.h>

// LCD pins
int rs = 10;
int e = 9;
int d4 = 8;
int d5 = 7;
int d6 = 6;
int d7 = 5;
LiquidCrystal lcd(rs, e, d4, d5, d6, d7);

// Servo pin
Servo myservo;
int servoPin = 11;

// HW-040 pins
int sw = 4;
int dt = 3;
int clk = 2;

int laststate;
int currentstate;
int counter = 0;
int lastcounter = -1;

const int passcode[4] = {4, 7, 3, 5};
int enteredcode[4];

bool matching(const int passcode[], const int enteredcode[]);

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(sw, INPUT_PULLUP);
  pinMode(dt, INPUT);
  pinMode(clk, INPUT);

  myservo.attach(servoPin);
  myservo.write(0);

  laststate = digitalRead(clk);

  lcd.setCursor(0, 0);
  lcd.print("Digital Safe");
  delay(1500);
  lcd.clear();
}

void loop() {
  for (int i = 0; i < 4; i++) {
    counter = 0;
    lastcounter = -1;

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Digit ");
    lcd.print(i + 1);
    lcd.print("/4:");

    while (digitalRead(sw) == HIGH) {
      currentstate = digitalRead(clk);
      
      if (currentstate != laststate && currentstate == LOW) {
        if (digitalRead(dt) != currentstate) {
          counter++;
        } else {
          counter--;
        }
      }

      if (counter > 9) { counter = 0; }
      if (counter < 0) { counter = 9; }
      
      laststate = currentstate;

      if (counter != lastcounter) {
        lcd.setCursor(0, 1);
        lcd.print("Value: ");
        lcd.print(counter);
        lcd.print("   ");
        lastcounter = counter;
      }
    }

    enteredcode[i] = counter;
    delay(200);
    while (digitalRead(sw) == LOW) {
      delay(50);
    }
  }

  lcd.clear();
  if (matching(passcode, enteredcode)) {
    lcd.setCursor(0, 0);
    lcd.print("Access Granted!");
    myservo.write(90);
    delay(3000);
    myservo.write(0);
  } else {
    lcd.setCursor(0, 0);
    lcd.print("Wrong Password!");
    delay(2500);
  }
}

bool matching(const int passcode[], const int enteredcode[]) {
  for (int i = 0; i < 4; i++) {
    if (passcode[i] != enteredcode[i])
      return false;
  }
  return true;
}