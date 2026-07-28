#include<IRremote.hpp>
int receiverPin = 4;

int enablePin = 11;
int input1Pin = 10;
int input2Pin = 9;
int isSpinning = 0;
int dt;

void setup() {

  Serial.begin(9600);
  IrReceiver.begin(receiverPin, ENABLE_LED_FEEDBACK);

  pinMode(enablePin, OUTPUT);
  pinMode(input1Pin, OUTPUT);
  pinMode(input2Pin, OUTPUT);
}

void loop() {

  if(IrReceiver.decode()){
    
    if(IrReceiver.decodedIRData.command == 0x45){
      Serial.print("Protocol: ");
      Serial.print(IrReceiver.getProtocolString());
      Serial.print(" | Command: 0x");
      Serial.println(IrReceiver.decodedIRData.command, HEX);

      if(isSpinning == 0){
        isSpinning = 1;
        Serial.println("Motor: ON");
      }else{
        isSpinning = 0;
        Serial.println("Motor: OFF");
      }

      delay(500);
    }
    IrReceiver.resume();

  }
  if(isSpinning == 1){

      digitalWrite(input1Pin, HIGH);
      digitalWrite(input2Pin, LOW);
      analogWrite(enablePin, 255);

    }
    else{
      digitalWrite(input1Pin, LOW);
      digitalWrite(input2Pin, LOW);
      analogWrite(enablePin, 0);
    }
}
