#include <Keypad.h>
#include <Servo.h>

Servo doorLock;
const int SERVO_PIN = 10;
const int LOCKED_POS = 0;
const int UNLOCKED_POS = 90;

const int LED_PIN = 13;

const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6}; 
byte colPins[COLS] = {5, 4, 3, 2}; 

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

const String CORRECT_PASSWORD = "1234";
String inputPassword = "";

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  doorLock.attach(SERVO_PIN);
  doorLock.write(LOCKED_POS);
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    if (key == '#') {
      checkPassword();
    } 
    else if (key == '*') {
      inputPassword = "";
      flashLED(2, 100);
    } 
    else {
      if (inputPassword.length() < 8) {
        inputPassword += key;
        flashLED(1, 50);
      }
    }
  }
}

void checkPassword() {
  if (inputPassword == CORRECT_PASSWORD) {
    doorLock.write(UNLOCKED_POS);
    digitalWrite(LED_PIN, HIGH);
    delay(3000);
    
    doorLock.write(LOCKED_POS);
    digitalWrite(LED_PIN, LOW);
  } else {
    flashLED(5, 80);
  }

  inputPassword = "";
}

void flashLED(int times, int speedMs) {
  for (int i = 0; i < times; i++) {
    digitalWrite(LED_PIN, HIGH);
    delay(speedMs);
    digitalWrite(LED_PIN, LOW);
    delay(speedMs);
  }
}