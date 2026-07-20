# Arduino Project 12: Pushbutton-Controlled Stepper Motor 🔘⚙️

This project demonstrates how a **pushbutton 🔘** can be used to change the rotation direction of a **stepper motor ⚙️**.

Each time the button is pressed, the stepper motor switches between:

```text id="n5k2x8"
🔘 Press 1 → ⚙️ Rotate Forward ➡️
🔘 Press 2 → ⚙️ Rotate Backward ⬅️
🔘 Press 3 → ⚙️ Rotate Forward ➡️
🔘 Press 4 → ⚙️ Rotate Backward ⬅️
              ↻ Repeat
```

The project uses a **28BYJ-48 stepper motor** with a suitable driver module.

## How It Works

The pushbutton is connected to digital pin **2**.

The stepper motor is controlled using the `Stepper` library.

```text id="r8m3q6"
🔘 Pushbutton
      ↓
🧠 Arduino Detects Press
      ↓
🔄 Change Direction
      ↓
⚙️ Stepper Motor Rotates
```

The direction is controlled by the variable:

```cpp id="v4p9s2"
state
```

The value of `state` is either:

```text id="j6k2x1"
state =  1  →  ➡️ Forward
state = -1  →  ⬅️ Backward
```

When the button is pressed:

```cpp id="c8m5n7"
state = -state;
```

This changes:

```text id="a3r7q9"
 1  →  -1
-1  →   1
```

Therefore, every button press reverses the motor's direction.


A **stepper motor ⚙️** is an electric motor that rotates in precise, small increments called **steps**.

Unlike a regular DC motor, which generally rotates continuously when powered, a stepper motor can be instructed to move a specific number of steps.

```text id="w2k8f5"
⚡ Electrical Pulses
        ↓
   🧲 Coils Activate
        ↓
   ⚙️ Rotor Moves
        ↓
    One Step
```

By activating the motor's coils in a specific sequence, the Arduino can control the motor's movement.

## Stepper Motor Components

A stepper motor typically contains:

### 🧲 Coils

Electromagnetic coils create magnetic fields when electricity flows through them.

```text id="p7s4m1"
Coil A → 🧲
Coil B → 🧲
Coil C → 🧲
Coil D → 🧲
```

The coils are energized in a sequence to make the rotor move.

### ⚙️ Rotor

The rotor is the rotating part of the motor.

It responds to the magnetic fields created by the energized coils.

### 🧲 Permanent Magnet

The rotor of many stepper motors contains a permanent magnet that interacts with the magnetic fields produced by the coils.

### 🔩 Gears

The **28BYJ-48** commonly includes internal gears.

These gears:

* Increase the output torque
* Reduce the output speed
* Allow more precise output movement

## What Is the Stepper Motor Driver?

The Arduino usually should not directly power the motor coils.

A stepper motor driver module is used between the Arduino and the motor.

```text id="e9m2s6"
🧠 Arduino
     │
     ▼
🎛️ Stepper Driver
     │
     ▼
⚙️ Stepper Motor
```

The driver receives control signals from the Arduino and supplies the required current to the motor coils.

## Steps Per Revolution

The code defines:

```cpp id="k5q8v3"
int stepsPerRevolutions = 2048;
```

This tells the `Stepper` library the number of steps required for approximately one full revolution of the motor.

```text id="u7x4n9"
2048 Steps
     ↓
🔄 Approximately
One Revolution
```

The exact number of steps per revolution can vary depending on the motor, gear ratio, stepping mode, and library configuration.

## Setting the Motor Speed

The motor speed is set using:

```cpp id="f3m6p1"
myStepper.setSpeed(speed);
```

In this project:

```cpp id="s8k2r5"
speed = 12
```

The `Stepper` library uses this value to control the motor's speed in revolutions per minute.

```text id="q4n7x9"
Lower Speed  → 🐢 Slower Rotation
Higher Speed → ⚡ Faster Rotation
```

## Moving the Stepper Motor

The motor is moved using:

```cpp id="m2v5c8"
myStepper.step(state);
```

The value determines both the number of steps and the direction:

```text id="b6p9s3"
step( 1)  → ➡️ One Step Forward
step(-1)  → ⬅️ One Step Backward
```

Because this command runs repeatedly inside `loop()`, the motor continuously rotates in the selected direction.

## Button State Logic

The button uses the following logic:

```text id="h3k7m2"
🔘 Not Pressed → HIGH
🔘 Pressed     → LOW
```

The program compares the current button value with the previous value:

```cpp id="x9q4f6"
if(buttonVal != buttonOld)
```

This helps detect a change in the button state.

When the button is pressed:

```text id="n8w2s5"
🔘 Button Press
      ↓
  buttonVal = LOW
      ↓
🔄 Reverse Direction
      ↓
state = -state
```

## Button Debouncing

The code includes:

```cpp id="r6m1p8"
delay(dt);
```

with:

```cpp id="v3k9x4"
dt = 100;
```

Mechanical buttons can produce rapid unwanted electrical transitions when pressed. This is known as **button bouncing**.

```text id="j5q8c2"
🔘 Press
   ↓
⚡ HIGH → LOW → HIGH → LOW
   ↓
✅ Stable Signal
```

The short delay helps prevent a single press from being interpreted as multiple presses.

## Project Logic

```text id="a7f3k9"
        🔘 Press Button
              ↓
      📥 Read Button Value
              ↓
       Has State Changed?
              ↓
            YES
              ↓
      🔄 Reverse Direction
              ↓
        state = -state
              ↓
       ⚙️ Stepper Rotates
```

The motor continues rotating in the selected direction until the button is pressed again.

## Components

* 🧠 Arduino board
* ⚙️ 28BYJ-48 stepper motor
* 🎛️ Stepper motor driver module
* 🔘 Pushbutton
* 🧩 Breadboard
* 🔌 Jumper wires

## Key Components & Functions

### 🔘 Pushbutton

Changes the direction of the stepper motor when pressed.

### ⚙️ Stepper Motor

Moves in precise steps and can rotate in either direction.

### 🎛️ Stepper Driver

Controls the motor coils and allows the Arduino to control the stepper motor safely.

### 📚 `Stepper` Library

Provides functions for controlling the stepper motor:

```cpp
Stepper(...)
```

Creates a stepper motor object.

```cpp
myStepper.setSpeed(speed);
```

Sets the motor speed.

```cpp
myStepper.step(steps);
```

Moves the motor a specified number of steps.

### 🔄 State Variable

Stores the current motor direction:

```text
 1 → ➡️ Forward
-1 → ⬅️ Backward
```

## Concepts Demonstrated

* ⚙️ Stepper motor control
* 📚 Using the `Stepper` library
* 🔘 Pushbutton input
* 🔄 Changing motor direction
* 🧲 Electromagnetic coil sequencing
* 🪜 Step-based motor movement
* ⚡ Motor speed control
* 🛡️ Button debouncing
* 🧠 State variables
* 🔁 Comparing current and previous button values

> 🔘 One button press changes the direction. ⚙️ The stepper motor follows one precise step at a time. 🔄

