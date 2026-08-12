# 🎵 Audio Visualizer — 8×8 MAX7219 LED Matrix & Sound Sensor

## 📌 Project Overview

This project creates a simple **real-time audio visualizer** using an **8×8 LED matrix controlled by the MAX7219** and a **microphone/sound sensor**.

The microphone detects changes in sound intensity, Arduino analyzes the signal, and the LED matrix displays the detected sound level as a moving bar graph.

The louder the detected sound, the higher the bars become.

```text
🎤 Sound Sensor
      ↓
  Analog Signal
      ↓
   Arduino
      ↓
Sound Analysis
      ↓
  MAX7219 Driver
      ↓
  8×8 LED Matrix
      ↓
📊 Visual Sound Level
```

This project introduces two important components:

* 🎤 **Microphone / Sound Sensor** — converts sound into an electrical signal.
* 🔲 **MAX7219 8×8 LED Matrix** — controls an 8×8 matrix using only a few Arduino pins.

---

## 🧩 Components

| Component                    | Purpose                                       |
| ---------------------------- | --------------------------------------------- |
| 🔲 Arduino                   | Reads the microphone and controls the display |
| 🎤 Microphone / Sound Sensor | Detects sound intensity                       |
| 💡 8×8 LED Matrix            | Displays the audio level                      |
| 🔌 MAX7219                   | Drives the 8×8 LED matrix                     |
| 🔗 Jumper Wires              | Connections                                   |
| ⚡ Power Source               | Powers the circuit                            |

---

# 🎤 1. Microphone / Sound Sensor

A microphone sensor detects **changes in air pressure caused by sound waves**.

When someone speaks, claps, plays music, or makes another sound, the sound waves cause the microphone's diaphragm to vibrate.

The sensor converts these physical vibrations into an electrical signal.

In this project:

```cpp
const int MIC_PIN = A0;
```

The microphone output is connected to **A0**, allowing Arduino to read the signal using:

```cpp
analogRead(MIC_PIN);
```

### 🔢 Analog Signal

Arduino's `analogRead()` normally returns a value between:

```text
0 ─────────────── 1023
```

The exact values depend on the sensor and the sound level.

A microphone module does not simply produce:

```text
quiet = 0
loud  = 1023
```

Instead, the signal continuously moves up and down around a certain voltage.

For example:

```text
        /\       /\
       /  \     /  \
------/----\---/----\------
     /      \ /
```

A louder sound generally produces a larger variation in the signal.

---

# 📏 2. Measuring Sound Intensity

The program does not use only one `analogRead()` value.

Instead, it samples the microphone for **30 milliseconds**:

```cpp
unsigned long startMillis = millis();

while (millis() - startMillis < 30) {
  int sample = analogRead(MIC_PIN);

  if (sample > signalMax) signalMax = sample;
  if (sample < signalMin) signalMin = sample;
}
```

During those 30 ms, the program finds:

* the highest microphone reading
* the lowest microphone reading

Then it calculates:

```cpp
int peakToPeak = signalMax - signalMin;
```

### 📊 Peak-to-Peak Value

This is the difference between the maximum and minimum signal.

For example:

```text
Maximum = 520
Minimum = 500

Peak-to-Peak = 520 - 500
             = 20
```

A louder sound may produce:

```text
Maximum = 600
Minimum = 400

Peak-to-Peak = 200
```

Therefore, the **peak-to-peak value is used as an approximate measurement of sound intensity**.

> ⚠️ This is not a calibrated measurement of sound pressure level in decibels (dB). It is a relative sound-level measurement based on the electrical output of the particular sensor.

---

# 🔇 3. Noise Floor

The project contains:

```cpp
const int NOISE_FLOOR = 14;
```

The microphone can produce small variations even when the environment appears quiet.

These variations can come from:

* 🎤 Sensor noise
* ⚡ Electrical noise
* 🏠 Background sounds
* 🔌 Power fluctuations

Without a threshold, the LED matrix could constantly display tiny bars.

Therefore:

```cpp
if (peakToPeak > NOISE_FLOOR)
```

means that the program ignores small signals.

In this project:

```text
Peak-to-Peak ≤ 14
        ↓
   Ignore signal
        ↓
     0 bars
```

while:

```text
Peak-to-Peak > 14
        ↓
   Process signal
        ↓
 Display bars
```

The value `14` is not a universal value. It was chosen for this particular setup and may need adjustment depending on the microphone module and environment.

---

# 🔲 4. 8×8 LED Matrix

The display contains:

```text
8 columns × 8 rows
```

giving a total of:

```text
8 × 8 = 64 LEDs
```

Conceptually:

```text
● ● ● ● ● ● ● ●
● ● ● ● ● ● ● ●
● ● ● ● ● ● ● ●
● ● ● ● ● ● ● ●
● ● ● ● ● ● ● ●
● ● ● ● ● ● ● ●
● ● ● ● ● ● ● ●
● ● ● ● ● ● ● ●
```

Each LED can be controlled as part of the matrix.

Instead of connecting all 64 LEDs directly to 64 Arduino pins, the project uses a **MAX7219 driver**.

---

# 🧠 5. MAX7219 LED Driver

The **MAX7219** is a dedicated display driver designed to control LED displays.

One of its major advantages is that Arduino does **not** need a separate control pin for every LED.

The MAX7219 receives display information from Arduino and handles the actual LED control.

For this project:

```cpp
LedControl lc = LedControl(DIN_PIN, CLK_PIN, CS_PIN, 1);
```

The final parameter:

```cpp
1
```

means that the program is controlling **one MAX7219 device**.

---

# 🔌 6. MAX7219 Communication

The MAX7219 module uses a serial communication interface based on three main signals:

| MAX7219 | Arduino | Purpose            |
| ------- | ------: | ------------------ |
| DIN     |      11 | Data input         |
| CLK     |      13 | Clock              |
| CS      |      10 | Chip Select / Load |
| VCC     |      5V | Power              |
| GND     |     GND | Ground             |

The project defines:

```cpp
const int DIN_PIN = 11;
const int CS_PIN  = 10;
const int CLK_PIN = 13;
```

### 📥 DIN — Data In

```text
Arduino → DIN → MAX7219
```

Carries the information that Arduino wants to send to the MAX7219.

### ⏱️ CLK — Clock

The clock synchronizes the transfer of data.

Each clock pulse tells the receiving device when to process the next bit of data.

### 🎯 CS — Chip Select

CS tells the MAX7219 when a data transmission is being sent.

---

# 📚 7. LedControl Library

The project uses:

```cpp
#include <LedControl.h>
```

The **LedControl** library makes working with MAX7219 displays much easier.

Without a library, you would have to manually implement the communication protocol and send the required control bytes yourself.

The library provides convenient functions such as:

### `shutdown()`

```cpp
lc.shutdown(0, false);
```

Enables the display.

The first parameter:

```cpp
0
```

is the device number.

The second parameter:

```cpp
false
```

means normal operation rather than shutdown mode.

---

### `setIntensity()`

```cpp
lc.setIntensity(0, 8);
```

Controls the display brightness.

The typical range is:

```text
0 ───── 15
```

Here:

```text
8
```

is selected as the brightness level.

---

### `clearDisplay()`

```cpp
lc.clearDisplay(0);
```

Turns all LEDs off.

---

### `setRow()`

```cpp
lc.setRow(0, row, 0xFF);
```

Sets all eight LEDs in a particular row.

`0xFF` in binary is:

```text
11111111
```

so all eight LEDs are turned on.

This is used during startup as a quick display test.

---

### `setColumn()`

The main visualization uses:

```cpp
lc.setColumn(0, col, columnBits);
```

This controls one complete column.

For example:

```text
00000001
```

lights one LED.

```text
00001111
```

lights four LEDs.

```text
11111111
```

lights all eight LEDs.

This is how the program creates the vertical bars.

---

# 📊 8. Converting Sound Into Bars

After calculating:

```cpp
peakToPeak
```

the project converts the value into a display height:

```cpp
barHeight = map(
  peakToPeak,
  NOISE_FLOOR + 1,
  45,
  1,
  8
);
```

The idea is:

```text
Sound Level             LED Height

Low     ────────────►      █
                        

Medium  ────────────►     ████


Loud    ────────────►     ████████
```

The `map()` function converts one numerical range into another.

Here:

```text
Input:
15 → 45

Output:
1 → 8
```

So a stronger microphone signal produces a larger bar.

Then:

```cpp
barHeight = constrain(barHeight, 0, 8);
```

makes sure the result cannot go below `0` or above `8`.

---

# 🕒 9. Creating the Moving Visualizer

The project doesn't simply display the current sound level.

It stores the previous eight measurements:

```cpp
static int history[8] = {0};
```

Think of it as:

```text
history[0] history[1] history[2] ... history[7]
    ↓          ↓          ↓              ↓
   Old       Old        Recent          New
```

Every new measurement shifts the previous values:

```cpp
for (int i = 0; i < 7; i++) {
  history[i] = history[i + 1];
}
```

Then the newest sound level is placed at the end:

```cpp
history[7] = barHeight;
```

This produces a scrolling effect across the eight columns.

For example:

```text
  █
  █       █
  █   █   █
  █   █   █   █
  █ █ █   █   █
  █ █ █ █ █ █ █
  █ █ █ █ █ █ █
  █ █ █ █ █ █ █
```

Each column represents a recent sound measurement.

This makes the display behave like a small **audio spectrum-style visualizer**, although it is measuring overall amplitude rather than separate frequency bands.

---

# 💻 10. Important Functions Used

### `analogRead()`

```cpp
analogRead(MIC_PIN);
```

Reads the microphone's analog voltage and converts it into an ADC value.

---

### `millis()`

```cpp
millis()
```

Returns the amount of time since Arduino started running the program.

It is used here to create a 30 ms sampling window without using a long blocking `delay()`.

---

### `map()`

```cpp
map(value, fromLow, fromHigh, toLow, toHigh);
```

Converts a value from one range to another.

---

### `constrain()`

```cpp
constrain(value, min, max);
```

Keeps a value inside a specified range.

---

### `setColumn()`

```cpp
lc.setColumn(0, col, columnBits);
```

Sends the calculated LED pattern to a particular matrix column.

---

# 🔄 Complete Working Process

The complete operation can be summarized as:

```text
        🎤 SOUND
           │
           ▼
    ┌──────────────┐
    │ Microphone   │
    │ Sound Sensor │
    └──────┬───────┘
           │
           │ Analog Signal
           ▼
    ┌──────────────┐
    │   Arduino    │
    │  analogRead  │
    └──────┬───────┘
           │
           ▼
    Find Maximum
           +
    Find Minimum
           │
           ▼
   Peak-to-Peak Value
           │
           ▼
     Noise Filter
           │
           ▼
      map() → 1–8
           │
           ▼
    Store in History
           │
           ▼
    ┌──────────────┐
    │   MAX7219    │
    └──────┬───────┘
           │
           ▼
    🔲 8×8 LED Matrix
           │
           ▼
     📊 Sound Bars
```

---

# 🧪 11. Startup Display Test

During startup, the project turns on every row:

```cpp
for (int row = 0; row < 8; row++) {
  lc.setRow(0, row, 0xFF);
}
```

This produces:

```text
████████
████████
████████
████████
████████
████████
████████
████████
```

After 300 ms:

```cpp
lc.clearDisplay(0);
```

turns everything off and the visualizer begins.

This is useful because it confirms that the LED matrix is working before the audio visualization starts.

---

# ⚙️ 12. Why MAX7219 Is Useful

Controlling a matrix directly can require many connections and more complicated multiplexing logic.

The MAX7219 handles much of this work internally.

Instead of Arduino directly managing every LED, the communication becomes:

```text
Arduino
   │
   │ Serial data
   ▼
MAX7219
   │
   ▼
8×8 LED Matrix
```

This reduces the number of Arduino pins required and makes the software significantly simpler.

---

# 🧠 What This Project Teaches

This project combines several important Arduino concepts:

* 🎤 Reading analog sensor data
* 📈 Measuring signal amplitude
* 🔇 Filtering background noise
* ⏱️ Sampling over a fixed time interval
* 🔢 Using `map()` and `constrain()`
* 💾 Maintaining historical sensor data
* 🔲 Controlling an 8×8 LED matrix
* 🔌 Communicating with an external display driver
* 📚 Using the `LedControl` library
* 🧠 Converting raw sensor data into a visual representation

---

## ⚠️ Calibration Note

The values:

```cpp
const int NOISE_FLOOR = 14;
```

and:

```cpp
map(peakToPeak, 15, 45, 1, 8);
```

are based on the behavior of the particular microphone and circuit used while building the project.

They are **not universal values**.

Different microphone modules, environments, power supplies, wiring, and even the physical position of the microphone can produce different readings.

For a different setup, you may need to adjust:

```cpp
NOISE_FLOOR
```

and the upper limit used by:

```cpp
map()
```

to obtain a useful visualization.

---

## 🎯 Final Result

The finished project turns sound into a simple visual display:

```text
Quiet
┌────────┐
│        │
│        │
│        │
│        │
│        │
│        │
│        │
│█       │
└────────┘


Loud
┌────────┐
│    █   │
│  █ █   │
│  █ █ █ │
│█ █ █ █ │
│█ █ █ █ │
│████████│
│████████│
│████████│
└────────┘
```

🎵 **Sound → Microphone → Arduino → MAX7219 → LED Matrix → Visualized Audio**
