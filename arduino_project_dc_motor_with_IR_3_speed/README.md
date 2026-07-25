# Arduino Project 23: IR Remote Controlled DC Fan 🌀📡📟

This project demonstrates how to control a **DC motor 🌀** remotely using an **infrared remote control 📡**.

The current motor speed is displayed on a **16×2 LCD 📟**, while an **L293D motor driver ⚙️** controls the motor.

```text id="q7m3x8"
🎮 IR Remote
      ↓
📡 IR Signal
      ↓
📥 IR Receiver
      ↓
🧠 Arduino
      ↓
⚙️ L293D Motor Driver
      ↓
🌀 DC Motor / Fan
```

At the same time:

```text id="m5r8k2"
🧠 Arduino
      ↓
📟 LCD
      ↓
Display Current Speed
```

The remote control provides three speed levels and an OFF command:

```text id="v3p9q6"
🔴 Button 1 → Speed 1
🟢 Button 2 → Speed 2
🔵 Button 3 → Speed 3
⏻ OFF Button → Stop Motor
```

## Project Overview

The project has four main sections:

```text id="x8k2m4"
        🎮 IR Remote
             ↓
        📡 IR Receiver
             ↓
          🧠 Arduino
          ↙       ↘
      📟 LCD      ⚙️ L293D
                     ↓
                 🌀 DC Motor
```

The Arduino receives the remote command, changes the motor speed, and updates the LCD display.

```text id="n6p4r9"
🎮 Press Button
      ↓
📡 Send IR Signal
      ↓
🧠 Arduino Reads Command
      ↓
⚡ Set Motor Speed
      ↓
📟 Update LCD
```

## Power Supply Arrangement ⚡🔌

This project uses two different power sources for different purposes.

### Arduino 5V Power

The Arduino's 5V pin powers the low-power control components:

```text id="a3m8q1"
🧠 Arduino 5V
      ├── 📟 LCD
      ├── 📥 IR Receiver
      └── 🎛️ Potentiometer
```

These components are used for:

* 🧠 Control
* 📡 Signal reception
* 📟 Display
* 🎛️ Input measurement

### Separate Power Supply for the DC Motor

The DC motor is powered separately using a wall adapter and power supply:

```text id="r4m9q6"
🔌 Wall Adapter
      ↓
⚡ Power Supply
      ↓
⚙️ L293D
      ↓
🌀 DC Motor
```

This is important because a DC motor can require significantly more current than the Arduino can safely provide.

```text id="v7n2k8"
🧠 Arduino
    │
    └── Control Signals ─────► ⚙️ L293D

🔌 External Power Supply ───► ⚙️ L293D ───► 🌀 Motor
```

> ⚠️ The Arduino controls the motor driver, while the external power supply provides the motor's power.

## Why Use a Separate Power Supply? ⚡

A DC motor can draw a relatively large amount of current, especially when:

* 🌀 Starting
* ⚡ Running at high speed
* 🛑 Changing speed
* 🔒 The motor is blocked or under heavy load

The Arduino's 5V pin is not intended to directly power a larger motor.

Therefore, the project separates:

```text id="q2v7m4"
CONTROL
🧠 Arduino
      ↓
⚙️ L293D

POWER
🔌 External Supply
      ↓
🌀 DC Motor
```

This helps protect the Arduino from excessive current demand.

## Important: Common Ground ⚠️

Although the motor uses a separate power supply, the Arduino and motor driver should generally share a common ground for the control signals to have the same voltage reference.

```text id="a8m5r2"
Arduino GND
     │
     ├────────► L293D GND
     │
External Supply GND
```

The exact wiring should follow the L293D datasheet and the power supply configuration being used.

> ⚠️ Always verify the voltage and polarity of the external power supply before connecting it to the motor driver.

## LCD Pin Connections 📟

The 16×2 LCD uses:

```text id="w5p9k3"
LCD Pin      Arduino Pin
────────────────────────
RS      →       12
E       →       11
D4      →       10
D5      →       9
D6      →       8
D7      →       7
```

The LCD is initialized with:

```cpp id="m7x2q8"
LiquidCrystal lcd(rs, e, d4, d5, d6, d7);
```

and:

```cpp id="c4n8v1"
lcd.begin(16, 2);
```

This creates a display with:

```text id="r3m6p9"
16 columns × 2 rows
```

## Initial LCD Display 📟

When the Arduino starts, the code displays:

```text id="x8q2k5"
Fan:
OFF
```

The code:

```cpp id="v6m3p8"
lcd.setCursor(0, 0);
lcd.print("Fan:");
```

prints the title on the first row.

Then:

```cpp id="k9p4x2"
lcd.setCursor(0, 1);
lcd.print(speed);
```

displays the current motor state.

Initially:

```cpp id="r7x2m6"
String speed = "OFF";
```

so the LCD starts with:

```text id="p3k8q5"
┌────────────────┐
│ Fan:           │
│ OFF            │
└────────────────┘
```

## IR Remote Control 📡🎮

The IR receiver is connected to:

```cpp id="a9m4v1"
int receiverPin = 6;
```

It is initialized with:

```cpp id="x6p2q8"
IrReceiver.begin(receiverPin, ENABLE_LED_FEEDBACK);
```

The Arduino waits for an infrared signal:

```cpp id="m8r3k5"
if (IrReceiver.decode()) {
```

When a remote button is pressed:

```text id="p9m2x6"
🎮 Button Press
      ↓
📡 IR Signal
      ↓
📥 Receiver
      ↓
🧠 Decode Command
```

The command is then used to control the motor.

## Remote Control Commands 🎮

The project uses four commands:

```text id="c7k4r8"
Command     Action
────────────────────────
0x45     🌀 Speed 1
0x46     🌀 Speed 2
0x47     🌀 Speed 3
0x19     ⏻ OFF
```

The exact command codes depend on the remote control being used.

Different remotes can produce different command values.

## L293D Motor Driver ⚙️

The Arduino does not directly power the DC motor.

Instead, it sends control signals to the **L293D motor driver**.

The L293D acts as an interface between:

```text id="j5q2x9"
🧠 Arduino
      ↓
⚙️ L293D
      ↓
🌀 DC Motor
```

The driver allows the Arduino to control:

* ⚡ Motor power
* 🌀 Direction
* 🎚️ Speed using PWM

## L293D Pin Configuration

This project uses:

```text id="a6m9p4"
L293D Function       Arduino Pin
────────────────────────────────
Enable                  5
Input 1                 3
Input 2                 2
```

```text id="v3n8m1"
Arduino Pin 5 ───► Enable
Arduino Pin 3 ───► Input 1
Arduino Pin 2 ───► Input 2
```

The motor is connected to the L293D motor output.

The external power supply provides the motor power.

## Controlling Motor Direction 🔄

The two input pins determine the motor direction.

For forward rotation:

```cpp id="s5p8k2"
digitalWrite(input1Pin, HIGH);
digitalWrite(input2Pin, LOW);
```

This creates:

```text id="q6m4r8"
Input 1 = HIGH
Input 2 = LOW
      ↓
🌀 Motor rotates in one direction
```

In this project, all three speed modes use the same direction.

The direction is therefore kept constant while only the motor speed changes.

## Controlling Motor Speed ⚡

The enable pin is connected to:

```cpp id="m4q7k2"
int enablePin = 5;
```

The project uses:

```cpp id="r9m2v6"
analogWrite(enablePin, value);
```

to control the motor speed using PWM.

The PWM range is:

```text id="x5k8p3"
0 ───────────────────► 255
OFF                  Maximum
```

The three speed levels are:

```text id="a7m4q9"
Speed 1 → 190
Speed 2 → 220
Speed 3 → 255
```

```text id="j2p6x8"
⚡ 190 → 🌀 Speed 1
⚡ 220 → 🌀 Speed 2
⚡ 255 → 🌀 Speed 3
```

## Speed 1 🌀

When command `0x45` is received:

```cpp id="v4n8m2"
analogWrite(enablePin, 190);
```

The motor runs at the first speed level.

```text id="q3m7x5"
🎮 Press Button
      ↓
0x45
      ↓
⚡ PWM = 190
      ↓
🌀 Speed 1
      ↓
📟 LCD: Speed 1
```

## Speed 2 🌀🌀

When command `0x46` is received:

```cpp id="k8p2r6"
analogWrite(enablePin, 220);
```

The motor runs faster.

```text id="s9m4v1"
⚡ PWM = 220
      ↓
🌀🌀 Speed 2
```

## Speed 3 🌀🌀🌀

When command `0x47` is received:

```cpp id="n5x8q2"
analogWrite(enablePin, 255);
```

The motor receives the maximum PWM value used in this project.

```text id="c4m7p9"
⚡ PWM = 255
      ↓
🌀🌀🌀 Speed 3
```

## Turning the Motor OFF ⏻

When command `0x19` is received:

```cpp id="r2k6v8"
digitalWrite(input1Pin, LOW);
digitalWrite(input2Pin, LOW);
analogWrite(enablePin, 0);
```

The motor is stopped:

```text id="j7m3x5"
Input 1 = LOW
Input 2 = LOW
Enable   = 0
      ↓
⏻ Motor OFF
```

The speed variable is also updated:

```cpp id="p8q4m1"
speed = "OFF";
```

## Updating the LCD 📟

After a command is processed, the LCD is updated.

First, the second row is cleared:

```cpp id="v6n2k9"
lcd.setCursor(0, 1);
lcd.print("                ");
```

This prints spaces over the previous text.

This is useful because LCD screens do not automatically erase old characters.

For example:

```text id="a5m8q3"
Previous:
Speed 3

New:
OFF
```

Without clearing:

```text id="k2r7m4"
OFFed 3 ❌
```

With clearing:

```text id="x8m3p6"
OFF ✅
```

Then the new speed is displayed:

```cpp id="j4n6w8"
lcd.setCursor(0, 1);
lcd.print(speed);
```

Example:

```text id="m7p3x9"
┌────────────────┐
│ Fan:           │
│ Speed 2        │
└────────────────┘
```

## Serial Monitor Output 💻

The program also displays information in the Serial Monitor.

### IR Protocol

```cpp id="q5k8r2"
Serial.print("Protocol: ");
Serial.println(IrReceiver.getProtocolString());
```

Example:

```text id="n4m8q2"
Protocol: NEC
```

The exact protocol depends on the remote control.

### Command Code

```cpp id="v6n2k9"
Serial.print("Command (Hex): 0x");
Serial.println(IrReceiver.decodedIRData.command, HEX);
```

Example:

```text id="a5m8q3"
Command (Hex): 0x45
```

### Motor State

```cpp id="k2r7m4"
Serial.print("Motor: ");
Serial.println(speed);
```

Example:

```text id="x8m3p6"
Motor: Speed 1
```

Complete example:

```text id="j4n6w8"
Protocol: NEC
Command (Hex): 0x45
Motor: Speed 1
---------------------------------
```

## Complete Project Flow

```text id="m7p3x9"
        🎮 IR Remote
              ↓
        📡 IR Signal
              ↓
        📥 IR Receiver
              ↓
      🔢 Read Command
              ↓
         🧠 Arduino
              ↓
      ┌───────┴────────┐
      │                │
  ⚡ PWM Motor      📟 LCD
      │                │
      ▼                ▼
  ⚙️ L293D       Display Speed
      │
      ▼
   🌀 DC Motor
```

## Example Interaction

```text id="q5k8r2"
1️⃣ Press Button 1
        ↓
   Command = 0x45
        ↓
   PWM = 190
        ↓
   🌀 Speed 1
        ↓
   📟 LCD: Speed 1
```

```text id="n4m8q2"
2️⃣ Press Button 2
        ↓
   Command = 0x46
        ↓
   PWM = 220
        ↓
   🌀 Speed 2
        ↓
   📟 LCD: Speed 2
```

```text id="v6n2k9"
3️⃣ Press Button 3
        ↓
   Command = 0x47
        ↓
   PWM = 255
        ↓
   🌀 Speed 3
        ↓
   📟 LCD: Speed 3
```

```text id="a5m8q3"
4️⃣ Press OFF
        ↓
   Command = 0x19
        ↓
   PWM = 0
        ↓
   ⏻ Motor Stops
        ↓
   📟 LCD: OFF
```

## Components

* 🧠 Arduino board
* 🎮 Infrared remote control
* 📥 IR receiver
* 📟 16×2 LCD
* ⚙️ L293D motor driver
* 🌀 DC motor / fan
* 🔌 External wall adapter / power supply
* 🧱 Breadboard
* 🔌 Jumper wires
* ⚡ Power connections

## Key Components & Functions

### 🎮 IR Remote

Sends infrared commands to control the motor.

### 📥 IR Receiver

Receives and decodes infrared signals.

### 📟 LCD

Displays the current motor speed.

### ⚙️ L293D

Acts as the interface between the Arduino and the DC motor.

It allows the Arduino to control the motor using:

* Enable control
* Direction inputs
* PWM speed control

### 🌀 DC Motor

Converts electrical energy into rotational motion.

### `IrReceiver.decode()`

Checks whether a new IR signal has been received.

### `IrReceiver.decodedIRData.command`

Reads the command code sent by the remote.

### `analogWrite()`

Uses PWM to control the motor speed.

### `digitalWrite()`

Controls the motor direction through the L293D input pins.

### `IrReceiver.resume()`

Prepares the IR receiver to receive the next command.

### `lcd.setCursor()`

Sets the position where text will be displayed.

### `lcd.print()`

Displays text on the LCD.

## Concepts Demonstrated

* 📡 Infrared communication
* 🎮 Remote control
* 📟 LCD display
* ⚙️ L293D motor driver
* 🌀 DC motor control
* ⚡ PWM speed control
* 🔌 Separate motor power supply
* 🧠 Arduino control signals
* 🔢 Hexadecimal IR commands
* `IRremote.hpp`
* `LiquidCrystal.h`
* `analogWrite()`
* `digitalWrite()`
* `IrReceiver.decode()`
* `IrReceiver.resume()`
* Functions and state variables

> 🎮 Press the button. 📡 Send the command. 🧠 Process the signal. ⚙️ Control the motor. 📟 Display the speed.
