# Arduino Project 5: Potentiometer-Controlled Buzzer 🔊🎛️

This project demonstrates how a potentiometer can be used to control a buzzer based on an analog input value.

The Arduino continuously reads the potentiometer value and activates the buzzer when the value reaches a defined threshold.

## How It Works

```text
🎛️ Potentiometer
       ↓
  Analog Input
   0 → 1023
       ↓
   Arduino
       ↓
  Check Value
       ↓
   potVal ≥ 1000?
     ↙         ↘
   YES          NO
    ↓            ↓
🔊 Buzzer ON   🔇 Buzzer OFF
```

The buzzer is activated when:

```text
potVal >= 1000
```

If the potentiometer value is below `1000`, the buzzer remains turned off.

The current potentiometer value is also displayed in the **Serial Monitor**.

## What Is a Potentiometer?

A **potentiometer** is a variable resistor that can provide an adjustable voltage.

When the knob is rotated, the voltage sent to the Arduino's analog input changes. The Arduino reads this voltage as a value between:

```text
0  ───────────────────────►  1023
Minimum                     Maximum
```

In this project, the potentiometer acts as an adjustable control for the buzzer.

## What Is a Buzzer?

A **buzzer** is an electronic component that produces sound when it receives an electrical signal.

There are two common types of buzzers:

### 🔊 Active Buzzer

An **active buzzer** contains a built-in oscillator.

It only needs a simple HIGH or LOW signal to produce a sound:

```text
Arduino HIGH
     ↓
🔊 Active Buzzer
     ↓
   Sound
```

In this project, the active buzzer can be controlled using:

```cpp
digitalWrite(buzzPin, HIGH);
```

### 🎵 Passive Buzzer

A **passive buzzer** does not contain a built-in oscillator.

It requires a changing electrical signal, usually a specific frequency, to produce different sounds or tones.

For example:

```cpp
tone(buzzPin, 1000);
```

The frequency can be changed to create different pitches.

```text
Frequency ↑  →  Higher Pitch
Frequency ↓  →  Lower Pitch
```

## Project Logic

```text
🎛️ Rotate Potentiometer
          ↓
  Arduino Reads Value
          ↓
    Is Value ≥ 1000?
       ↙        ↘
     YES         NO
      ↓           ↓
🔊 Sound ON    🔇 Sound OFF
```

## Components

* Arduino board
* Potentiometer
* Buzzer
* Breadboard
* Jumper wires

## Key Components & Functions

### 🎛️ Potentiometer

Provides a variable analog input that can be adjusted by rotating the knob.

### 🔊 Buzzer

Produces sound when the potentiometer value reaches the defined threshold.

### 🧠 Arduino

Reads the analog input and makes a decision using an `if-else` condition.

### 🖥️ Serial Monitor

Displays the current potentiometer value in real time.

## Concepts Demonstrated

* Analog input using `analogRead()`
* Digital output control using `digitalWrite()`
* `if-else` conditional statements
* Threshold-based control
* Serial communication
* Active and passive buzzers
* Potentiometer input

> Turn the knob. Reach the threshold. Trigger the sound. 🎛️🔊
