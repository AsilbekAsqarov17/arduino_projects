#include<SPI.h>
#include<MFRC522.h>

#define ss 10
#define rst 9

MFRC522 mfrc522(ss, rst);

int red = 5;
int green = 6;



void setup(){

  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();

  pinMode(green, OUTPUT);
  pinMode(red, OUTPUT);
  delay(4);
  Serial.println(F("RC522 Ready! Scan an RFID card or key fob..."));

}

void loop(){

  if(!mfrc522.PICC_IsNewCardPresent()){
    return;
  }

  if(!mfrc522.PICC_ReadCardSerial()){
    return;
  }

  Serial.print(F("Card Type: "));
  MFRC522::PICC_Type piccType = mfrc522.PICC_GetType(mfrc522.uid.sak);
  Serial.println(mfrc522.PICC_GetTypeName(piccType));

  Serial.print(F("Card UID: "));
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    if (mfrc522.uid.uidByte[i] < 0x10) {
      Serial.print(F(" 0"));
    } else {
      Serial.print(F(" "));
    }
    Serial.print(mfrc522.uid.uidByte[i], HEX);
  }
  Serial.println();

  String content = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();

  if(content.substring(1) == "90 3F F9 55") {
    Serial.print("Access Granted!");
    Serial.print("Welcome!");

    digitalWrite(green, HIGH);
    delay(3000);
    digitalWrite(green, LOW);
  } else {
    Serial.print("Access Denied!");
    Serial.print("Unknown Card");

    digitalWrite(red, HIGH);
    delay(3000);
    digitalWrite(red, LOW);
  }

  Serial.println("Scan Your Card");

  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();

  delay(1000);
}




