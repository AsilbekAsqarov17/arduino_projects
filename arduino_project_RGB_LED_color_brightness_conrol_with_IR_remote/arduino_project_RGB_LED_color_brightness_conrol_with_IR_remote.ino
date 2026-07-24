#include <IRremote.hpp>
int receiverPin = 9;
int command;
String color = "OFF";
int redPin = 6;
int greenPin = 5;
int bluePin = 10;
int brightness = 255;

int dt = 250;

void setup() {

  Serial.begin(9600);
  IrReceiver.begin(receiverPin, ENABLE_LED_FEEDBACK);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {

  if (IrReceiver.decode()) {

    command = IrReceiver.decodedIRData.command;

    if(command == 0x16){
      color = "White";
    }
    else if(command == 0xD){
      color = "OFF";
    }
    else if(command == 0x45){
      color = "Red";
    }
    else if(command == 0x46){
      color = "Green";
    }
    else if(command == 0x47){
      color = "Blue";
    }
    else if(command == 0x44){
      color = "Cyan";
    }
    else if(command == 0x40){
      color = "Magenta";
    }
    else if(command == 0x43){
      color = "Yellow";
    }
    else if(command == 0x18){
      if(brightness <= 240){
      brightness += 15;
      }
    }
    else if(command == 0x52){
      if(brightness >=15){
        brightness -= 15;
      }
    }

    Serial.print("Command: ");
    Serial.println(command,HEX);
    Serial.print("Color: ");
    Serial.println(color);
    Serial.print("Brightness:");
    Serial.println(brightness);
    Serial.println("----------------------");

    updateLED();
    delay(dt);

    IrReceiver.resume();
  }

}

void updateLED() {
  if (color == "OFF")     setColor(0, 0, 0);
  else if (color == "White")   setColor(brightness, brightness, brightness);
  else if (color == "Red")     setColor(brightness, 0, 0);
  else if (color == "Green")   setColor(0, brightness, 0);
  else if (color == "Blue")    setColor(0, 0, brightness);
  else if (color == "Cyan")    setColor(0, brightness, brightness);
  else if (color == "Magenta") setColor(brightness, 0, brightness);
  else if (color == "Yellow")  setColor(brightness, brightness, 0);
}

void setColor(int red, int green, int blue){
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}
