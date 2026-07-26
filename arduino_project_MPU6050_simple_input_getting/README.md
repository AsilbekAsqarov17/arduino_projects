# Arduino Project 25: MPU-6050 Motion Sensor 📐⚡🌀

This project introduces the **MPU-6050**, a motion-sensing module that combines:

* 📐 A 3-axis accelerometer
* 🌀 A 3-axis gyroscope
* 🌡️ A temperature sensor

The project uses the MPU-6050 to measure:

```text
📐 ACCELERATION
   X-axis
   Y-axis
   Z-axis

🌀 ANGULAR VELOCITY
   X-axis
   Y-axis
   Z-axis

🌡️ TEMPERATURE
```

The sensor communicates with the Arduino using the **I²C communication protocol**.

```text
        🧠 Arduino
             │
       I²C Communication
             │
             ▼
        📐 MPU-6050
```

This project is especially useful for understanding how a complex sensor communicates with a microcontroller.

---

# What Is the MPU-6050? 📐🌀

The MPU-6050 is a **6-axis motion sensor**.

The term:

```text
6-axis
```

comes from:

```text
3-axis Accelerometer
+
3-axis Gyroscope
```

```text
┌──────────────────────────┐
│       MPU-6050           │
│                          │
│  📐 Accelerometer        │
│  X  Y  Z                 │
│                          │
│  🌀 Gyroscope            │
│  X  Y  Z                 │
│                          │
│  🌡️ Temperature Sensor   │
└──────────────────────────┘
```

The MPU-6050 can detect:

* ↔️ Movement
* ⬆️ Acceleration
* 🔄 Rotation
* 🧭 Orientation changes
* 📐 Tilting
* 📳 Vibrations
* 🌡️ Temperature

It is commonly used in:

* 🚁 Drones
* 🤖 Robots
* 🚗 Self-balancing vehicles
* 🎮 Motion controllers
* 🛩️ Flight controllers
* 🧭 Navigation systems
* 🦾 Robotics projects

---

# The Main Idea of This Project 🧠

The Arduino does not directly measure the MPU-6050's internal electrical signals.

Instead, the process is:

```text
📐 MPU-6050
      ↓
📡 Measures Motion
      ↓
🔢 Converts Measurements into Data
      ↓
🔗 Sends Data through I²C
      ↓
🧠 Arduino Receives Data
      ↓
💻 Library Interprets Data
      ↓
🖥️ Serial Monitor
```

In this project:

```text
📐 Sensor
   ↓
📡 I²C
   ↓
🧠 Arduino
   ↓
📟 Serial Monitor
```

The Arduino receives values such as:

```text
Accel X: 0.15
Accel Y: 0.42
Accel Z: 9.81

Gyro X: 0.02
Gyro Y: -0.10
Gyro Z: 0.05
```

---

# MPU-6050 Pins 🔌

The basic MPU-6050 module usually uses four main pins:

```text
┌─────────────────────┐
│     MPU-6050        │
│                     │
│ VCC                 │
│ GND                 │
│ SCL                 │
│ SDA                 │
└─────────────────────┘
```

The important connections are:

| MPU-6050 | Arduino Uno                     |
| -------- | ------------------------------- |
| VCC      | 5V or appropriate module supply |
| GND      | GND                             |
| SCL      | A5                              |
| SDA      | A4                              |

```text
MPU-6050          Arduino Uno

VCC   ───────────► 5V
GND   ───────────► GND
SCL   ───────────► A5
SDA   ───────────► A4
```

The most important part is:

```text
A4 → SDA
A5 → SCL
```

---

# What Are VCC and GND? ⚡

## VCC ⚡

VCC provides power to the MPU-6050.

```text
Arduino 5V
     │
     ▼
   VCC
     │
     ▼
📐 MPU-6050
```

The exact voltage requirement depends on the specific MPU-6050 module.

Many breakout boards include a voltage regulator and level-shifting circuitry, but not every module is identical.

Therefore, the voltage requirements of the particular board should always be checked.

---

## GND 🔗

GND is the electrical reference shared by the Arduino and the sensor.

```text
Arduino GND
     │
     └────────► MPU-6050 GND
```

Without a common electrical reference, the Arduino and sensor may not correctly interpret the communication signals.

```text
🧠 Arduino
     │
     └──── Common GND ──── 📐 MPU-6050
```

---

# What Is I²C? 🔗📡

I²C stands for:

```text
Inter-Integrated Circuit
```

It is a communication protocol used for communication between electronic devices.

Instead of requiring many separate wires, I²C mainly uses two communication lines:

```text
SDA
SCL
```

```text
        🧠 Arduino
        ┌────────┐
        │        │
        │ SDA ───┼────────► SDA
        │        │
        │ SCL ───┼────────► SCL
        └────────┘             📐 MPU-6050
```

The two lines have different purposes.

---

# SDA — Serial Data Line 📡

SDA means:

```text
Serial Data
```

This line carries the actual data.

```text
Arduino ◄────────────► MPU-6050
          SDA
       DATA LINE
```

Information such as:

```text
Acceleration X
Acceleration Y
Acceleration Z
Gyroscope X
Gyroscope Y
Gyroscope Z
Temperature
```

is transferred through SDA.

The communication is generally bidirectional:

```text
🧠 Arduino
    │
    │  SDA
    │◄────────►
    │
📐 MPU-6050
```

The Arduino can:

* 📤 Send commands to the sensor
* 📥 Receive sensor data

through the SDA line.

---

# SCL — Serial Clock Line ⏱️

SCL means:

```text
Serial Clock
```

This line synchronizes communication.

Digital devices need to know:

```text
"When should I read this bit?"
"When should I send the next bit?"
```

The clock signal provides this timing.

```text
SCL:

HIGH ──┐    ┌────┐    ┌────┐
        │    │    │    │
LOW ────┘────┘    └────┘    └──
```

The clock helps coordinate the data being transferred through SDA.

```text
SCL → ⏱️ Communication Timing

SDA → 📡 Actual Data
```

Together:

```text
SCL = "When?"
SDA = "What?"
```

---

# Why Does the Arduino Use A4 and A5? 🔄

On an Arduino Uno, the pins:

```text
A4
A5
```

are normally analog input pins.

For example:

```cpp
int sensorPin = A5;
int value = analogRead(sensorPin);
```

In that situation:

```text
A5
 ↓
Analog Input
 ↓
analogRead()
```

However, Arduino pins can often have multiple functions.

The same physical pins can be used for I²C:

```text
A4 → SDA
A5 → SCL
```

So the pins have multiple possible roles:

```text
A4:
├── Analog Input
└── I²C SDA

A5:
├── Analog Input
└── I²C SCL
```

This is called **multiplexing**.

The physical pin remains the same, but the Arduino hardware uses it differently depending on the selected peripheral.

```text
         A4
          │
     ┌────┴────┐
     │         │
analogRead   SDA
```

```text
         A5
          │
     ┌────┴────┐
     │         │
analogRead   SCL
```

---

# A4 and A5 Are Not Permanently Only Analog Pins 🔄

A common misunderstanding is:

```text
A4 = Only Analog Input ❌
A5 = Only Analog Input ❌
```

The correct idea is:

```text
A4 = Analog Input OR SDA
A5 = Analog Input OR SCL
```

The Arduino's internal hardware determines how these pins are being used.

With:

```cpp
analogRead(A5);
```

A5 is used as an analog input.

With I²C communication:

```text
A4 → SDA
A5 → SCL
```

the same physical pins are controlled by the Arduino's I²C hardware.

```text
Before:

A5 → Potentiometer
      ↓
analogRead(A5)

Now:

A5 → SCL
      ↓
I²C Communication
```

This is why the MPU-6050 can communicate through pins that you previously used for potentiometers and other analog sensors.

---

# The Two Libraries Used 📚

This project includes:

```cpp
#include <Adafruit_MPU6050.h>
```

The project also depends on the I²C communication system provided by Arduino's:

```text
Wire
```

The two layers can be understood like this:

```text
┌──────────────────────────┐
│   Adafruit MPU6050       │
│   High-Level Library     │
└────────────┬─────────────┘
             │
             ▼
┌──────────────────────────┐
│        Wire              │
│   I²C Communication      │
└────────────┬─────────────┘
             │
             ▼
┌──────────────────────────┐
│      Arduino Hardware    │
│      A4 = SDA            │
│      A5 = SCL            │
└────────────┬─────────────┘
             │
             ▼
        📐 MPU-6050
```

---

# What Is the `Wire` Library? 🔗

The `Wire` library is Arduino's basic library for I²C communication.

It allows the Arduino to communicate with I²C devices.

Conceptually:

```text
🧠 Arduino
      ↓
   Wire.h
      ↓
I²C Hardware
      ↓
 A4 / A5
      ↓
📐 MPU-6050
```

Without a high-level sensor library, you could communicate with the MPU-6050 using low-level I²C commands.

For example, you would need to:

1. Start I²C communication
2. Select the MPU-6050's address
3. Select a register
4. Request bytes
5. Read the bytes
6. Combine bytes
7. Convert raw data
8. Apply calibration or scaling

Conceptually:

```text
Arduino
   ↓
Start I²C
   ↓
Address MPU-6050
   ↓
Select Register
   ↓
Request Data
   ↓
Receive Raw Bytes
   ↓
Combine Bytes
   ↓
Convert Values
   ↓
Acceleration / Gyroscope
```

This is what makes direct `Wire` communication more complicated.

---

# What Would Direct `Wire` Communication Look Like? 🧠

The MPU-6050 contains many internal registers.

Each register has an address.

For example, the sensor internally stores data in locations such as:

```text
Register
   ↓
┌──────────────┐
│ Accel X High │
├──────────────┤
│ Accel X Low  │
├──────────────┤
│ Accel Y High │
├──────────────┤
│ Accel Y Low  │
├──────────────┤
│ Accel Z High │
├──────────────┤
│ Accel Z Low  │
└──────────────┘
```

Using low-level I²C, the Arduino would need to tell the MPU-6050:

```text
"Go to this register"
        ↓
"Read these bytes"
        ↓
"Send them back to me"
```

Then the Arduino would need to combine the bytes.

For example:

```text
High Byte + Low Byte
          ↓
      Raw Number
          ↓
   Convert to Units
```

This can require code using functions such as:

```text
Wire.begin()
Wire.beginTransmission()
Wire.write()
Wire.endTransmission()
Wire.requestFrom()
Wire.read()
```

The exact code can become significantly longer and more difficult to understand.

---

# Why Use the Adafruit Library? 📚🧠

The Adafruit library provides a higher-level interface.

Instead of manually handling every register and byte, you can use:

```cpp
mpu.getEvent(&a, &g, &temp);
```

This one function performs much of the complicated work internally.

```text
Without Adafruit:

📐 MPU-6050
   ↓
Wire
   ↓
Register Addresses
   ↓
Raw Bytes
   ↓
Combine Bytes
   ↓
Convert Units
   ↓
Your Code

With Adafruit:

📐 MPU-6050
   ↓
Wire
   ↓
Adafruit Library
   ↓
mpu.getEvent()
   ↓
Clean Sensor Data
```

This is the main reason for using a library.

The library provides functions that you would otherwise have to write yourself.

```text
🔴 Low-Level Work
   ↓
Registers
Bytes
Addresses
Conversions
I²C Transactions

🟢 High-Level Work
   ↓
mpu.getEvent()
```

---

# A Library Is Not Magic 🪄

When you write:

```cpp
mpu.getEvent(&a, &g, &temp);
```

the library is performing many operations internally.

Conceptually:

```text
mpu.getEvent()
      ↓
Read MPU-6050 Registers
      ↓
Receive Raw Bytes
      ↓
Combine Bytes
      ↓
Apply Configuration
      ↓
Convert Values
      ↓
Store Results
      ↓
Return Data to Your Program
```

So instead of writing all of that yourself, you use a ready-made abstraction.

```text
Complex Internal Code
        ↓
   📚 Library
        ↓
Simple Function
```

This is similar to using:

```cpp
analogRead(A5);
```

Instead of manually controlling the ADC hardware.

The function hides the complicated low-level operations.

---

# The Adafruit MPU6050 Object 🧱

The code creates an object:

```cpp
Adafruit_MPU6050 mpu;
```

This creates an instance of the `Adafruit_MPU6050` class.

```text
Adafruit_MPU6050
        ↓
       mpu
        ↓
Represents the physical MPU-6050
```

You can then call functions through the object:

```cpp
mpu.begin();
mpu.setAccelerometerRange();
mpu.setGyroRange();
mpu.setFilterBandwidth();
mpu.getEvent();
```

The object acts as an interface between your code and the physical sensor.

```text
Your Code
    ↓
mpu object
    ↓
Adafruit Library
    ↓
Wire / I²C
    ↓
📐 MPU-6050
```

---

# The MPU-6050 I²C Address 📍

The code defines:

```cpp
int address = 0x68;
```

The value:

```text
0x68
```

is the I²C address of the MPU-6050 in the default configuration.

An I²C address works like an identification number.

Imagine several devices connected to the same communication bus:

```text
        SDA
         │
         ├──── 📐 MPU-6050
         │       Address: 0x68
         │
         └──── Other I²C Device
                 Address: 0x3C
```

The Arduino sends:

```text
"Address 0x68, I want to communicate with you."
```

The MPU-6050 responds.

```text
🧠 Arduino
     │
     │ "0x68?"
     ▼
📐 MPU-6050
     │
     └── "Yes, that's me."
```

The MPU-6050 address can be changed using its AD0 pin.

Typically:

```text
AD0 LOW  → 0x68
AD0 HIGH → 0x69
```

This allows two MPU-6050 devices to potentially share the same I²C bus with different addresses.

---

# Starting the Sensor 🔌

The code uses:

```cpp
if(!mpu.begin(address)){
  Serial.println("MPU-6050 not detected!");
}
```

The `begin()` function initializes communication with the sensor.

Conceptually:

```text
Arduino
   ↓
I²C Address 0x68
   ↓
"Are you there?"
   ↓
📐 MPU-6050
   ↓
Response
```

If communication succeeds:

```text
✅ MPU-6050 detected
```

If communication fails:

```text
❌ MPU-6050 not detected
```

Possible causes include:

* 🔌 Incorrect wiring
* 🔄 SDA and SCL swapped
* ⚡ Incorrect power
* 🔗 Missing common ground
* 📍 Incorrect I²C address
* 📐 Faulty sensor
* 📚 Library installation problems

---

# The Accelerometer 📐

An accelerometer measures acceleration along three axes:

```text
X-axis
Y-axis
Z-axis
```

```text
             Z
             ↑
             │
             │
             ●────────► X
            /
           /
          Y
```

The sensor can detect:

```text
↔️ Movement along X
↕️ Movement along Y
⬆️ Movement along Z
```

The code reads:

```cpp
a.acceleration.x
a.acceleration.y
a.acceleration.z
```

The result is usually measured in:

```text
m/s²
```

which means:

```text
meters per second squared
```

---

# Gravity and the Accelerometer 🌍

One interesting thing about an accelerometer is that it detects gravity.

Earth's gravitational acceleration is approximately:

```text
9.81 m/s²
```

If the sensor is lying flat:

```text
        📐 MPU-6050
       ┌──────────┐
       │          │
       └──────────┘
             ↓
           🌍 Gravity
```

one axis may measure approximately:

```text
9.81 m/s²
```

while the other axes may be close to:

```text
0 m/s²
```

For example:

```text
Accel X: 0.10
Accel Y: 0.20
Accel Z: 9.81
```

This means the Z-axis is currently aligned approximately with gravity.

---

# Accelerometer Range ⚡

The code sets:

```cpp
mpu.setAccelerometerRange(MPU6050_RANGE_2_G);
```

This configures the accelerometer to measure approximately:

```text
-2G to +2G
```

Since:

```text
1G ≈ 9.81 m/s²
```

the approximate range is:

```text
-19.62 m/s²
        ↓
+19.62 m/s²
```

```text
       0
       │
-2G ───┼─── +2G
```

The MPU-6050 supports different accelerometer ranges:

```text
±2G
±4G
±8G
±16G
```

The trade-off is:

```text
Smaller Range
      ↓
Better Sensitivity

Larger Range
      ↓
Can Measure Stronger Acceleration
```

For gentle movement:

```text
±2G
```

may be useful.

For stronger movement:

```text
±8G or ±16G
```

may be more appropriate.

---

# The Gyroscope 🌀

The gyroscope measures rotational movement.

It measures how quickly the sensor rotates around each axis.

```text
             Z
             ↑
             │
             ●────────► X
            /
           /
          Y
```

The gyroscope measures:

```text
Rotation around X
Rotation around Y
Rotation around Z
```

The code reads:

```cpp
g.gyro.x
g.gyro.y
g.gyro.z
```

The values are usually measured in:

```text
radians per second
```

```text
rad/s
```

Conceptually:

```text
📐 Sensor
   ↓
Rotate around X
   ↓
Gyroscope X detects rotation
```

```text
📐 Sensor
   ↓
Rotate around Y
   ↓
Gyroscope Y detects rotation
```

```text
📐 Sensor
   ↓
Rotate around Z
   ↓
Gyroscope Z detects rotation
```

---

# Gyroscope Range 🌀

The code sets:

```cpp
mpu.setGyroRange(MPU6050_RANGE_250_DEG);
```

This configures the gyroscope to measure approximately:

```text
±250 degrees per second
```

The MPU-6050 can use different ranges:

```text
±250°/s
±500°/s
±1000°/s
±2000°/s
```

The same idea applies:

```text
Smaller Range
      ↓
More Sensitive to Small Rotations

Larger Range
      ↓
Can Measure Faster Rotation
```

For slow movements:

```text
±250°/s
```

is useful.

For very fast rotation:

```text
±1000°/s
or
±2000°/s
```

may be necessary.

---

# Accelerometer vs Gyroscope 📐🌀

These sensors measure different things.

## Accelerometer

Measures:

```text
Linear Acceleration
```

Example:

```text
The sensor moves forward.
```

```text
🧠 Movement
   ↓
📐 Accelerometer
   ↓
Detects acceleration
```

## Gyroscope

Measures:

```text
Rotation
```

Example:

```text
The sensor turns or rotates.
```

```text
🔄 Rotation
   ↓
🌀 Gyroscope
   ↓
Detects angular velocity
```

Together:

```text
📐 Accelerometer → Linear Movement
🌀 Gyroscope    → Rotation
```

This combination is extremely useful in robotics and motion tracking.

---

# The Digital Filter 🎛️

The code uses:

```cpp
mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
```

This configures the sensor's digital low-pass filter.

Real-world sensor data can contain noise:

```text
Ideal Signal:

───────╮      ╭───────
       │      │
       ╰──────╯

Real Signal:

─╮─╭──╮─╭──╮──╭─╮──╭──
 │ │  │ │  │  │ │  │
```

A filter can reduce unwanted high-frequency noise.

```text
Raw Data
   ↓
📡 Noise
   ↓
🎛️ Digital Filter
   ↓
Cleaner Data
```

The setting:

```text
21 Hz
```

means the filter is configured to reduce higher-frequency changes above the selected bandwidth.

There is always a trade-off:

```text
More Filtering
      ↓
Smoother Data
      ↓
Potentially More Delay

Less Filtering
      ↓
Faster Response
      ↓
More Noise
```

---

# The `sensors_event_t` Structure 📦

Inside `loop()`:

```cpp
sensors_event_t a, g, temp;
```

creates three variables:

```text
a    → Accelerometer data
g    → Gyroscope data
temp → Temperature data
```

Conceptually:

```text
a
├── acceleration.x
├── acceleration.y
└── acceleration.z

g
├── gyro.x
├── gyro.y
└── gyro.z

temp
└── temperature
```

These variables act like containers for sensor measurements.

---

# Getting Sensor Data 📥

The most important function in the project is:

```cpp
mpu.getEvent(&a, &g, &temp);
```

This asks the library to read the current sensor data.

The `&` symbol passes the variables by reference.

Conceptually:

```text
Before:

a     = empty
g     = empty
temp  = empty

        ↓

mpu.getEvent(&a, &g, &temp)

        ↓

After:

a     = Accelerometer Data
g     = Gyroscope Data
temp  = Temperature Data
```

Then the program can access:

```cpp
a.acceleration.x
```

or:

```cpp
g.gyro.z
```

---

# Why Does `getEvent()` Use `&`? 🧠

The function needs to fill several data structures.

Instead of returning only one value:

```text
return acceleration
```

the function receives references to variables that it can update.

```text
Function
    │
    ├──► Fill accelerometer variable
    ├──► Fill gyroscope variable
    └──► Fill temperature variable
```

Conceptually:

```text
mpu.getEvent(
    &accelerometer,
    &gyroscope,
    &temperature
);
```

The function writes the measured values into those variables.

---

# Reading Accelerometer Values 📐

The code:

```cpp
Serial.print("Accel X: ");
Serial.println(a.acceleration.x);
```

prints the acceleration along the X-axis.

Similarly:

```cpp
a.acceleration.y
```

reads Y-axis acceleration.

```cpp
a.acceleration.z
```

reads Z-axis acceleration.

```text
📐 Accelerometer
     │
     ├── X → a.acceleration.x
     ├── Y → a.acceleration.y
     └── Z → a.acceleration.z
```

---

# Reading Gyroscope Values 🌀

The code:

```cpp
g.gyro.x
```

reads rotation around the X-axis.

```cpp
g.gyro.y
```

reads rotation around the Y-axis.

```cpp
g.gyro.z
```

reads rotation around the Z-axis.

```text
🌀 Gyroscope
     │
     ├── X → g.gyro.x
     ├── Y → g.gyro.y
     └── Z → g.gyro.z
```

---

# Temperature Data 🌡️

The code also creates:

```cpp
sensors_event_t temp;
```

The MPU-6050 contains an internal temperature sensor.

The temperature can be accessed through the temperature event structure.

```text
📐 MPU-6050
      ↓
🌡️ Internal Temperature Sensor
      ↓
📦 temp
```

Although this project does not print the temperature, the sensor data is still retrieved by:

```cpp
mpu.getEvent(&a, &g, &temp);
```

---

# The Complete Data Flow 📡

The complete process is:

```text
        📐 MPU-6050
              │
              │ Measures
              ▼
     ┌──────────────────┐
     │ Acceleration      │
     │ Rotation          │
     │ Temperature       │
     └────────┬─────────┘
              │
              ▼
          I²C Bus
        SDA + SCL
              │
              ▼
          🧠 Arduino
              │
              ▼
      📚 Adafruit Library
              │
              ▼
        mpu.getEvent()
              │
              ▼
       sensors_event_t
              │
              ▼
       💻 Serial Monitor
```

---

# Complete Project Flow 🔄

```text
1️⃣ Arduino starts
        ↓
2️⃣ Serial communication begins
        ↓
3️⃣ MPU-6050 is initialized
        ↓
4️⃣ Accelerometer range is configured
        ↓
5️⃣ Gyroscope range is configured
        ↓
6️⃣ Digital filter is configured
        ↓
7️⃣ Sensor data is requested
        ↓
8️⃣ I²C transfers data
        ↓
9️⃣ Adafruit library processes the data
        ↓
🔟 Values are printed to Serial Monitor
        ↓
⏱️ Wait 1 second
        ↓
🔄 Repeat
```

---

# The `setup()` Function ⚙️

## Serial Communication

```cpp
Serial.begin(9600);
```

starts communication between the Arduino and the computer.

```text
🧠 Arduino
     │
     │ USB Serial
     ▼
💻 Computer
```

The baud rate is:

```text
9600 bits per second
```

This allows the values to be displayed in the Serial Monitor.

---

# Initializing the MPU-6050 🔌

```cpp
if(!mpu.begin(address)){
```

The Arduino attempts to communicate with the sensor at:

```text
0x68
```

If the sensor cannot be detected:

```cpp
Serial.println("MPU-6050 not detected!");
```

is printed.

A more complete program would usually stop or handle the error after detection fails.

---

# Configuring the Accelerometer 📐

```cpp
mpu.setAccelerometerRange(MPU6050_RANGE_2_G);
```

The sensor is configured for:

```text
±2G
```

This determines the maximum acceleration range that the sensor measures.

---

# Configuring the Gyroscope 🌀

```cpp
mpu.setGyroRange(MPU6050_RANGE_250_DEG);
```

The gyroscope is configured for:

```text
±250°/s
```

This determines the maximum angular velocity range.

---

# Configuring the Filter 🎛️

```cpp
mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
```

This configures the internal digital filtering.

```text
Raw Sensor Data
      ↓
🎛️ Filter
      ↓
Cleaner Measurements
```

---

# The `loop()` Function 🔄

Every loop iteration:

```cpp
sensors_event_t a, g, temp;
```

creates containers for the current sensor measurements.

Then:

```cpp
mpu.getEvent(&a, &g, &temp);
```

requests fresh data.

The values are then printed:

```text
Acceleration X
Acceleration Y
Acceleration Z

Gyroscope X
Gyroscope Y
Gyroscope Z
```

Finally:

```cpp
delay(dt);
```

pauses the program.

Since:

```cpp
int dt = 1000;
```

the program waits:

```text
1000 ms = 1 second
```

before taking another measurement.

```text
📐 Read Data
    ↓
💻 Print Data
    ↓
⏱️ Wait 1 sec
    ↓
🔄 Read Again
```

---

# Why Use a Library Instead of Writing Everything with `Wire`? 📚

This project demonstrates an important programming concept:

```text
Abstraction
```

At the low level:

```text
I²C
   ↓
Register Addresses
   ↓
Raw Bytes
   ↓
Conversions
   ↓
Physical Values
```

At the high level:

```cpp
mpu.getEvent(&a, &g, &temp);
```

The library hides unnecessary complexity.

This is similar to using:

```cpp
analogRead(A5);
```

You do not manually control every ADC register.

Instead, Arduino provides a function.

```text
Low-Level Hardware
       ↓
      API
       ↓
Simple Function
```

The Adafruit library provides a similar abstraction for the MPU-6050.

---

# `Wire` vs `Adafruit_MPU6050` 🔗📚

The two libraries operate at different levels.

## `Wire`

```text
Low-Level I²C Communication
```

It handles:

```text
📡 SDA
⏱️ SCL
📍 Device Addresses
📦 Bytes
🔗 I²C Transactions
```

You would use it when you need direct control over the sensor's registers.

---

## `Adafruit_MPU6050`

```text
High-Level Sensor Interface
```

It provides functions such as:

```cpp
mpu.begin();
mpu.getEvent();
mpu.setAccelerometerRange();
mpu.setGyroRange();
mpu.setFilterBandwidth();
```

This allows you to work with the sensor more easily.

```text
        Your Code
            ↓
   Adafruit MPU6050
            ↓
           Wire
            ↓
           I²C
            ↓
        MPU-6050
```

The Adafruit library uses lower-level communication internally.

---

# Libraries Are Layers 🧱

A useful way to understand libraries is to imagine layers:

```text
┌────────────────────────────┐
│       YOUR PROGRAM         │
│                            │
│   mpu.getEvent(...)        │
└─────────────┬──────────────┘
              │
              ▼
┌────────────────────────────┐
│   ADAFRUIT MPU6050         │
│                            │
│ Sensor-specific functions  │
└─────────────┬──────────────┘
              │
              ▼
┌────────────────────────────┐
│          WIRE              │
│                            │
│   I²C communication        │
└─────────────┬──────────────┘
              │
              ▼
┌────────────────────────────┐
│     ARDUINO I²C HARDWARE   │
│                            │
│       A4 = SDA             │
│       A5 = SCL             │
└─────────────┬──────────────┘
              │
              ▼
┌────────────────────────────┐
│        MPU-6050            │
└────────────────────────────┘
```

Each layer makes the next layer easier to use.

---

# What Happens When You Call `mpu.getEvent()`? 🧠

Conceptually:

```text
mpu.getEvent()
       ↓
Adafruit Library
       ↓
Wire Library
       ↓
I²C START
       ↓
Address 0x68
       ↓
Register Request
       ↓
SDA Transfers Bytes
       ↓
SCL Synchronizes Timing
       ↓
Raw Data Received
       ↓
Data Converted
       ↓
Event Structures Filled
       ↓
Your Code Reads Values
```

This is why a single line can replace a large amount of low-level code.

---

# Important I²C Concept: Multiple Devices on One Bus 🚌

One advantage of I²C is that multiple devices can share the same SDA and SCL lines.

```text
                 SDA
                  │
        ┌─────────┼─────────┐
        │         │         │
        ▼         ▼         ▼
   📐 MPU-6050  📟 LCD  🌡️ Sensor
     0x68       0x27      0x76
```

Each device has a different address.

The Arduino communicates with a specific device by using its address.

```text
0x68 → MPU-6050
0x27 → Another device
0x76 → Another device
```

This is much more efficient than needing separate communication pins for every sensor.

---

# Why I²C Is Useful 🔗

Without I²C:

```text
Arduino
  │
  ├── Many pins for Sensor 1
  ├── Many pins for Sensor 2
  ├── Many pins for Sensor 3
  └── Many pins for Sensor 4
```

With I²C:

```text
Arduino
   │
   ├── SDA ───────┐
   └── SCL ───────┼── Multiple I²C Devices
                  │
                  ├── 📐 MPU-6050
                  ├── 📟 Display
                  └── 🌡️ Sensor
```

The devices share the same communication bus.

---

# The MPU-6050 and Analog Pins 🔄

Previously, A5 could be used like:

```cpp
int potVal = analogRead(A5);
```

In that project:

```text
Potentiometer
      ↓
A5
      ↓
ADC
      ↓
analogRead()
```

In this project:

```text
MPU-6050
      ↓
SCL
      ↓
A5
      ↓
I²C Hardware
```

Similarly:

```text
Previous:

Photoresistor
      ↓
A4 or A5
      ↓
analogRead()

Now:

MPU-6050
      ↓
SDA
      ↓
A4
      ↓
I²C Hardware
```

The important concept is:

```text
The physical pin has multiple possible functions.
```

The Arduino can connect the pin internally to different hardware systems.

```text
A5
 │
 ├── ADC → analogRead()
 │
 └── I²C → SCL
```

```text
A4
 │
 ├── ADC → analogRead()
 │
 └── I²C → SDA
```

This is an example of the microcontroller's internal peripheral system.

---

# Components

* 🧠 Arduino board
* 📐 MPU-6050 motion sensor
* 🔌 Jumper wires
* 🧱 Breadboard
* 💻 Computer
* 📚 `Adafruit_MPU6050` library
* 🔗 I²C / `Wire` communication system

---

# Important Functions Used

### `mpu.begin()`

Initializes communication with the MPU-6050.

```cpp
mpu.begin(address);
```

---

### `setAccelerometerRange()`

Configures the acceleration measurement range.

```cpp
mpu.setAccelerometerRange(MPU6050_RANGE_2_G);
```

---

### `setGyroRange()`

Configures the gyroscope measurement range.

```cpp
mpu.setGyroRange(MPU6050_RANGE_250_DEG);
```

---

### `setFilterBandwidth()`

Configures the digital filtering bandwidth.

```cpp
mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
```

---

### `getEvent()`

Reads the latest accelerometer, gyroscope, and temperature data.

```cpp
mpu.getEvent(&a, &g, &temp);
```

---

### `Serial.print()`

Prints text and values to the Serial Monitor.

---

### `delay()`

Pauses the program for a specified amount of time.

```cpp
delay(1000);
```

means:

```text
⏱️ Wait 1 second
```

---

# Concepts Demonstrated 🧠

* 📐 Accelerometers
* 🌀 Gyroscopes
* 🌡️ Temperature sensors
* 🔗 I²C communication
* 📡 SDA and SCL
* 🔄 Arduino multifunction pins
* A4 as SDA
* A5 as SCL
* 📚 Arduino libraries
* 📚 Adafruit sensor abstraction
* 🔗 `Wire` communication layer
* 📍 I²C device addresses
* 🧱 Software abstraction layers
* 📦 Structures and sensor events
* `sensors_event_t`
* `mpu.getEvent()`
* Digital filtering
* Sensor measurement ranges
* Raw hardware communication vs high-level APIs

---

# Complete Concept Summary 🧠

```text
        📐 MPU-6050
        ┌──────────┐
        │ Accel    │
        │ Gyro     │
        │ Temp     │
        └────┬─────┘
             │
             │ I²C
       ┌─────┴─────┐
       │           │
      SDA         SCL
       │           │
      A4          A5
       │           │
       └─────┬─────┘
             │
        🧠 Arduino
             │
             ▼
          📚 Wire
             │
             ▼
      📚 Adafruit Library
             │
             ▼
       mpu.getEvent()
             │
             ▼
      📦 Sensor Events
             │
             ▼
       💻 Serial Monitor
```

The main lesson of this project is that a sensor does not need a separate Arduino pin for every individual value it measures.

Instead, the MPU-6050 sends multiple measurements through a shared communication system:

```text
📐 Acceleration X
📐 Acceleration Y
📐 Acceleration Z
🌀 Gyroscope X
🌀 Gyroscope Y
🌀 Gyroscope Z
🌡️ Temperature
        ↓
   I²C Communication
        ↓
      Arduino
```

And instead of manually writing all of the low-level communication code yourself, the Adafruit library provides a convenient interface:

```cpp
mpu.getEvent(&a, &g, &temp);
```

> 📐🌀 The MPU-6050 is a great example of how modern electronics combine sensors, digital communication, microcontroller peripherals, and software libraries into one system.

