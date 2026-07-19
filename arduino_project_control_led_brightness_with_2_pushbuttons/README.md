# Arduino Project 9: Two-Button LED Brightness Control 🔘💡

This project demonstrates how two pushbuttons can be used to control the brightness of an LED.

One button increases the brightness, while the other decreases it.

```text id="q7m2x8"
🔘 Button 1
     │
     ▼
💡 Increase Brightness

🔘 Button 2
     │
     ▼
🌑 Decrease Brightness
```

The LED brightness is controlled using **PWM (Pulse Width Modulation)**.

## How It Works

The two pushbuttons are connected to:

```text id="m5k9r1"
🔘 Button 1 → Pin 7
🔘 Button 2 → Pin 6
```

The LED is connected to:

```text id="v3p8c6"
💡 LED → Pin 9
```

The Arduino reads both button states and changes the brightness value stored in:

```cpp id="w6h2n9"
state
```

The brightness value ranges from:

```text id="z4f7s2"
🌑 0   ─────────────────►   255 💡
OFF                         Maximum Brightness
```

## Brightness Control

### 🔘 Button 1 — Increase Brightness

When Button 1 is pressed:

```text id="j8q3m5"
🔘 Button 1
      ↓
state += 15
      ↓
💡 LED Gets Brighter
```

Example:

```text id="4k2v7p"
0 → 15 → 30 → 45 → ... → 255
```

The brightness cannot exceed `255`:

```cpp id="a5r9c2"
if(state > 255) state = 255;
```

---

### 🔘 Button 2 — Decrease Brightness

When Button 2 is pressed:

```text id="n7x4b1"
🔘 Button 2
      ↓
state -= 15
      ↓
🌑 LED Gets Dimmer
```

Example:

```text id="h3p8s6"
255 → 240 → 225 → 210 → ... → 0
```

The brightness cannot go below `0`:

```cpp id="f6w2k9"
if(state < 0) state = 0;
```

## What Is PWM?

**PWM (Pulse Width Modulation)** is a technique used to control the average power delivered to a component.

The Arduino rapidly switches the LED ON and OFF:

```text id="r5m1q8"
HIGH  ────┐    ┌────    ┌────
          │    │        │
LOW       └────┘        └────
```

By changing how long the signal stays HIGH, the Arduino changes the LED's apparent brightness.

This is called the **duty cycle**.

```text id="c9v3k7"
0% Duty Cycle    → 🌑 LED OFF
50% Duty Cycle   → 💡 Medium Brightness
100% Duty Cycle  → 🔆 Maximum Brightness
```

In this project, the brightness is controlled using:

```cpp id="p2s6n4"
analogWrite(ledPin, state);
```

The value of `state` determines the brightness.

## Brightness Range

```text id="e7k1m5"
state = 0
    ↓
🌑 LED OFF

state = 127
    ↓
💡 Medium Brightness

state = 255
    ↓
🔆 Maximum Brightness
```

The brightness increases or decreases in steps of **15**.

## Project Logic

```text id="u8q4r2"
        🔘 Button 1
             │
             ▼
      Increase state by 15
             │
             ▼
         💡 Brighter
             
             
        🔘 Button 2
             │
             ▼
      Decrease state by 15
             │
             ▼
          🌑 Dimmer
```

The current button values and brightness state are displayed in the **Serial Monitor**:

```text id="y6n3p9"
Button 1    Button 2    Brightness
   1           1            0
   0           1           15
   1           0            0
```

## Components

* 🧠 Arduino board
* 🔘 2 Pushbuttons
* 💡 LED
* 🧱 Resistor
* 🧩 Breadboard
* 🔌 Jumper wires

## Key Components & Functions

### 🔘 Pushbuttons

Control whether the LED brightness should increase or decrease.

### 💡 LED

Changes brightness based on the PWM value received from the Arduino.

### 🧠 Arduino

Reads the button inputs and updates the LED brightness.

### ⚡ PWM

Controls the LED's brightness using values from `0` to `255`.

### 🖥️ Serial Monitor

Displays the button states and current brightness value.

## Concepts Demonstrated

* 🔘 Multiple digital inputs
* 💡 PWM brightness control
* `analogWrite()`
* `digitalRead()`
* Incrementing and decrementing values
* Limiting values between `0` and `255`
* Conditional statements
* Serial communication

> 🔘 One button adds light. One button takes it away. You control the brightness. 💡⚡
