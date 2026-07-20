# Arduino Project 14: Joystick-Controlled DC Motor 🕹️⚙️

This project demonstrates how a **joystick 🕹️** can be used to control both the **direction** and **speed** of a **DC motor ⚙️** through an **L293D motor driver 🎛️**.

The joystick's **Y-axis** controls the motor:

```text id="g7x2m9"
🕹️ Move Joystick Up
        ↓
   ➡️ Motor Forward
```

```text id="k4p8s3"
🕹️ Move Joystick Down
        ↓
   ⬅️ Motor Reverse
```

```text id="n6q3v1"
🕹️ Joystick Centered
        ↓
     🛑 Motor Stops
```

The farther the joystick is moved from the center, the faster the motor rotates.

```text id="a8r5c2"
Joystick Movement
       ↓
    📥 Y Value
       ↓
   🧮 Convert Value
       ↓
 ⚡ PWM Speed
       ↓
   🎛️ L293D
       ↓
   ⚙️ DC Motor
```

## How the Project Works

The joystick's Y-axis is connected to analog pin **A1**.

```text id="f3m8q6"
🕹️ Joystick
      │
      ▼
   Y-Axis
      │
      ▼
     A1
      │
      ▼
🧠 Arduino
```

The Arduino reads a value between:

```text id="v9k2p5"
0 ─────────────────────► 1023
```

The center position is approximately:

```text id="r4x7m1"
          Center
            ↓
          ~505
```

The program divides the joystick into three regions:

```text id="s8n3c7"
0 ─────────── 495 | 496 ── 514 | 515 ───────── 1023
      FORWARD        🛑 STOP          REVERSE
```

## Joystick Control Logic

### ⬆️ Forward Direction

When:

```text id="q5m8x2"
0 ≤ yVal ≤ 495
```

the motor rotates forward.

```cpp id="b7r3k9"
digitalWrite(input1, HIGH);
digitalWrite(input2, LOW);
```

```text id="p2v6n4"
🕹️ Joystick Up
      ↓
  yVal Decreases
      ↓
➡️ Forward Direction
```

The motor speed is calculated using:

```cpp id="h9m4s1"
forward = (255. / -495.) * (yVal - 495);
```

The resulting value is between approximately:

```text id="c6x2q8"
0 ───────────────────► 255
Slow                    Fast
```

The closer the joystick is to the upper limit, the faster the motor moves.

---

### ⬇️ Reverse Direction

When:

```text id="z3k7m5"
515 ≤ yVal ≤ 1023
```

the motor rotates in the opposite direction.

```cpp id="n8p4r2"
digitalWrite(input1, LOW);
digitalWrite(input2, HIGH);
```

```text id="m5q9v3"
🕹️ Joystick Down
      ↓
  yVal Increases
      ↓
⬅️ Reverse Direction
```

The reverse speed is calculated using:

```cpp id="w2c8f6"
reverse = (255. / 508.) * (yVal - 515);
```

Again, the result is converted into a PWM value between approximately:

```text id="j4s7m1"
0 ───────────────────► 255
Slow                    Fast
```

## 🛑 The Joystick Dead Zone

The project includes a small dead zone around the center of the joystick:

```text id="d8p3x5"
495 < yVal < 515
```

When the joystick is inside this range:

```text id="e7m2q9"
🕹️ Near Center
      ↓
   🛑 Motor Stops
```

The motor is stopped using:

```cpp id="a6k9r4"
analogWrite(enablePin, 0);
```

and:

```cpp id="u3v8n2"
digitalWrite(input1, LOW);
digitalWrite(input2, LOW);
```

This dead zone is important because a joystick may not return to exactly the same value every time.

For example, the center may produce values such as:

```text id="x5q1m7"
498
503
507
512
```

Instead of exactly `511` or `512`.

Without a dead zone, the motor might move slightly even when the joystick appears to be centered.

```text id="f9k4c2"
Small Center Range
        ↓
  🛑 Motor Stays Still
```

## What Is a Joystick Module? 🕹️

A typical joystick module contains:

* 🎛️ X-axis potentiometer
* 🎛️ Y-axis potentiometer
* 🔘 Pushbutton switch

```text id="n7m3q8"
             🕹️ Joystick
             /    |    \
            /     |     \
       X-Axis   Y-Axis  🔘 Switch
         A0       A1
```

This project uses the **Y-axis**.

The Y-axis behaves like a potentiometer:

```text id="k8p2v6"
⬆️ Joystick Up
      ↓
Lower Analog Value

⬇️ Joystick Down
      ↓
Higher Analog Value
```

The Arduino reads this changing analog voltage using:

```cpp id="s4m9x1"
analogRead(y);
```

## What Is the L293D? 🎛️⚙️

The **L293D** is a motor driver IC that allows an Arduino to control a DC motor.

The Arduino provides control signals, while the L293D handles the higher current needed by the motor.

```text id="q3n7m5"
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

The project uses:

```text id="w6p2r8"
Arduino Pin 5 → Enable Pin
Arduino Pin 4 → Input 1
Arduino Pin 3 → Input 2
```

The control flow is:

```text id="a9k4s1"
🧠 Arduino
   │
   ├── Input 1 ──► 🔄 Direction
   ├── Input 2 ──► 🔄 Direction
   └── Enable  ──► ⚡ Speed
              ↓
           🎛️ L293D
              ↓
           ⚙️ Motor
```

## Motor Direction Control

The two input pins determine the direction:

```text id="j5v8n2"
Input 1   Input 2   Motor
  LOW       LOW     🛑 Stop
  HIGH      LOW     ➡️ Forward
  LOW       HIGH    ⬅️ Reverse
  HIGH      HIGH    🛑 Stop
```

The program changes these values based on the joystick position.

### Forward

```cpp id="c7m3q9"
input1 = HIGH;
input2 = LOW;
```

### Reverse

```cpp id="r2x8p4"
input1 = LOW;
input2 = HIGH;
```

### Stop

```cpp id="v6n1k5"
input1 = LOW;
input2 = LOW;
```

## Speed Control with PWM ⚡

The L293D enable pin is controlled using:

```cpp id="t4q9m2"
analogWrite(enablePin, speed);
```

The PWM range is:

```text id="h8m5c3"
0 ───────────────────► 255
OFF                    Maximum Speed
```

The joystick position is converted into this PWM range.

```text id="z7p2r6"
Joystick Near Center
        ↓
   Small PWM Value
        ↓
🐢 Slow Motor

Joystick Far From Center
        ↓
  Large PWM Value
        ↓
🚀 Fast Motor
```

This allows the joystick to control both:

```text id="x3k8n5"
Direction + Speed
```

## Why Are Two Different Formulas Used?

The joystick has two different movement directions.

The forward region is:

```text id="m9v4q2"
0 → 495
```

The reverse region is:

```text id="b6p1s8"
515 → 1023
```

Because these ranges have different starting and ending points, separate linear formulas are used to convert each range into:

```text id="n2r7k4"
0 → 255 PWM
```

Conceptually:

```text id="p8x3m6"
Joystick Value
      ↓
📐 Linear Conversion
      ↓
PWM Value
      ↓
⚡ Motor Speed
```

The formulas were created using a linear relationship between the joystick's measured values and the PWM range.

## Motor Start Logic

The project uses:

```cpp id="c5m8q1"
bool isMotorStopped = true;
```

This variable keeps track of whether the motor is currently stopped.

When the motor starts moving:

```text id="v4p9k2"
🛑 Motor Stopped
       ↓
🕹️ Joystick Moves
       ↓
⚡ Start Motor
       ↓
isMotorStopped = false
```

The code briefly applies full PWM when starting:

```cpp id="r7n2x5"
analogWrite(enablePin, 255);
delay(100);
```

This gives the motor an initial push to overcome the force required to start rotating.

After that, the calculated PWM value controls the speed.

## Complete Project Logic

```text id="q6m3v8"
          🕹️ Move Joystick
                 ↓
          📥 Read Y-Axis
                 ↓
          Value: 0 → 1023
                 ↓
        ┌────────────────┐
        │ Determine Zone │
        └────────────────┘
          ↙      ↓       ↘
      FORWARD   STOP   REVERSE
         ↓       ↓        ↓
      ➡️       🛑       ⬅️
         ↓       ↓        ↓
    Calculate  PWM=0   Calculate
      PWM                PWM
         ↓       ↓        ↓
      🎛️ L293D Motor Driver
                 ↓
              ⚙️ DC Motor
```

## Components

* 🧠 Arduino board
* 🕹️ Joystick module
* 🎛️ L293D motor driver
* ⚙️ DC motor
* 🧩 Breadboard
* 🔌 Jumper wires
* 🔋 Suitable motor power supply

## Key Components & Functions

### 🕹️ Joystick

Provides an analog control signal based on physical movement.

### 🎛️ Y-Axis

Controls both the direction and speed of the DC motor.

### 🎛️ L293D

Receives control signals from the Arduino and drives the DC motor.

### ⚙️ DC Motor

Rotates forward or backward at a speed determined by the joystick.

### ⚡ PWM

Controls the motor speed using values from `0` to `255`.

### 🛑 Dead Zone

Prevents unwanted motor movement when the joystick is near its center position.

## Concepts Demonstrated

* 🕹️ Joystick control
* 📥 Analog input using `analogRead()`
* ⚙️ DC motor control
* 🎛️ L293D motor driver
* 🔄 Forward and reverse motor direction
* ⚡ PWM speed control
* 📐 Linear mathematical conversion
* 🛑 Dead-zone implementation
* 🧠 Boolean state tracking
* `analogWrite()`
* `digitalWrite()`
* Conditional logic

> 🕹️ Push the joystick. Choose the direction. Control the speed. ⚙️⚡
