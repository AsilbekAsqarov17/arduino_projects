# 🚗 Arduino Project 32: Smart Parking System Using RFID, HC-SR04, Servo Motor & LEDs

This project combines multiple Arduino components to create a simple **Smart Parking Access System**.

The system uses an **HC-SR04 ultrasonic sensor** to detect when a vehicle arrives at the parking entrance. Once a vehicle is detected within **10 cm**, the system asks the driver to scan an RFID card.

The **MFRC522 RFID reader** reads the card's UID and sends the information to the Arduino using the **SPI hardware communication protocol**.

🔐 If the RFID card is authorized:

* 🟢 Green LED turns ON
* 🔴 Red LED turns OFF
* 🚧 Servo motor opens the parking barrier
* ⏱️ Barrier remains open for 5 seconds
* 🚧 Barrier closes automatically
* 🔴 Red LED turns ON again

If the RFID card is not authorized:

* ❌ Access is denied
* 🔴 Red LED remains ON
* 🚧 Barrier stays closed
* 🔴 Red LED flashes three times as an indication of an invalid card

This project demonstrates how several independent hardware components can work together to create a practical embedded system.

```text
                    🚗 VEHICLE
                       │
                       ▼
                📡 HC-SR04
                       │
                  Distance ≤ 10 cm?
                       │
                       ▼
              🔐 "Scan RFID Card"
                       │
                       ▼
                 📇 RFID Card
                       │
                       ▼
              📡 MFRC522 Reader
                       │
                  SPI Communication
                       │
                       ▼
                  🧠 Arduino
                       │
                 🔍 Check UID
                 ┌─────┴─────┐
                 ▼           ▼
             ✅ Correct    ❌ Wrong
                 │           │
                 ▼           ▼
             🟢 Green      🔴 Red
                 │           │
                 ▼           ▼
          🚧 Open Barrier  🚧 Stay Closed
                 │
                 ▼
              ⏱️ 5 Seconds
                 │
                 ▼
          🚧 Close Barrier
```

---

# 🧩 Main Components

This project uses five main hardware components:

| Component          | Purpose                              |
| ------------------ | ------------------------------------ |
| 📡 **HC-SR04**     | Detects the presence of a vehicle    |
| 🔐 **MFRC522**     | Reads RFID cards                     |
| ⚙️ **Servo Motor** | Opens and closes the parking barrier |
| 🟢🔴 **LEDs**      | Show access status                   |
| 🧠 **Arduino Uno** | Controls the entire system           |

The project also uses two different communication/power concepts:

* 🛰️ **SPI** → Arduino ↔ MFRC522
* 📏 **Pulse timing** → Arduino ↔ HC-SR04

---

# 🚗 How the Smart Parking System Works

The system starts in the **locked / unavailable state**.

```text
🔴 RED LED → ON
🟢 GREEN LED → OFF
🚧 Barrier → CLOSED
```

The Arduino continuously measures the distance between the ultrasonic sensor and the object in front of it.

```cpp
long dist = getDistance();
```

If the measured distance is:

```text
0 < distance ≤ 10 cm
```

the Arduino considers a vehicle to be present.

It then prints:

```text
Vehicle detected! Scan RFID card...
```

The system now waits for an RFID card.

---

# 📡 Step 1 — Vehicle Detection with HC-SR04

The **HC-SR04 ultrasonic sensor** is responsible for detecting the vehicle.

It contains two important parts:

* 📤 **Transmitter (TRIG)** → sends an ultrasonic pulse
* 📥 **Receiver (ECHO)** → detects the returning pulse

The sensor works by measuring the time required for sound to travel to an object and return.

```text
        🔊 Ultrasonic Pulse
             ─────────────►
📡 HC-SR04                  🚗 Vehicle
             ◄─────────────
                Echo
```

The Arduino calculates the distance using:

```cpp
distance = duration * 0.034 / 2;
```

### Why `0.034`?

The approximate speed of sound is:

```text
343 m/s
```

which is approximately:

```text
0.034 cm/µs
```

The division by `2` is necessary because the measured time represents:

```text
Sensor → Vehicle
       +
Vehicle → Sensor
```

We only want the one-way distance.

Therefore:

```text
Distance = Time × Speed of Sound ÷ 2
```

---

# 📏 Vehicle Detection Limit

This project uses:

```cpp
if (dist > 0 && dist <= 10)
```

Therefore, a vehicle is considered detected when it is **10 cm or closer** to the sensor.

```text
📡 Sensor
   │
   │  10 cm
   ▼
🚗 Vehicle
```

> 💡 **Important:** The 10 cm value is a project-specific threshold. In a real parking system, this value would depend on the physical placement of the sensor, entrance design, and vehicle size.

---

# 🔐 Step 2 — RFID Authentication

After detecting a vehicle, the Arduino waits for an RFID card.

The RFID system consists of:

* 📇 RFID card/key fob
* 📡 MFRC522 reader
* 🧠 Arduino

The MFRC522 reads the card's **UID (Unique Identifier)**.

Example:

```text
90 3F F9 55
```

The program stores the authorized UID:

```cpp
if (content.substring(1) == "90 3F F9 55")
```

Only a card with this UID is accepted.

---

# 📡 MFRC522 and SPI Communication

The MFRC522 communicates with the Arduino using **SPI (Serial Peripheral Interface)**.

In this project:

```text
🧠 Arduino Uno = SPI Master
📡 MFRC522     = SPI Slave
```

The main SPI communication lines are:

| SPI Signal | Arduino Uno | MFRC522 |
| ---------- | ----------: | ------- |
| MOSI       |          11 | MOSI    |
| MISO       |          12 | MISO    |
| SCK        |          13 | SCK     |
| SS / SDA   |          10 | SDA/SS  |

The RFID module also uses:

| MFRC522 Pin | Arduino  |
| ----------- | -------- |
| RST         | 9        |
| VCC         | **3.3V** |
| GND         | GND      |

---

# ⚡ Why the RFID Reader Uses 3.3V

This is especially important.

The **MFRC522 operates at 3.3V**.

Therefore, in this project the RFID reader is powered from:

```text
Arduino 3.3V → MFRC522 VCC
Arduino GND  → MFRC522 GND
```

⚠️ **Do not power the MFRC522 directly from the Arduino's 5V pin.**

The module is designed for a lower voltage supply, and applying 5V can damage the reader.

```text
Arduino
┌─────────────┐
│ 3.3V ───────┼──────► 📡 MFRC522 VCC
│ GND ────────┼──────► 📡 MFRC522 GND
│              │
│ Pin 10 ─────┼──────► SS
│ Pin 11 ─────┼──────► MOSI
│ Pin 12 ─────┼──────► MISO
│ Pin 13 ─────┼──────► SCK
│ Pin 9 ──────┼──────► RST
└─────────────┘
```

---

# 📚 RFID Libraries

Two libraries are required:

```cpp
#include <SPI.h>
#include <MFRC522.h>
```

### 🛰️ `SPI.h`

`SPI.h` is Arduino's built-in SPI library.

It provides access to the Arduino's hardware SPI peripheral.

The project initializes it using:

```cpp
SPI.begin();
```

This prepares the Arduino to communicate with the MFRC522.

---

### 📡 `MFRC522.h`

The `MFRC522` library provides higher-level functions for controlling the RFID reader.

For example:

```cpp
mfrc522.PCD_Init();
```

initializes the MFRC522.

The program checks for a new card using:

```cpp
mfrc522.PICC_IsNewCardPresent()
```

and reads the card using:

```cpp
mfrc522.PICC_ReadCardSerial()
```

After communication is finished:

```cpp
mfrc522.PICC_HaltA();
mfrc522.PCD_StopCrypto1();
```

These commands stop communication with the current card and prepare the reader for future operations.

---

# 📇 UID Authentication

After the RFID card is detected, the program extracts every byte of its UID.

```cpp
for (byte i = 0; i < mfrc522.uid.size; i++)
```

Each byte is converted to hexadecimal and added to a string.

For example:

```text
90
3F
F9
55
```

becomes:

```text
90 3F F9 55
```

The program then converts the result to uppercase:

```cpp
content.toUpperCase();
```

Finally, it compares the scanned UID with the authorized UID.

```text
             📇 RFID Card
                   │
                   ▼
             Read UID
                   │
                   ▼
            "90 3F F9 55"
                   │
             🔍 Compare
             ┌─────┴─────┐
             ▼           ▼
          MATCH        NO MATCH
             │             │
             ▼             ▼
          ✅ Allow       ❌ Deny
```

> 🔐 **Security Note:** This project uses the UID as a simple identification mechanism. UID-only authentication is suitable for learning and simple demonstrations, but it should not be considered strong security for a real access-control system because some RFID systems can have cloneable or changeable identifiers.

---

# 🚧 Step 3 — Servo Motor Barrier

The servo motor represents the physical parking barrier.

The servo is initialized with:

```cpp
barrier.attach(SERVO_PIN);
```

The barrier starts closed:

```cpp
barrier.write(0);
```

When the correct RFID card is detected:

```cpp
barrier.write(90);
```

The servo rotates to 90°.

```text
🔒 CLOSED
   0°
   │
   │  Authorized RFID
   ▼
🚧 OPEN
   90°
```

After five seconds:

```cpp
delay(5000);
barrier.write(0);
```

The barrier returns to its closed position.

---

# 🔋 Why the Servo Uses a Separate Battery

The servo in this project is powered using:

```text
🔋 4 × AA batteries
1.5V × 4 = 6V
```

instead of taking its power directly from the Arduino.

This is important because a servo can require significantly more current while:

* ⚙️ Starting movement
* 🚧 Moving the barrier
* 🧱 Working against mechanical resistance
* 🔄 Changing direction
* 🛑 Holding a load

The Arduino's 5V rail is not always capable of safely supplying the required current.

If the servo draws too much current from the Arduino, you may experience:

* 🔄 Servo jitter
* 🔌 Arduino resets
* 💡 LEDs flickering
* 📡 RFID communication problems
* ⚠️ Unstable behavior

Using a separate power source gives the servo the current it needs.

> ⚠️ **Important:** If the servo uses an external battery supply, the external supply's **GND should be connected to Arduino GND** so the control signal has a common reference.

```text
        🧠 Arduino
           │
           │ PWM Signal
           ▼
       ⚙️ Servo
           ▲
           │
      🔋 4 × AA
       6V Supply
           │
           └────── GND ────── Arduino GND
```

> 💡 **Note:** The exact acceptable servo voltage depends on the specific servo model. A 4×AA pack can be around 6V with fresh alkaline cells, so always verify that your servo is rated for that voltage.

---

# 🟢🔴 Step 4 — LED Status System

Two LEDs provide the current access status.

### 🔴 Red LED

The red LED represents:

```text
🚫 ACCESS DENIED
🔒 Barrier CLOSED
```

At startup:

```cpp
digitalWrite(RED_LED, HIGH);
digitalWrite(GREEN_LED, LOW);
```

The parking entrance therefore starts in the locked state.

---

### 🟢 Green LED

The green LED represents:

```text
✅ ACCESS GRANTED
🚧 Barrier OPEN
```

When an authorized card is scanned:

```cpp
digitalWrite(RED_LED, LOW);
digitalWrite(GREEN_LED, HIGH);
```

The green LED remains on while the barrier is open.

After five seconds, the system returns to:

```text
🔴 RED → ON
🟢 GREEN → OFF
🚧 BARRIER → CLOSED
```

---

# ❌ Unauthorized Card

If the UID doesn't match:

```cpp
else {
```

the barrier is **not opened**.

The red LED flashes three times:

```cpp
for (int i = 0; i < 3; i++)
```

The sequence is:

```text
🔴 OFF → 🔴 ON
   200ms

🔴 OFF → 🔴 ON
   200ms

🔴 OFF → 🔴 ON
   200ms
```

This gives the driver a clear visual indication that the card was rejected.

---

# 🧠 `vehicleDetected` Variable

The project uses:

```cpp
bool vehicleDetected = false;
```

This variable keeps track of whether the system has already detected a vehicle.

When a vehicle first enters the detection area:

```cpp
if (!vehicleDetected) {
    Serial.println(F("Vehicle detected! Scan RFID card..."));
    vehicleDetected = true;
}
```

The message is therefore printed only once instead of continuously printing it every loop.

When the vehicle leaves:

```cpp
vehicleDetected = false;
```

the system resets and becomes ready for the next vehicle.

```text
🚗 Vehicle Arrives
       │
       ▼
vehicleDetected = true
       │
       ▼
🔐 Scan Card
       │
       ▼
🚗 Vehicle Leaves
       │
       ▼
vehicleDetected = false
       │
       ▼
🔄 Ready for Next Vehicle
```

---

# 🔄 Complete System Sequence

The entire project follows this sequence:

### 1️⃣ Waiting

```text
🔴 Red LED ON
🟢 Green LED OFF
🚧 Barrier CLOSED
```

### 2️⃣ Vehicle Arrives

```text
📡 HC-SR04
Distance ≤ 10 cm
```

### 3️⃣ RFID Authentication

```text
📇 Scan Card
       ↓
📡 MFRC522
       ↓
🛰️ SPI
       ↓
🧠 Arduino
```

### 4️⃣ Authorized Card

```text
✅ UID MATCH

🟢 Green LED ON
🔴 Red LED OFF
🚧 Servo → 90°
```

### 5️⃣ Five Seconds Later

```text
⏱️ 5 seconds

🚧 Servo → 0°
🟢 Green LED OFF
🔴 Red LED ON
```

### 6️⃣ Unauthorized Card

```text
❌ UID DOES NOT MATCH

🔴 Red LED flashes ×3
🚧 Barrier remains CLOSED
```

---

# 🔌 Complete Pin Configuration

## 📡 MFRC522

| MFRC522  | Arduino Uno | Purpose           |
| -------- | ----------: | ----------------- |
| SDA / SS |          10 | SPI Slave Select  |
| SCK      |          13 | SPI Clock         |
| MOSI     |          11 | Arduino → MFRC522 |
| MISO     |          12 | MFRC522 → Arduino |
| RST      |           9 | Reset             |
| 3.3V     |        3.3V | Power             |
| GND      |         GND | Ground            |

---

## 📏 HC-SR04

| HC-SR04 | Arduino | Purpose       |
| ------- | ------: | ------------- |
| VCC     |      5V | Power         |
| GND     |     GND | Ground        |
| TRIG    |       2 | Trigger pulse |
| ECHO    |       3 | Echo signal   |

---

## 🚧 Servo

| Servo  | Connection                    |
| ------ | ----------------------------- |
| Signal | Arduino Pin 4                 |
| VCC    | 🔋 External 6V supply         |
| GND    | 🔋 External GND + Arduino GND |

---

## 💡 LEDs

| Component    | Arduino |
| ------------ | ------: |
| 🔴 Red LED   |   Pin 6 |
| 🟢 Green LED |   Pin 5 |

> ⚠️ Use an appropriate current-limiting resistor, typically around **220–330 Ω**, in series with each LED.

---

# 🔋 Power Architecture

One of the important lessons in this project is that **not every component should necessarily be powered from the same source**.

```text
                    🧠 Arduino
                 ┌─────┼─────┐
                 │     │     │
                3.3V   5V   GND
                 │     │     │
                 ▼     ▼     │
              📡 RFID  📏 HC-SR04
                             │
                             │
                     Common Ground
                             │
                             ▼
                    🔋 External 6V
                             │
                             ▼
                         ⚙️ Servo
```

### ⚡ Power Summary

| Component  | Power                          |
| ---------- | ------------------------------ |
| 🧠 Arduino | Main Arduino supply            |
| 📡 MFRC522 | **3.3V**                       |
| 📏 HC-SR04 | **5V**                         |
| 💡 LEDs    | Arduino GPIO through resistors |
| ⚙️ Servo   | **External 4×AA ≈ 6V supply**  |

This separation helps prevent the servo's high-current movement from disturbing sensitive electronics such as the RFID reader.

---

# 🧩 Why This Project Is More Advanced

Previous projects focused on individual components:

```text
🎛️ Rotary Encoder
📡 RFID
📏 Ultrasonic Sensor
⚙️ Servo
💡 LEDs
```

This project combines them into one coordinated system.

Each component has a different role:

```text
📏 HC-SR04
   ↓
"Is there a vehicle?"

📡 MFRC522
   ↓
"Who is the driver?"

🧠 Arduino
   ↓
"Should access be allowed?"

⚙️ Servo
   ↓
"Open or close the barrier."

🟢🔴 LEDs
   ↓
"Show the current status."
```

This is closer to how real embedded systems are designed: **multiple sensors and actuators working together under the control of one microcontroller**.

---

# 📚 Main Libraries

### 🛰️ `SPI.h`

Provides communication between the Arduino and MFRC522 through the Arduino Uno's hardware SPI interface.

```cpp
#include <SPI.h>
```

---

### 📡 `MFRC522.h`

Provides high-level functions for controlling the RFID reader.

```cpp
#include <MFRC522.h>
```

---

### ⚙️ `Servo.h`

Provides functions for controlling the servo motor.

```cpp
#include <Servo.h>
```

The most important functions used here are:

```cpp
barrier.attach(4);
barrier.write(0);
barrier.write(90);
```

---

# 🧠 Important Functions

### 📏 `getDistance()`

This custom function handles the complete HC-SR04 measurement process.

```cpp
long getDistance()
```

It:

1. Sends a trigger pulse.
2. Waits for the echo.
3. Measures the echo duration.
4. Converts the duration to distance.
5. Returns the distance in centimeters.

This keeps the main `loop()` cleaner.

---

### 📡 `PICC_IsNewCardPresent()`

Checks whether a new RFID card is available.

```cpp
mfrc522.PICC_IsNewCardPresent()
```

---

### 📇 `PICC_ReadCardSerial()`

Reads the card's UID.

```cpp
mfrc522.PICC_ReadCardSerial()
```

---

### 🚧 `barrier.write()`

Controls the servo position.

```cpp
barrier.write(0);   // Closed
barrier.write(90);  // Open
```

---

# 💡 Important Practical Notes

> ⚠️ **Sensor readings can vary.** The HC-SR04's measured distance may fluctuate depending on the object's shape, angle, surface, environmental conditions, and sensor placement.

> ⚠️ **Servo power requirements vary.** The 4×AA battery setup is specific to this project. Always check the voltage range and current requirements of your particular servo.

> ⚠️ **MFRC522 uses 3.3V.** Keep its power supply at 3.3V and use appropriate voltage-level considerations when connecting it to a 5V Arduino.

> 💡 **RFID range is limited.** The MFRC522 is designed for short-range RFID communication. The exact reading distance depends on the card, antenna, orientation, and surrounding environment.

> 🔐 **UID authentication is for learning.** Comparing a UID is a simple way to build an RFID access demo, but a production access-control system would need stronger authentication and additional security measures.

---

# 🚀 Possible Improvements

This project could be developed into a much more complete parking system.

### 🅿️ Multiple Parking Spaces

Add several HC-SR04 sensors:

```text
🚗 Space 1 → 📡
🚗 Space 2 → 📡
🚗 Space 3 → 📡
🚗 Space 4 → 📡
```

The Arduino could determine which parking spaces are occupied.

---

### 📺 LCD Display

Add an LCD to display:

```text
🅿️ SMART PARKING

Spaces: 3 / 5
Scan Your Card
```

---

### 🔐 Multiple RFID Cards

Instead of one UID, store several authorized cards:

```text
👤 User 1 → Authorized
👤 User 2 → Authorized
👤 User 3 → Authorized
```

---

### 💾 EEPROM Storage

Store authorized RFID UIDs in EEPROM so they remain saved even after the Arduino loses power.

---

### 🌐 Internet Connectivity

With an ESP8266/ESP32, the system could:

* 📊 Track parking occupancy
* 📱 Send notifications
* ☁️ Store entry logs
* 🕒 Record entry and exit times
* 👤 Identify users

---

# 📌 What You'll Learn

After completing this project, you'll understand:

* 🚗 How to detect a vehicle using an ultrasonic sensor.
* 📏 How HC-SR04 calculates distance using sound.
* 📡 How RFID readers communicate with cards.
* 🛰️ How SPI hardware communication works.
* 🔐 How an RFID UID can be used for basic authentication.
* ⚙️ How to control a servo as a mechanical actuator.
* 🔋 Why high-current components may require external power.
* 💡 How LEDs can provide system status feedback.
* 🧠 How multiple hardware modules can work together.
* 🔄 How sensors, decision-making logic, and actuators form a complete embedded system.

---

# 🏁 Final Project Flow

```text
                    🚗 VEHICLE ARRIVES
                           │
                           ▼
                     📏 HC-SR04
                           │
                     Distance ≤ 10 cm?
                           │
                           ▼
                  🔐 Scan RFID Card
                           │
                           ▼
                    📡 MFRC522
                           │
                           ▼
                    🛰️ SPI Protocol
                           │
                           ▼
                     🧠 Arduino
                           │
                     🔍 Check UID
                           │
                ┌──────────┴──────────┐
                │                     │
             ✅ MATCH              ❌ WRONG
                │                     │
                ▼                     ▼
          🟢 Green LED          🔴 Red LED
                │                     │
                ▼                     ▼
          🚧 Servo 90°          🚧 Stay Closed
                │
                ▼
             ⏱️ 5 sec
                │
                ▼
          🚧 Servo 0°
                │
                ▼
        🔴 Red LED ON
                │
                ▼
             🅿️ READY
```

---

# 🎯 Project Summary

**Arduino Project 32** brings together several important concepts from the previous projects into one practical application.

Instead of simply controlling one component, the Arduino now acts as the **central controller of a complete automated system**:

```text
📏 SENSOR
   ↓
📥 INPUT
   ↓
🧠 PROCESSING
   ↓
🔐 AUTHENTICATION
   ↓
⚙️ ACTUATOR
   ↓
💡 FEEDBACK
```

The result is a miniature **Smart Parking Access System** where the Arduino detects a vehicle, authenticates its RFID card, controls a physical barrier, and communicates the system status through LEDs.
