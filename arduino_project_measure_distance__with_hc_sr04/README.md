# Arduino Project 19: Ultrasonic Distance Measurement 📏🔊

This project demonstrates how to measure the distance between an **Arduino 🧠** and an object using an **HC-SR04 ultrasonic distance sensor 📡**.

The sensor sends an ultrasonic sound wave and measures how long it takes for the echo to return.

```text
🧠 Arduino
    │
    ▼
📡 HC-SR04
    │
    │ 🔊 Ultrasonic Sound Wave
    ▼
   🧱 Object
    │
    │ ↩️ Echo Returns
    ▼
📡 HC-SR04
    │
    ▼
🧠 Arduino Calculates Distance
```

The measured distance is then sent to the **Serial Monitor 💻**.

```text
Distance, Upper Limit, Lower Limit
```

Example:

```text
15.42,30.00,2.00
```

## How the Project Works

The project uses two main pins:

```text
Arduino Pin 10 → TRIG
Arduino Pin 9  → ECHO
```

The complete process is:

```text
🔔 Send Trigger Pulse
        ↓
📡 Sensor Sends Ultrasonic Wave
        ↓
🧱 Wave Hits Object
        ↓
↩️ Echo Returns
        ↓
⏱️ Measure Travel Time
        ↓
📏 Calculate Distance
        ↓
💻 Print Result
```

## What Is an Ultrasonic Sensor? 📡

An ultrasonic sensor measures distance using **sound waves with a frequency higher than humans can hear**.

The HC-SR04 has two main parts:

```text
┌─────────────────────────┐
│  🔊 Transmitter  📥 Receiver │
└─────────────────────────┘
```

### 🔊 Transmitter

Sends an ultrasonic sound wave toward an object.

### 📥 Receiver

Detects the sound wave when it returns as an echo.

```text
📡 Sensor
   │
   │ 🔊 Sound Wave
   ▼
🧱 Object
   │
   │ ↩️ Echo
   ▼
📡 Sensor
```

The Arduino calculates the distance based on the time between sending and receiving the sound wave.

## HC-SR04 Pins

The HC-SR04 normally has four pins:

```text
VCC    → Power
TRIG   → Sends the measurement signal
ECHO   → Receives the returned signal
GND    → Ground
```

In this project:

```text
TRIG → Arduino Pin 10
ECHO → Arduino Pin 9
```

```text
🧠 Arduino
   │
   ├── Pin 10 ─────► TRIG
   └── Pin 9  ◄───── ECHO
```

## The Trigger Signal 🔔

The Arduino starts a measurement by sending a short pulse to the trigger pin.

The code first sets the pin LOW:

```cpp
digitalWrite(triggerPin, LOW);
```

Then sends a HIGH pulse:

```cpp
digitalWrite(triggerPin, HIGH);
delayMicroseconds(10);
```

Finally, it returns the pin to LOW:

```cpp
digitalWrite(triggerPin, LOW);
```

The complete sequence is:

```text
LOW
 ↓
HIGH for 10 microseconds
 ↓
LOW
```

```text
🔔 Trigger Pulse
      ↓
📡 Sensor Sends Ultrasonic Wave
```

This tells the HC-SR04 to begin a distance measurement.

## Measuring the Echo ⏱️

After the ultrasonic wave is sent, the Arduino waits for the echo:

```cpp
duration = pulseIn(echoPin, HIGH);
```

The `pulseIn()` function measures how long the echo pin stays HIGH.

```text
📡 Wave Sent
      ↓
⏱️ Timer Starts
      ↓
🧱 Wave Hits Object
      ↓
↩️ Echo Returns
      ↓
⏱️ Timer Stops
```

The result is stored in:

```cpp
float duration;
```

The duration is measured in:

```text
microseconds (μs)
```

## Calculating the Distance 📏

The project uses:

```cpp
distance = duration * 0.034 / 2;
```

This formula is based on the speed of sound.

The speed of sound is approximately:

```text
0.034 cm/μs
```

The basic calculation is:

```text
Distance = Time × Speed
```

However, the ultrasonic wave travels:

```text
Sensor → Object
      +
Object → Sensor
```

Therefore, the measured time represents a **round trip**.

The distance must be divided by `2`:

```text
Distance = (Duration × Speed of Sound) / 2
```

So the code uses:

```text
distance = duration × 0.034 / 2
```

## Example Calculation

Suppose:

```text
Duration = 1000 μs
```

Then:

```text
Distance = 1000 × 0.034 / 2
```

```text
Distance = 17 cm
```

The result:

```text
📏 Object is approximately 17 cm away
```

## Why Are `float` Variables Used?

The project uses:

```cpp
float duration;
float distance;
```

A `float` can store decimal values:

```text
15.42 cm
23.75 cm
2.34 cm
```

This allows the sensor to provide more precise distance measurements than an integer.

## Distance Limits 📏

The project defines two distance limits:

```cpp
float upperLimit = 30.0;
float lowerLimit = 2.0;
```

These represent:

```text
Upper Limit → 30 cm
Lower Limit → 2 cm
```

```text
2 cm ─────────────── 30 cm
🔴                  🟢
Lower              Upper
Limit              Limit
```

Currently, these values are printed to the Serial Monitor along with the measured distance.

Example:

```text
15.42,30.00,2.00
```

This format can be useful later for:

* 📊 Serial Plotter visualization
* 📈 Graphing distance
* 🚨 Distance limit detection
* 💡 LED indicators
* 🔊 Buzzer alarms

## Serial Monitor Output 💻

The program prints:

```cpp
Serial.print(distance);
Serial.print(",");
Serial.print(upperLimit);
Serial.print(",");
Serial.println(lowerLimit);
```

The output format is:

```text
Distance, Upper Limit, Lower Limit
```

Example:

```text
15.42,30.00,2.00
16.10,30.00,2.00
16.05,30.00,2.00
```

This format is especially useful with the **Serial Plotter 📈**, where the three values can be visualized as separate lines.

```text
📈 Distance
───────────────
30 cm ───────────── Upper Limit
        ╱╲
       ╱  ╲
      ╱    ╲
 2 cm ───────────── Lower Limit
```

## Measurement Frequency ⏱️

The project uses:

```cpp
int dt = 200;
```

and:

```cpp
delay(dt);
```

This means the Arduino waits:

```text
200 milliseconds
      ↓
0.2 seconds
```

between measurements.

```text
📏 Measure
    ↓
💻 Print
    ↓
⏳ Wait 0.2 sec
    ↓
🔄 Measure Again
```

This creates approximately:

```text
5 measurements per second
```

under normal conditions.

## Complete Project Flow

```text
       🔔 Trigger
          ↓
    📡 Send Sound Wave
          ↓
        🧱 Object
          ↓
      ↩️ Echo Returns
          ↓
     ⏱️ Measure Time
          ↓
      🧮 Calculate
          ↓
      📏 Distance
          ↓
       💻 Serial
          ↓
       ⏳ Wait
          ↓
         🔄 Repeat
```

## Example

If an object is located approximately:

```text
📏 15 cm
```

from the sensor, the Serial Monitor may display:

```text
15.00,30.00,2.00
```

The values may slightly change:

```text
14.85,30.00,2.00
15.12,30.00,2.00
15.30,30.00,2.00
```

This is normal because ultrasonic measurements can be affected by the environment.

## Important Note About Distance Readings ⚠️

The measured values may vary depending on:

* 🧱 Object material
* 📐 Object angle
* 📏 Distance from the sensor
* 🌬️ Air conditions
* 🔊 Environmental noise
* 📡 Sensor positioning
* ⚡ Power stability

For example, a flat object facing directly toward the sensor usually provides a stronger echo than an object positioned at an angle.

```text
Good Reflection:

📡 ─────────► 🧱
    ◄─────────

Weaker Reflection:

📡 ─────────► ╱
             ↗
```

Therefore, the exact readings can change depending on the conditions of the experiment.

## Components

* 🧠 Arduino board
* 📡 HC-SR04 ultrasonic sensor
* 🧱 Test objects
* 🧱 Breadboard
* 🔌 Jumper wires
* 💻 Computer with Serial Monitor

## Key Components & Functions

### 📡 HC-SR04

Measures distance using ultrasonic sound waves.

### 🔔 Trigger Pin

Starts the distance measurement.

### 📥 Echo Pin

Receives the returning ultrasonic signal.

### `pulseIn()`

Measures the duration of a HIGH signal.

### `delayMicroseconds()`

Creates a very short delay measured in microseconds.

### `float`

Stores decimal values such as:

```text
15.42
```

### `Serial.print()`

Sends data to the Serial Monitor or Serial Plotter.

## Concepts Demonstrated

* 📡 Ultrasonic distance measurement
* 🔊 Sound wave reflection
* ⏱️ Measuring time
* 📏 Distance calculation
* `pulseIn()`
* `delayMicroseconds()`
* `float` variables
* Serial Monitor output
* Serial Plotter-compatible data
* Upper and lower distance limits
* Periodic sensor readings

> 📡 Send the wave. ⏱️ Measure the echo. 🧮 Calculate the time. 📏 Know the distance.
