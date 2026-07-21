# Arduino Project 15: Two-Button DC Motor Speed & Direction Control 🔘⚙️

This project demonstrates how **two pushbuttons 🔘** can be used to control both the **speed** and **direction** of a **DC motor ⚙️** through an **L293D motor driver 🎛️**.

```text id="k3v7p2"
🔘 Button 1
     ↓
⬆️ Increase Speed
     ↓
➡️ Forward Rotation

🔘 Button 2
     ↓
⬇️ Decrease Speed
     ↓
⬅️ Reverse Rotation
```

The motor speed is changed in steps of **15**, allowing gradual control instead of immediately switching between OFF and maximum speed.

```text id="a8m4q9"
0 → 15 → 30 → 45 → ... → 255
```

The motor can also rotate in the opposite direction:

```text id="n6p2x5"
0 → -15 → -30 → -45 → ... → -255
```

## How the Project Works

The project uses:

```text id="q5r8m1"
🔘 Button 1 → Pin 9
🔘 Button 2 → Pin 8

🎛️ L293D:
Enable → Pin 5
Input 1 → Pin 4
Input 2 → Pin 3
```

The complete control flow is:

```text id="w7k2p4"
       🔘 Buttons
           ↓
    🧠 Arduino Reads Input
           ↓
     🔄 Change Speed Value
           ↓
      Determine Direction
           ↓
        🎛️ L293D
           ↓
        ⚙️ DC Motor
```

## Button Controls

### 🔘 Button 1 — Forward / Increase Speed

When Button 1 is pressed:

```text id="x3m9q6"
🔘 Button 1
      ↓
  speed += 15
      ↓
⬆️ Speed Increases
      ↓
➡️ Motor Moves Forward
```

Example:

```text id="v5p2n8"
0 → 15 → 30 → 45 → 60 → ...
```

The speed cannot exceed the maximum PWM value:

```text id="r8k4s1"
+255
```

---

### 🔘 Button 2 — Reverse / Decrease Speed

When Button 2 is pressed:

```text id="j6q3m9"
🔘 Button 2
      ↓
  speed -= 15
      ↓
⬇️ Speed Value Decreases
      ↓
⬅️ Motor Moves Reverse
```

Example:

```text id="c4x7p2"
0 → -15 → -30 → -45 → -60 → ...
```

The minimum value is:

```text id="m9v2k5"
-255
```

## The `speed` Variable

One of the main ideas in this project is using a **signed speed variable**.

```text id="s7n3q8"
Positive Value  → ➡️ Forward
Negative Value  → ⬅️ Reverse
Zero            → 🛑 Stop
```

```text id="f2k8r4"
 speed =  255 → 🚀 Maximum Forward
 speed =   90 → ⚡ Slow Forward
 speed =    0 → 🛑 Stopped
 speed =  -90 → ⚡ Slow Reverse
 speed = -255 → 🚀 Maximum Reverse
```

This allows one variable to store both:

```text id="p5m1x7"
⚡ Speed
+
🔄 Direction
```

## Why Is `abs(speed)` Used?

When the motor is moving in reverse:

```text id="z8q4n2"
speed = -90
```

The negative sign represents the direction.

However, PWM values must be positive:

```text id="h3v7k9"
analogWrite(enablePin, 90);
```

Therefore, the code uses:

```cpp id="b6m2r8"
analogWrite(enablePin, abs(speed));
```

The `abs()` function converts:

```text id="d4p9x1"
-90  →  90
-255 → 255
```

The direction is controlled separately using the L293D input pins.

```text id="q7k3m5"
⚡ Speed  → Enable Pin
🔄 Direction → Input 1 + Input 2
```

## Motor Direction Control

The L293D uses two input pins to control the motor direction.

```text id="n5r8v2"
Input 1   Input 2   Motor
  LOW       LOW     🛑 Stop
  HIGH      LOW     ➡️ Forward
  LOW       HIGH    ⬅️ Reverse
  HIGH      HIGH    🛑 Stop
```

### Forward

```cpp id="m8q2x6"
digitalWrite(input1Pin, HIGH);
digitalWrite(input2Pin, LOW);
```

```text id="t4k9p3"
🎛️ L293D
   ↓
➡️ DC Motor
```

### Reverse

```cpp id="v6n3s8"
digitalWrite(input1Pin, LOW);
digitalWrite(input2Pin, HIGH);
```

```text id="r2x7m5"
🎛️ L293D
   ↓
⬅️ DC Motor
```

### Stop

```cpp id="c9p4k1"
digitalWrite(input1Pin, LOW);
digitalWrite(input2Pin, LOW);
```

```text id="j5m8q2"
🛑 Motor Stops
```

## Speed Control Using PWM ⚡

The L293D's Enable pin is connected to Arduino pin **5**.

The motor speed is controlled using:

```cpp id="f7x3n9"
analogWrite(enablePin, speed);
```

For reverse rotation:

```cpp id="a2k6r8"
analogWrite(enablePin, abs(speed));
```

The PWM range is:

```text id="w4m9p2"
0 ───────────────────► 255
OFF                    Maximum Speed
```

In this project, the speed changes in steps of:

```text id="s8q3v6"
stepSize = 15
```

```text id="h2m7x9"
🛑 0
 ↓
15
 ↓
30
 ↓
45
 ↓
...
 ↓
255 🚀
```

The motor does not instantly jump to maximum speed. Instead, the buttons gradually change the PWM value.

## Motor Start Logic

The project uses:

```cpp id="n6r2k8"
bool wasStopped = (speed == 0);
```

This checks whether the motor was previously stopped.

When the motor starts moving from zero:

```text id="p3v8m1"
🛑 Motor Stopped
       ↓
🔘 Button Press
       ↓
⚡ Start Motor
       ↓
🎛️ L293D
       ↓
⚙️ Motor Begins Rotating
```

The code briefly applies maximum PWM:

```cpp id="q9m4x7"
analogWrite(enablePin, 255);
delay(200);
```

This gives the motor an initial boost to overcome the force required to start rotating.

After that, the motor continues using the calculated speed value.

## What Is the L293D? 🎛️⚙️

The **L293D** is a motor driver IC that allows an Arduino to control DC motors.

The Arduino provides control signals, while the L293D handles the larger current required by the motor.

```text id="u5k2r8"
🧠 Arduino
    │
    │ Direction + PWM
    ▼
🎛️ L293D
    │
    │ Motor Power
    ▼
⚙️ DC Motor
```

The L293D contains two H-bridge circuits and can control two DC motors independently.

This project uses one motor channel.

## L293D Connections

```text id="m7x3q9"
Arduino Pin 5 → Enable Pin
Arduino Pin 4 → Input 1
Arduino Pin 3 → Input 2
```

The L293D receives:

```text id="k4p8v2"
🔄 Direction Signals
        +
⚡ PWM Speed Signal
```

and uses them to control the motor.

## What Is a DC Motor? ⚙️

A DC motor converts electrical energy into rotational motion.

```text id="r6m1x8"
⚡ Electrical Energy
        ↓
🧲 Magnetic Fields
        ↓
⚙️ Rotor
        ↓
🔄 Rotation
```

A DC motor can be controlled by changing:

* 🔄 Direction
* ⚡ Speed
* 🛑 ON/OFF state

This project controls all three:

```text id="a9q5n3"
🔘 Button 1 → Forward + Increase Speed
🔘 Button 2 → Reverse + Decrease Speed
🛑 speed = 0 → Stop
```

## Both Buttons Pressed

The code contains:

```cpp id="v8k2m6"
if(button1Val == 0 && button2Val == 0) {
}
```

When both buttons are pressed simultaneously:

```text id="x3p7r9"
🔘 Button 1 + 🔘 Button 2
            ↓
       No Speed Change
```

The current motor state remains unchanged.

This prevents both speed controls from being activated at the same time.

## Complete Project Logic

```text id="n4m8q2"
          🔘 Button 1
               │
               ▼
        Increase speed by 15
               │
               ▼
          Positive Value
               │
               ▼
          ➡️ Forward


          🔘 Button 2
               │
               ▼
        Decrease speed by 15
               │
               ▼
          Negative Value
               │
               ▼
          ⬅️ Reverse
```

The complete motor control:

```text id="j7x2k5"
              🧠 Arduino
                  │
        ┌─────────┴─────────┐
        │                   │
   🔄 Direction         ⚡ PWM Speed
        │                   │
        └─────────┬─────────┘
                  ↓
             🎛️ L293D
                  ↓
              ⚙️ DC Motor
```

## Serial Monitor Output

The project displays:

```text id="p5r8m3"
Button 1: 1
Button 2: 0
Forward!
15
```

or:

```text id="c6q2v9"
Button 1: 0
Button 2: 1
Reverse!
-15
```

When the motor is stopped:

```text id="m8x4k1"
Not Spinning!!!
0
```

This makes it possible to monitor:

* 🔘 Button states
* 🔄 Motor direction
* ⚡ Current speed value

## Components

* 🧠 Arduino board
* 🔘 2 Pushbuttons
* 🎛️ L293D motor driver
* ⚙️ DC motor
* 🧩 Breadboard
* 🔌 Jumper wires
* 🔋 Suitable motor power supply

## Key Components & Functions

### 🔘 Pushbuttons

Control the motor's speed and direction.

### 🎛️ L293D

Drives the DC motor and controls its direction and speed.

### ⚙️ DC Motor

Rotates forward or backward based on the input signals.

### ⚡ PWM

Controls the motor speed using values from `0` to `255`.

### 🔄 Signed Speed Variable

Stores both speed and direction:

```text
Positive → ➡️ Forward
Negative → ⬅️ Reverse
Zero     → 🛑 Stop
```

### 🛡️ Speed Limiting

Prevents the PWM value from exceeding the valid range:

```text
-255 ≤ speed ≤ 255
```

## Concepts Demonstrated

* 🔘 Multiple pushbutton inputs
* ⚙️ DC motor control
* 🎛️ L293D motor driver
* 🔄 Forward and reverse rotation
* ⚡ PWM speed control
* 📈 Incrementing values
* 📉 Decrementing values
* 🧠 Signed variables
* `abs()`
* `analogWrite()`
* `digitalWrite()`
* Conditional logic
* 🛑 Motor state tracking
* 🔋 Motor power control

> 🔘 Two buttons. One motor. Speed and direction under your control. ⚙️⚡
