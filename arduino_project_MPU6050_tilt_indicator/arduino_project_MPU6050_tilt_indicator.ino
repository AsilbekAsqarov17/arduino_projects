#include<Adafruit_MPU6050.h>

Adafruit_MPU6050 mpu;
int address = 0x68;

int redPin = 8;
int yellowPin = 9;
int greenPin = 10;

int dt = 500;

void setup() {

  Serial.begin(9600);
  if(!mpu.begin(address)){
    Serial.println("MPU-6050 not detected!!!");
  }

  pinMode(redPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(greenPin, OUTPUT);

}

void loop() {

  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  float tiltX = abs(a.acceleration.x);
  float tiltY = abs(a.acceleration.y);

  if(tiltX < 0.5 && tiltY < 0.5){
    
    Serial.println("Balanced!");
    Serial.println("-------------------");
    digitalWrite(greenPin, HIGH);
    digitalWrite(redPin, LOW);
    digitalWrite(yellowPin, LOW);

  }
  else if(tiltX < 2.5 && tiltY < 2.5){

    Serial.println("Slightly Tilted!");
    Serial.println("------------------");
    digitalWrite(greenPin, LOW);
    digitalWrite(redPin, LOW);
    digitalWrite(yellowPin, HIGH);

  }
  else{

    Serial.println("Highly Tilted!");
    Serial.println("------------------");
    digitalWrite(greenPin, LOW);
    digitalWrite(redPin, HIGH);
    digitalWrite(yellowPin, LOW);

  }

  delay(dt);
}
