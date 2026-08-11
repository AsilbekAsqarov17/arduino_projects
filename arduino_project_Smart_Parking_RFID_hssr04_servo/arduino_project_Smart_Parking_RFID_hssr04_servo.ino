#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

// RFID pin
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);

// Servo pin
Servo barrier;
const int SERVO_PIN = 4;

// HC-SR04 pins
const int TRIG_PIN = 2;
const int ECHO_PIN = 3;

// LED Pinlari
const int RED_LED = 6;
const int GREEN_LED = 5;

bool vehicleDetected = false;

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();

  barrier.attach(SERVO_PIN);
  barrier.write(0); 

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);

  digitalWrite(RED_LED, HIGH);
  digitalWrite(GREEN_LED, LOW);

  Serial.println(F("Smart Parking System Ready..."));
}

long getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);
  long distance = duration * 0.034 / 2;
  return distance;
}

void loop() {
  long dist = getDistance();

  if (dist > 0 && dist <= 10) {
    
    if (!vehicleDetected) {
      Serial.println(F("Vehicle detected! Scan RFID card..."));
      vehicleDetected = true; 
    }

    if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
      
      String content = "";
      for (byte i = 0; i < mfrc522.uid.size; i++) {
        content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
        content.concat(String(mfrc522.uid.uidByte[i], HEX));
      }
      content.toUpperCase();

      Serial.print(F("Scanned UID:"));
      Serial.println(content);

      if (content.substring(1) == "90 3F F9 55") {
        Serial.println(F("Access Granted. Opening Barrier..."));

        digitalWrite(RED_LED, LOW);
        digitalWrite(GREEN_LED, HIGH);
        barrier.write(90); 

        delay(5000); 

        barrier.write(0);
        digitalWrite(GREEN_LED, LOW);
        digitalWrite(RED_LED, HIGH);
        Serial.println(F("Barrier Closed."));

      } else {
        Serial.println(F("Access Denied!"));
        
        for (int i = 0; i < 3; i++) {
          digitalWrite(RED_LED, LOW);
          delay(200);
          digitalWrite(RED_LED, HIGH);
          delay(200);
        }
      }

      mfrc522.PICC_HaltA();
      mfrc522.PCD_StopCrypto1();
    }

  } else {
    if (vehicleDetected) {
      vehicleDetected = false; 
    }
  }

  delay(200);
}