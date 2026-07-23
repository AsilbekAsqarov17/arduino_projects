# Arduino Project 20: Push-to-Measure Ultrasonic Distance Meter 📏🔘📟

This project demonstrates how to build a simple **distance measuring device 📏** using:

* 📡 HC-SR04 Ultrasonic Sensor
* 🔘 Pushbutton
* 📟 16×2 LCD
* 🧠 Arduino

Unlike the previous ultrasonic distance project, which continuously measured distance, this project measures the distance **only when the user presses the button**.

```text id="q7m3x8"
🧱 Place Target
      ↓
🔘 Press Button
      ↓
📡 Measure Distance
      ↓
🧮 Calculate Distance
      ↓
📟 Display Result
```

Example:

```text id="m5r8k2"
Place the Target
Press to measure
```

After pressing the button:

```text id="v3p9q6"
Target Distance:
25.43 cm
```

## How the Project Works

The project combines three main parts:

```text id="x8k2m4"
🔘 Pushbutton
      ↓
🧠 Arduino
      ↓
📡 HC-SR04
      ↓
📏 Distance Calculation
      ↓
📟 LCD Display
```

The user first places an object in front of the ultrasonic sensor.

The LCD displays:

```text id="n6p4r9"
Place the Target
Press to measure
```

The Arduino waits until the button is pressed.

After the button is pressed:

```text id="a3m8q1"
🔘 Button Press
      ↓
📡 Send Ultrasonic Pulse
      ↓
↩️ Receive Echo
      ↓
📏 Calculate Distance
      ↓
📟 Display Measurement
```

## LCD Pin Connections 📟

The 16×2 LCD is connected using:

```text id="k5x7p2"
LCD Pin      Arduino Pin
────────────────────────
RS      →       12
E       →       11
D4      →       10
D5      →       9
D6      →       8
D7      →       7
```

The LCD is initialized using:

```cpp id="r4m9q6"
LiquidCrystal lcd(rs, e, d4, d5, d6, d7);
```

The display is configured as:

```cpp id="v7n2k8"
lcd.begin(16, 2);
```

This means:

```text id="q2v7m4"
16 Columns
    ×
2 Rows
```

## HC-SR04 Pin Connections 📡

The ultrasonic sensor uses:

```text id="a8m5r2"
HC-SR04       Arduino
──────────────────────
TRIG      →      5
ECHO      →      4
```

The trigger pin sends the ultrasonic signal:

```text id="w5p9k3"
triggerPin = 5
```

The echo pin receives the reflected signal:

```text id="m7x2q8"
echoPin = 4
```

```text id="c4n8v1"
📡 HC-SR04
   │
   ├── 🔔 TRIG → Arduino Pin 5
   └── 📥 ECHO → Arduino Pin 4
```

## The Pushbutton 🔘

The pushbutton is connected to:

```cpp id="r3m6p9"
int buttonPin = 2;
```

The project uses:

```cpp id="x8q2k5"
pinMode(buttonPin, INPUT_PULLUP);
```

### What Is `INPUT_PULLUP`?

Arduino provides an internal pull-up resistor.

This means the button normally reads:

```text id="v6m3p8"
Button Not Pressed → HIGH
Button Pressed     → LOW
```

```text id="k9p4x2"
        Not Pressed
             ↓
        HIGH (1)

🔘 Press Button
             ↓

         LOW (0)
```

Therefore, the program waits while:

```cpp id="r7x2m6"
buttonVal == 1
```

When the button is pressed:

```text id="p3k8q5"
buttonVal == 0
      ↓
Measurement Starts
```

## Waiting for the Button Press ⏳

The program first reads the button:

```cpp id="a9m4v1"
buttonVal = digitalRead(buttonPin);
```

Then it waits:

```cpp id="x6p2q8"
while(buttonVal == 1) {
  buttonVal = digitalRead(buttonPin);
}
```

The program remains inside this loop until the button is pressed.

```text id="m8r3k5"
Button = HIGH?
      │
      ├── Yes → ⏳ Keep Waiting
      │
      └── No → 📏 Measure Distance
```

This creates a simple user-controlled measurement system.

## Displaying the Instructions 📟

Before measuring, the LCD is cleared:

```cpp id="p9m2x6"
lcd.clear();
```

The first line displays:

```cpp id="c7k4r8"
lcd.print("Place the Target");
```

The second line displays:

```cpp id="j5q2x9"
lcd.print("Press to measure");
```

The LCD shows:

```text id="a6m9p4"
┌────────────────┐
│ Place the Target│
│ Press to measure│
└────────────────┘
```

The actual text may be limited by the LCD's 16-character width, so longer messages may not fit perfectly on one row.

## Starting the Ultrasonic Measurement 📡

After the button is pressed, the Arduino sends a trigger pulse.

First:

```cpp id="v3n8m1"
digitalWrite(triggerPin, LOW);
delayMicroseconds(2);
```

Then:

```cpp id="s5p8k2"
digitalWrite(triggerPin, HIGH);
delayMicroseconds(10);
```

Finally:

```cpp id="q6m4r8"
digitalWrite(triggerPin, LOW);
```

The sequence is:

```text id="n8x3p5"
LOW
 ↓
HIGH for 10 μs
 ↓
LOW
```

This tells the HC-SR04 to send an ultrasonic sound wave.

```text id="m4q7k2"
📡 Sensor
   │
   ▼
🔊 Ultrasonic Wave
   │
   ▼
🧱 Target
   │
   ▼
↩️ Echo Returns
```

## Measuring the Echo ⏱️

The Arduino measures the time taken for the echo to return:

```cpp id="r9m2v6"
duration = pulseIn(echoPin, HIGH);
```

The measured time is stored in:

```cpp id="x5k8p3"
float duration;
```

The duration is measured in microseconds.

```text id="a7m4q9"
📡 Send Wave
      ↓
⏱️ Start Timer
      ↓
🧱 Hit Target
      ↓
↩️ Echo Returns
      ↓
⏱️ Stop Timer
```

## Calculating the Distance 📏

The project uses:

```cpp id="j2p6x8"
distance = duration * 0.034 / 2;
```

The formula is:

```text id="v4n8m2"
Distance = Duration × Speed of Sound ÷ 2
```

The value:

```text id="q3m7x5"
0.034 cm/μs
```

represents the approximate speed of sound.

The division by `2` is necessary because the sound travels:

```text id="k8p2r6"
Sensor → Target
      +
Target → Sensor
```

The measured time represents the entire round trip.

```text id="s9m4v1"
Total Distance
     ↓
Sensor → Target → Sensor
     ↓
Divide by 2
     ↓
Actual Distance
```

## Displaying the Distance 📟

After the measurement is complete, the LCD is cleared:

```cpp id="n5x8q2"
lcd.clear();
```

The first row displays:

```cpp id="c4m7p9"
lcd.print("Target Distance:");
```

The second row displays the measured value:

```cpp id="r2k6v8"
lcd.print(distance);
lcd.print(" sm");
```

Example:

```text id="j7m3x5"
┌────────────────┐
│ Target Distance│
│ 25.43 cm       │
└────────────────┘
```

> **Note:** The code uses `"sm"` as the unit text. If you are using centimeters, `"cm"` would be the standard abbreviation.

## Complete Project Flow

```text id="p8q4m1"
        🧠 Arduino
            ↓
      📟 Display Prompt
            ↓
    "Place the Target"
            ↓
    "Press to measure"
            ↓
        ⏳ Wait
            ↓
        🔘 Button
        Pressed?
            ↓
      📡 Send Trigger
            ↓
       🔊 Sound Wave
            ↓
        🧱 Target
            ↓
        ↩️ Echo
            ↓
      ⏱️ Measure Time
            ↓
      🧮 Calculate
            ↓
       📏 Distance
            ↓
      📟 LCD Display
```

## Example

Suppose the target is approximately:

```text id="v6n2k9"
📏 25 cm
```

from the ultrasonic sensor.

The user:

```text id="a5m8q3"
1️⃣ Places the target
2️⃣ Presses the button
3️⃣ Arduino measures the echo
4️⃣ Arduino calculates the distance
5️⃣ LCD displays the result
```

Example output:

```text id="k2r7m4"
Target Distance:
25.43 cm
```

After the measurement is displayed for:

```cpp id="x8m3p6"
int dt = 5000;
```

the Arduino waits:

```text id="j4n6w8"
5000 milliseconds
      ↓
5 seconds
```

Then the program starts the process again.

## Why This Project Is Different

The previous ultrasonic project measured distance continuously:

```text id="m7p3x9"
📡 Measure
   ↓
📏 Display
   ↓
⏳ Wait
   ↓
🔄 Repeat
```

This project uses a button:

```text id="q5k8r2"
🔘 Press Button
      ↓
📡 Measure Once
      ↓
📟 Display Result
```

This makes the project more similar to a simple handheld measuring device.

## Components

* 🧠 Arduino board
* 📡 HC-SR04 ultrasonic sensor
* 📟 16×2 LCD
* 🔘 Pushbutton
* 🧱 Breadboard
* 🔌 Jumper wires
* 💻 Computer for programming

## Key Components & Functions

### 📡 HC-SR04

Measures distance using ultrasonic sound waves.

### 🔘 Pushbutton

Starts the measurement when pressed.

### 📟 16×2 LCD

Displays instructions and the measured distance.

### `INPUT_PULLUP`

Uses Arduino's internal pull-up resistor.

```text id="n4m8q2"
Not Pressed → HIGH
Pressed     → LOW
```

### `pulseIn()`

Measures the duration of the returning echo signal.

### `delayMicroseconds()`

Creates precise delays measured in microseconds.

### `lcd.clear()`

Clears the LCD screen.

### `lcd.setCursor()`

Sets the position where text will be displayed.

### `lcd.print()`

Displays text and values on the LCD.

## Concepts Demonstrated

* 📏 Ultrasonic distance measurement
* 🔘 Pushbutton-controlled actions
* 📟 LCD displays
* 📡 HC-SR04 sensor
* `INPUT_PULLUP`
* `digitalRead()`
* `digitalWrite()`
* `pulseIn()`
* `delayMicroseconds()`
* `lcd.clear()`
* `lcd.setCursor()`
* `lcd.print()`
* Distance calculation
* User-controlled sensor measurements

> 🔘 Press the button. 📡 Send the wave. ⏱️ Measure the echo. 📟 See the distance.
