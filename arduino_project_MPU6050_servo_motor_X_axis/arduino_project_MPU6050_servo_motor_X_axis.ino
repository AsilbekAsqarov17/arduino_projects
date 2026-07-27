#include<Adafruit_MPU6050.h>
#include<Servo.h>

Adafruit_MPU6050 mpu;
int address = 0x68;

Servo myServo;
int servoPin = 9;
int val;
void setup() {

  Serial.begin(9600);
  if(!mpu.begin(address)){
    Serial.println("MPU-6050 not detected!!!");
  }

  mpu.setAccelerometerRange(MPU6050_RANGE_2_G);
  myServo.attach(servoPin);

}

void loop() {

  sensors_event_t a, g, temp;

  mpu.getEvent(&a, &g, &temp);
  float accelX = a.acceleration.x;

  int servoAngle = map(accelX, -9.8, 9.8, 0, 180);

  servoAngle = constrain(servoAngle, 0, 180);
  myServo.write(servoAngle);

  delay(20);
}
