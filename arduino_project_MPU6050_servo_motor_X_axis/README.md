# Arduino Project 27: MPU-6050 Accelerometer Controlled Servo

This project uses an **MPU-6050 motion sensor** to control the position of a **servo motor** based on the acceleration detected along the X-axis.

As the MPU-6050 is tilted, the acceleration value changes. The Arduino then converts this acceleration value into a servo angle between **0° and 180°**.

```text
MPU-6050
    ↓
X-Axis Acceleration
    ↓
Convert Acceleration → Servo Angle
    ↓
Servo Motor Movement
```

---

## How It Works

The MPU-6050 is initialized using the **Adafruit MPU6050 library**:

```cpp
Adafruit_MPU6050 mpu;
```

The sensor is then started:

```cpp
mpu.begin(address);
```

The accelerometer range is set to:

```cpp
mpu.setAccelerometerRange(MPU6050_RANGE_2_G);
```

This configures the sensor to measure acceleration within a range of approximately:

```text
-2G → +2G
```

The sensor data is then read:

```cpp
sensors_event_t a, g, temp;

mpu.getEvent(&a, &g, &temp);
```

The X-axis acceleration is extracted:

```cpp
float accelX = a.acceleration.x;
```

The acceleration is measured in:

```text
m/s²
```

---

## Converting Acceleration into a Servo Angle

The acceleration value is converted into an angle using:

```cpp
int servoAngle = map(accelX, -9.8, 9.8, 0, 180);
```

This creates a relationship between acceleration and servo position:

```text
-9.8 m/s²  →  0°
  0.0 m/s² →  90°
+9.8 m/s²  →  180°
```

Conceptually:

```text
Acceleration
     │
+9.8 │                 ─────── 180°
     │
 0.0 │          ─────── 90°
     │
-9.8 │ ─────── 0°
     └──────────────────────────
             Servo Angle
```

The resulting angle is sent to the servo:

```cpp
myServo.write(servoAngle);
```

The servo therefore responds to the physical movement of the MPU-6050.

---

## Why `constrain()` Is Used

The calculated angle is limited using:

```cpp
servoAngle = constrain(servoAngle, 0, 180);
```

This guarantees that the value sent to the servo remains inside its expected range:

```text
0° ≤ servoAngle ≤ 180°
```

Real sensor readings can sometimes be slightly outside the expected range because of:

* Sensor noise
* Vibrations
* Sudden movement
* Measurement variation

For example:

```text
185° → 180°
-5°  → 0°
```

---

## Servo Motor

A servo motor is designed to move to a specific position rather than simply rotating continuously like a normal DC motor.

Its typical position range is:

```text
0° ───────── 90° ───────── 180°
```

The Arduino sends a control signal to the servo on:

```cpp
int servoPin = 9;
```

and controls its position using:

```cpp
myServo.write(servoAngle);
```

In this project:

```text
MPU-6050 tilts
      ↓
Acceleration changes
      ↓
Acceleration is mapped
      ↓
Servo angle changes
```

---

# 🔋 Capacitor in the Circuit

A capacitor is connected between the **5V and GND power rails** of the Arduino:

```text
Arduino 5V ────────┬──── MPU-6050 VCC
                   │
                 (+)
              Capacitor
                 (-)
                   │
Arduino GND ───────┴──── MPU-6050 GND
```

The servo is also powered from the same 5V and GND supply lines in this setup.

---

## What Is a Capacitor?

A capacitor is an electronic component that can:

* ⚡ Store a small amount of electrical energy
* 🔄 Release energy quickly when needed
* 🧹 Reduce voltage fluctuations
* 🛡️ Help stabilize a power supply

A simple capacitor can be thought of as a small temporary electrical reservoir.

```text
Power supply
     ↓
Capacitor stores energy
     ↓
Small voltage fluctuation
     ↓
Capacitor helps stabilize the voltage
```

---

## Why Is a Capacitor Used Here?

Servo motors can suddenly draw more current when they start moving or change direction.

For example:

```text
Servo stopped
     ↓
Servo suddenly starts moving
     ↓
Current demand increases
     ↓
Voltage may temporarily drop
```

Because the **MPU-6050 and servo share the same 5V power line**, these sudden changes can affect the power supply.

This can cause:

* MPU-6050 communication errors
* Unstable sensor readings
* Servo jitter
* Arduino resets
* The sensor temporarily disconnecting

The capacitor helps by acting as a **small local energy buffer** near the circuit.

When the voltage briefly drops, the capacitor can release some stored energy and help smooth the power supply.

```text
Servo suddenly needs more current
             ↓
       Voltage fluctuation
             ↓
      Capacitor helps smooth
             ↓
       More stable power
```

> ⚠️ The capacitor cannot replace a proper power supply. If a servo requires more current than the Arduino's 5V supply can safely provide, an external power supply should be used.

When using an external power supply for the servo:

```text
External Supply GND ───── Arduino GND
```

must be connected together so that both devices share a **common ground**.

---

## Why This Is Especially Important with a Servo

A servo contains:

* A DC motor
* Gears
* A position control circuit

When the servo moves, the motor may require significantly more current than when it is stationary.

This creates a sudden change in the power demand:

```text
Servo not moving:
Current demand → low

Servo starts moving:
Current demand → increases suddenly
```

Since the MPU-6050 communicates with the Arduino using I²C, unstable power can potentially interfere with the sensor's operation.

The capacitor helps improve the stability of the shared power rail.

---

# Hardware

## MPU-6050

| MPU-6050 Pin | Arduino Uno | Purpose   |
| ------------ | ----------- | --------- |
| `VCC`        | `5V`        | Power     |
| `GND`        | `GND`       | Ground    |
| `SCL`        | `A5`        | I²C clock |
| `SDA`        | `A4`        | I²C data  |

## Servo Motor

| Servo Wire | Connection           |
| ---------- | -------------------- |
| Signal     | Arduino Pin `9`      |
| VCC        | Shared 5V power rail |
| GND        | Shared GND rail      |

## Capacitor

| Capacitor Terminal | Connection |
| ------------------ | ---------- |
| Positive `+`       | 5V         |
| Negative `-`       | GND        |

> ⚠️ If you are using a polarized electrolytic capacitor, connect the positive and negative terminals correctly. Reversing the polarity can damage the capacitor.

---

# Important: Sensor Orientation

This project reads only:

```cpp
a.acceleration.x
```

Therefore, the servo responds specifically to changes along the **X-axis**.

The physical orientation of the MPU-6050 matters significantly.

If the sensor is rotated, the same physical movement may produce different values.

For example:

```text
Tilt along X-axis → Servo responds strongly
Tilt along Y-axis → Little or no response
```

To use a different axis, you could read:

```cpp
a.acceleration.y
```

or:

```cpp
a.acceleration.z
```

---

# Real-World Calibration

The values:

```text
-9.8 m/s²
+9.8 m/s²
```

are based on the approximate acceleration caused by Earth's gravity.

However, the actual readings in a real circuit may vary because of:

* Sensor orientation
* Sensor noise
* Calibration
* Mechanical mounting
* Vibrations
* Movement speed
* Power stability

Therefore, the mapping range may need to be adjusted for a specific physical setup.

A useful way to calibrate the project is to first print:

```cpp
Serial.println(accelX);
```

Then observe the minimum and maximum values produced by the actual movement of the sensor.

Those measured values can then be used in:

```cpp
map(accelX, minimumValue, maximumValue, 0, 180);
```

---

# Project Concept

This project combines:

* 📡 I²C communication
* 📐 Accelerometer measurements
* 🔢 Data mapping
* ⚙️ Servo motor control
* 🔋 Power supply stabilization

The complete process is:

```text
┌───────────────────┐
│     MPU-6050      │
│  Motion Sensor    │
└─────────┬─────────┘
          │
          ▼
  X-Axis Acceleration
          │
          ▼
   map() Function
          │
          ▼
     0° – 180°
          │
          ▼
┌───────────────────┐
│   Servo Motor     │
│ Changes Position  │
└───────────────────┘

      5V Power Rail
          │
     ┌────┴────┐
     │ Capacitor│
     │ 5V ↔ GND │
     └─────────┘
```

This project demonstrates how a physical movement can be detected by a sensor, processed by a microcontroller, and converted into mechanical movement.

It is a simple foundation for more advanced projects such as:

* 🤖 Robot orientation systems
* 🦾 Robotic mechanisms
* 📐 Electronic leveling systems
* 🎮 Motion controllers
* 🚁 Drone stabilization concepts
* 🧭 Sensor-based control systems
