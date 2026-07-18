# Arduino Project 7: Light-Dependent LED Indicator 🌞💡

This project demonstrates how a **photoresistor** can be used to detect the amount of light in the environment and control LEDs based on the detected light level.

The Arduino reads the photoresistor's analog value and uses it to determine whether the environment is bright or dark.

```text id="8a2r3k"
🌞 Bright Environment
        ↓
  Photoresistor
        ↓
   Arduino Reads
   Light Level
        ↓
   ┌─────────────┐
   │ Light > 50? │
   └─────────────┘
      ↙       ↘
    YES        NO
     ↓          ↓
🟢 Green ON  🔴 Red ON
```

## How It Works

The photoresistor is connected to analog pin **A5**.

The Arduino continuously reads the light level:

```text id="3q5z8h"
Light Value
    0 ───────────────────► Higher Value
 Dark Environment          Bright Environment
```

The program checks whether the value is greater than `50`:

```cpp id="7h2m4k"
if (lightVal > 50)
```

### If the Light Value Is Greater Than 50

```text id="e8p1c4"
lightVal > 50
     ↓
🟢 Green LED ON
🔴 Red LED OFF
```

### If the Light Value Is 50 or Less

```text id="n6v3s9"
lightVal <= 50
      ↓
🔴 Red LED ON
🟢 Green LED OFF
```

The light value is also displayed in the **Serial Monitor**.

## What Is a Photoresistor?

A **photoresistor**, also called an **LDR (Light-Dependent Resistor)**, is a component whose resistance changes depending on the amount of light it receives.

```text
More Light  → Lower Resistance
Less Light  → Higher Resistance
```

Because its resistance changes with light, the voltage in the circuit also changes. The Arduino can read this changing voltage using an analog input.

```text id="r2f6k8"
        Light
          ↓
   🌞 ──────────
          ↓
   Photoresistor
          ↓
   Changing Voltage
          ↓
      Arduino
          ↓
    Analog Value
```

## Photoresistor Behavior

```text
🌞 More Light
      ↓
Lower Resistance
      ↓
Different Voltage
      ↓
Arduino Reads Value
```

```text
🌙 Less Light
      ↓
Higher Resistance
      ↓
Different Voltage
      ↓
Arduino Reads Value
```

The exact values depend on the photoresistor and the circuit configuration.

## Components

* Arduino board
* Photoresistor (LDR)
* Green LED
* Red LED
* Resistors
* Breadboard
* Jumper wires

## Key Components & Functions

### 🌞 Photoresistor (LDR)

Detects changes in the surrounding light level by changing its resistance.

### 🟢 Green LED

Indicates that the detected light value is greater than the threshold.

### 🔴 Red LED

Indicates that the detected light value is at or below the threshold.

### 🧠 Arduino

Reads the analog light value and controls the LEDs based on an `if-else` condition.

### 🖥️ Serial Monitor

Displays the current photoresistor value in real time.

## Concepts Demonstrated

* Photoresistors and light detection
* Analog input using `analogRead()`
* Digital output using `digitalWrite()`
* `if-else` conditional logic
* Threshold-based control
* Serial communication
* Using sensors to interact with the physical environment

> Light changes resistance. Resistance changes voltage. Voltage changes behavior. 🌞⚡
