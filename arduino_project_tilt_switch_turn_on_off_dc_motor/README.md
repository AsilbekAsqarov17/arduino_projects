# Arduino Project 13: Tilt Switch-Controlled DC Motor 📐⚙️

This project demonstrates how a **tilt switch 📐** can be used to control a **DC motor ⚙️** through an **L293D motor driver 🎛️**.

When the tilt switch detects a specific orientation, the Arduino activates the L293D, allowing the motor to run. When the tilt condition changes, the motor stops.

```text id="n7x3m5"
📐 Tilt Switch
      ↓
🧠 Arduino Reads Tilt
      ↓
🎛️ L293D Motor Driver
      ↓
⚙️ DC Motor
```

The complete project connects:

```text id="v4k8p2"
📐 Tilt Switch
      │
      ▼
🧠 Arduino
      │
      ▼
🎛️ L293D
      │
      ▼
⚙️ DC Motor
```

## How the Project Works

The tilt switch is connected to the Arduino's digital pin **8**.

The Arduino continuously reads its state:

```text id="q9m2s6"
📐 Tilt Switch
      ↓
📥 Digital Signal
      ↓
🧠 Arduino
```

The Arduino then controls the **L293D motor driver**.

The L293D controls the DC motor using:

```text id="x6p3n8"
Enable Pin → 5
Input 1    → 4
Input 2    → 3
```

The complete control flow is:

```text id="m5r8k1"
📐 Tilt Switch
      ↓
  tiltVal = 0?
   ↙       ↘
 YES        NO
  ↓          ↓
⚡ Enable   🛑 Disable
  ↓          ↓
🎛️ L293D   🎛️ L293D
  ↓          ↓
⚙️ Motor ON  🛑 Motor OFF
```

## What Is a Tilt Switch? 📐

A **tilt switch** is a sensor that detects changes in orientation.

A simple tilt switch often contains a small conductive ball inside a tube.

```text id="a8q4v7"
   📐 Tilt Switch

  ┌─────────────┐
  │      ●      │
  └─────────────┘
       ⚪
  Conductive Ball
```

When the switch is tilted, the ball moves and may:

```text id="k3m7x2"
🔌 Complete the circuit
        OR
🚫 Break the circuit
```

The Arduino reads this as a digital signal:

```text id="f9p2s5"
HIGH → 1
LOW  → 0
```

In this project:

```text id="w6n4c8"
tiltVal == 0
      ↓
⚙️ Motor ON
```

```text id="j2r8m3"
tiltVal != 0
      ↓
🛑 Motor OFF
```

The exact HIGH/LOW behavior depends on the tilt switch type and circuit configuration.

## What Is the L293D? 🎛️⚙️

The **L293D** is a motor driver IC that allows an Arduino to control DC motors.

An Arduino can provide control signals, but its pins are not designed to supply the larger current required by a motor.

The L293D acts as an interface:

```text id="p4x9s1"
🧠 Arduino
    │
    │ Control Signals
    ▼
🎛️ L293D
    │
    │ Motor Power
    ▼
⚙️ DC Motor
```

The Arduino decides what the motor should do, while the L293D handles the motor-driving part of the circuit.

## Why Use the L293D?

A DC motor may require more current than an Arduino pin should provide.

Connecting a motor directly to an Arduino pin can:

* ⚠️ Draw too much current
* 🔥 Damage the Arduino
* 🔄 Cause unstable operation
* ⚡ Create electrical noise

The L293D allows the Arduino to control the motor more safely.

## L293D as a Dual H-Bridge Driver

The L293D contains two **H-bridge motor driver circuits**.

This means it can control two DC motors independently:

```text
             🎛️ L293D
             /      \
            /        \
       ⚙️ Motor A  ⚙️ Motor B
```

Each H-bridge can control:

* ➡️ Motor direction
* ⬅️ Reverse direction
* ⚡ Motor speed using PWM
* 🛑 Motor stopping

This project uses one motor channel.

## Motor Direction Control

The L293D uses two input pins to control the motor direction.

In this project:

```cpp id="y7q2m5"
digitalWrite(input1, HIGH);
digitalWrite(input2, LOW);
```

This sets one direction of rotation.

The general logic is:

```text id="r5n8c3"
Input 1   Input 2   Motor
  LOW       LOW     🛑 Stop
  HIGH      LOW     ➡️ Direction 1
  LOW       HIGH    ⬅️ Direction 2
  HIGH      HIGH    🛑 Stop
```

The direction is fixed in this project because:

```text id="s3k9p6"
Input 1 = HIGH
Input 2 = LOW
```

The tilt switch only determines whether the motor runs or stops.

## Enable Pin and PWM

The L293D's **Enable pin** controls whether the motor channel is active.

The enable pin is connected to Arduino pin **5**.

```cpp id="m8v4x1"
analogWrite(enablePin, 255);
```

means:

```text id="q6p2r9"
PWM = 255
    ↓
⚡ Maximum Power
    ↓
⚙️ Motor Runs
```

When:

```cpp id="c5n7s2"
analogWrite(enablePin, 0);
```

the motor stops:

```text id="h4m9k6"
PWM = 0
    ↓
🛑 No Motor Power
    ↓
⚙️ Motor Stops
```

PWM can also be used to control the motor speed:

```text id="v2p8m5"
PWM = 0    → 🛑 OFF
PWM = 100  → 🐢 Slower
PWM = 200  → ⚡ Faster
PWM = 255  → 🚀 Maximum
```

In this project, only `0` and `255` are used, so the motor is essentially controlled as ON or OFF.

## What Is a DC Motor? ⚙️

A **DC motor** converts electrical energy into rotational motion.

```text id="n3x7q1"
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

In this project:

```text
📐 Tilt Switch → Controls ON/OFF
🎛️ L293D       → Controls Motor
⚙️ DC Motor     → Produces Rotation
```

## Complete Project Logic

```text id="t8m4q6"
        📐 Tilt Switch
              ↓
       📥 digitalRead()
              ↓
      Read tiltVal
              ↓
       tiltVal == 0?
          ↙      ↘
        YES       NO
         ↓         ↓
   Enable = 255  Enable = 0
         ↓         ↓
      🎛️ L293D  🎛️ L293D
         ↓         ↓
     ⚙️ ON      🛑 OFF
```

The motor direction is set by:

```text id="z5r2k8"
Input 1 = HIGH
Input 2 = LOW
```

The motor's ON/OFF state is controlled by:

```text id="p9x3m7"
Enable = 255 → ⚙️ Motor ON
Enable = 0   → 🛑 Motor OFF
```

## Components

* 🧠 Arduino board
* 📐 Tilt switch
* 🎛️ L293D motor driver
* ⚙️ DC motor
* 🧱 Breadboard
* 🔌 Jumper wires
* 🔋 Suitable motor power supply

## Key Components & Functions

### 📐 Tilt Switch

Detects changes in the orientation of the circuit.

### 🧠 Arduino

Reads the tilt switch and sends control signals to the L293D.

### 🎛️ L293D

Acts as an interface between the Arduino and DC motor, controlling motor power and direction.

### ⚙️ DC Motor

Converts electrical energy into rotational movement.

### ⚡ Enable Pin

Controls the motor's activation and can be used for PWM speed control.

### 🔄 Input Pins

Determine the direction in which the motor rotates.

## Concepts Demonstrated

* 📐 Tilt switch input
* 📥 Digital input using `digitalRead()`
* 🎛️ L293D motor driver
* ⚙️ DC motor control
* 🔄 H-bridge direction control
* ⚡ PWM motor control
* `analogWrite()`
* `digitalWrite()`
* 🧠 Arduino-to-driver communication
* 🔌 Motor power control

> 📐 The tilt switch detects the position. 🧠 The Arduino makes the decision. 🎛️ The L293D drives the motor. ⚙️
