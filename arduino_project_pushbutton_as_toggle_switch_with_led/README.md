# Arduino Project 8: Pushbutton Toggle Switch 🔘💡

This project demonstrates how a **pushbutton 🔘** can be used as a toggle switch to control an LED 💡.

Unlike a normal button-controlled LED, where the LED is ON only while the button is being pressed, this project allows each button press to change the LED's state:

```text
🔘 Press 1  →  💡 LED ON
🔘 Press 2  →  🌑 LED OFF
🔘 Press 3  →  💡 LED ON
🔘 Press 4  →  🌑 LED OFF
              ↻ Repeat
```

## How It Works

The pushbutton 🔘 is connected to digital pin **12**, while the LED 💡 is connected to digital pin **8**.

The Arduino continuously reads the button state:

```text
       🔘
   Pushbutton
       │
       ▼
  📥 Digital Input
       │
       ▼
    🧠 Arduino
       │
       ▼
🔄 Detect Button Change
       │
       ▼
  💡 Toggle LED
```

## Button State Logic

The button in this project uses:

```text
🔘 Not Pressed  →  HIGH
🔘 Pressed      →  LOW
```

When the button state changes to `LOW`, the Arduino detects a button press and changes the LED state.

```text
🔘 Button Press
       │
       ▼
   val == LOW
       │
       ▼
  🔄 Check State
    ↙       ↘
  OFF       ON
   │         │
   ▼         ▼
💡 ON      🌑 OFF
```

## What Is a Pushbutton?

A **pushbutton 🔘** is a momentary switch. It changes its electrical state while being pressed and returns to its normal state when released.

```text
🖐️ Not Pressed → Normal State
       │
       ▼
🔘 Pressed → Changed State
       │
       ▼
↩️ Released → Returns to Normal
```

The Arduino reads the button's state using:

```cpp
digitalRead(buttonPin);
```

## Software Toggle Logic

The variable `state` stores the current LED state:

```text
state = 0  →  🌑 LED OFF
state = 1  →  💡 LED ON
```

When the button is pressed:

```text
🔘 Press
   │
   ▼
state == 0?
   │
   ▼
💡 Turn LED ON
   │
   ▼
state = 1
```

On the next press:

```text
🔘 Press
   │
   ▼
state == 1?
   │
   ▼
🌑 Turn LED OFF
   │
   ▼
state = 0
```

This creates a toggle effect using a momentary pushbutton.

## Why Is `old_val` Used?

The Arduino's `loop()` function runs repeatedly and very quickly.

Without comparing the current and previous button values, a single press could potentially be detected multiple times.

```text
📥 Current Value
       │
       ▼
   ⚖️ Compare
       ▲
       │
📦 Previous Value
       │
       ▼
🔄 Has the button state changed?
```

The code checks:

```cpp
if (val != old_val)
```

If the values are different, the button state has changed.

After checking the button:

```cpp
old_val = val;
```

The current value becomes the previous value for the next loop.

## Button Debouncing

The code includes:

```cpp
delay(50);
```

This helps reduce the effects of **button bouncing**.

When a physical button is pressed, its internal contacts may rapidly switch between HIGH and LOW for a short period before settling.

```text
🔘 Press
   ↓
⚡ HIGH → LOW → HIGH → LOW
   ↓
✅ Stable LOW
```

Without debouncing, the Arduino might interpret one physical press as multiple presses.

The 50 ms delay gives the signal time to stabilize.

## Components

* 🧠 Arduino board
* 🔘 Pushbutton
* 💡 LED
* 🧱 Resistor
* 🧩 Breadboard
* 🔌 Jumper wires

## Key Components & Functions

### 🔘 Pushbutton

Provides a digital input that changes state when pressed.

### 💡 LED

Indicates the current toggle state.

### 🧠 Arduino

Detects button state changes and controls the LED.

### 🔄 State Variable

Stores whether the LED is currently ON or OFF.

### 🖥️ Serial Monitor

Displays the current button value for observation and debugging.

## Concepts Demonstrated

* 📥 Digital input using `digitalRead()`
* 💡 Digital output using `digitalWrite()`
* 🔘 Pushbutton state detection
* ⚖️ Current and previous value comparison
* 🔄 Toggle logic
* 🧠 State variables
* 🛡️ Button debouncing
* 🔀 `if-else` conditional statements

> 🔘 One press. One state change. A simple pushbutton becomes a switch. ⚡
