#include<Adafruit_MPU6050.h>

int address = 0x68;
int dt = 1000;

Adafruit_MPU6050 mpu;

void setup(){

  Serial.begin(9600);

  if(!mpu.begin(address)){
    Serial.println("MPU-6050 not detected!");
  }
  mpu.setAccelerometerRange(MPU6050_RANGE_2_G);
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

}

void loop(){

  sensors_event_t a, g, temp;

  mpu.getEvent(&a, &g, &temp);

  Serial.print("Accel X: "); Serial.println(a.acceleration.x);
  Serial.print("Accel Y: "); Serial.println(a.acceleration.y);
  Serial.print("Accel Z: "); Serial.println(a.acceleration.z);  

  Serial.print("Gyro X: "); Serial.println(g.gyro.x);
  Serial.print("Gyro Y: "); Serial.println(g.gyro.y);
  Serial.print("Gyro Z: "); Serial.println(g.gyro.z);
  Serial.println("------------------------------");

  delay(dt);
}





