#include <LiquidCrystal.h>
#include <IRremote.hpp>

// LCD pins
int rs = 12;
int e = 11;
int d4 = 10;
int d5 = 9;
int d6 = 8;
int d7 = 7;
LiquidCrystal lcd(rs, e, d4, d5, d6, d7);
 
// IR receive pin
int receiverPin = 6;

// L293D pins
int enablePin  = 5;
int input1Pin = 3;
int input2Pin = 2;

String speed = "OFF"; 

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  IrReceiver.begin(receiverPin, ENABLE_LED_FEEDBACK);
  
  pinMode(enablePin, OUTPUT);
  pinMode(input1Pin, OUTPUT);
  pinMode(input2Pin, OUTPUT);
  
  lcd.setCursor(0, 0);
  lcd.print("Fan: ");
  lcd.setCursor(0, 1);
  lcd.print(speed);
}

void loop() {
  if (IrReceiver.decode()) {

    if (IrReceiver.decodedIRData.command == 0x45) {
      digitalWrite(input1Pin, HIGH);
      digitalWrite(input2Pin, LOW);
      analogWrite(enablePin, 190);
      speed = "Speed 1";
    }
    else if (IrReceiver.decodedIRData.command == 0x46) {
      digitalWrite(input1Pin, HIGH);
      digitalWrite(input2Pin, LOW);
      analogWrite(enablePin, 220);
      speed = "Speed 2"; 
    }
    else if (IrReceiver.decodedIRData.command == 0x47) {
      digitalWrite(input1Pin, HIGH);
      digitalWrite(input2Pin, LOW);
      analogWrite(enablePin, 255); 
      speed = "Speed 3";
    }
    else if (IrReceiver.decodedIRData.command == 0x19) {
      digitalWrite(input1Pin, LOW);
      digitalWrite(input2Pin, LOW);
      analogWrite(enablePin, 0);
      speed = "OFF"; 
    }

    Serial.print("Protocol: ");
    Serial.println(IrReceiver.getProtocolString());

    Serial.print("Command (Hex): 0x");
    Serial.println(IrReceiver.decodedIRData.command, HEX);

    Serial.print("Motor: ");
    Serial.println(speed);

    Serial.println("---------------------------------");

    lcd.setCursor(0, 1);
    lcd.print("                "); 
    lcd.setCursor(0, 1);
    lcd.print(speed);

    IrReceiver.resume();
  }
}