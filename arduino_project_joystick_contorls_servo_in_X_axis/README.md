# Arduino Project 11: Joystick-Controlled Servo Motor 🕹️⚙️

This project demonstrates how a **joystick module 🕹️** can be used to control the position of a **servo motor ⚙️**.

The joystick's horizontal movement is converted into a servo angle between **0° and 180°**.

```text id="n2w7qk"
🕹️ Move Joystick Horizontally
          ↓
      X-Axis Value
       0 → 1023
          ↓
    🧮 Convert Value
       0° → 180°
          ↓
      ⚙️ Servo Rotates
```

## How It Works

The joystick provides two analog values:

```text id="j5k9r3"
🕹️ Joystick
   ↙       ↘
X-Axis     Y-Axis
 A0         A1
```

This project uses the **X-axis** to control the servo motor.

The **Y-axis** is also read and displayed in the Serial Monitor, but it does not currently control the servo.

The joystick switch is connected to digital pin **2**.

```text id="f8m3v6"
X-Axis → A0
Y-Axis → A1
Switch → Pin 2
Servo  → Pin 10
```

## X-Axis to Servo Angle

The joystick's X-axis provides an analog value between:

```text id="c7p2x9"
0 ─────────────────────► 1023
Left                      Right
```

This value is converted into a servo angle:

```text id="a4k8s1"
0° ─────────────────────► 180°
```

The conversion is performed using:

```cpp id="m6q3v8"
xAngle = (180. / 1023.) * xVal;
```

This creates a linear relationship:

```text id="q9w5n2"
X-Axis Value              Servo Angle

     0       ─────────►       0°
    ~512      ─────────►      90°
    1023      ─────────►     180°
```

The calculated angle is then sent to the servo:

```cpp id="z3r7k4"
servo.write(xAngle);
```

## What Is a Joystick Module?

A typical Arduino joystick module is essentially a combination of:

* 🎛️ An X-axis potentiometer
* 🎛️ A Y-axis potentiometer
* 🔘 A pushbutton switch

```text id="h8v2m5"
              🕹️ Joystick
              /    |    \
             /     |     \
        X-Axis   Y-Axis  🔘 Switch
          A0       A1       D2
```

### 🎛️ X-Axis

Measures horizontal movement.

In this project, the X-axis controls the servo angle.

```text id="s6k1p9"
⬅️ Move Left
     ↓
Lower X Value
     ↓
⚙️ Smaller Angle

Move Right ➡️
     ↓
Higher X Value
     ↓
⚙️ Larger Angle
```

### 🎛️ Y-Axis

Measures vertical movement.

The Y-axis value is read and displayed in the Serial Monitor but is not used to control the servo in this project.

### 🔘 Joystick Switch

Most joystick modules contain a built-in pushbutton.

Pressing the joystick down changes the state of the switch.

The switch is connected to digital pin **2**.

## Switch Configuration

The code uses:

```cpp id="p4n8x2"
digitalWrite(switchPin, HIGH);
```

After setting the pin as an input:

```cpp id="v7m3q5"
pinMode(switchPin, INPUT);
```

This enables the Arduino's internal pull-up resistor.

The switch logic is therefore:

```text id="b2k9r6"
🔘 Not Pressed → HIGH
🔘 Pressed     → LOW
```

The current switch value is displayed in the Serial Monitor.

## Project Logic

```text id="t5x8m1"
🕹️ Move Joystick
        ↓
📥 Read X-Axis
        ↓
  Value: 0 → 1023
        ↓
🧮 Convert to Angle
        ↓
  Angle: 0° → 180°
        ↓
    ⚙️ Servo Moves
```

At the same time:

```text id="d9q4s7"
🕹️ Y-Axis ─────► 📊 Serial Monitor
🔘 Switch ─────► 📊 Serial Monitor
```

## Serial Monitor Output

The project displays:

```text id="r3w6k2"
X = 512
Y = 498
Switch = 1
Angle: 90
```

This makes it possible to observe the joystick values and the calculated servo angle in real time.

## Components

* 🧠 Arduino board
* 🕹️ Joystick module
* ⚙️ Servo motor
* 🧩 Breadboard
* 🔌 Jumper wires

## Key Components & Functions

### 🕹️ Joystick

Provides two analog axes and a built-in pushbutton.

### 🎛️ X-Axis

Controls the servo position by providing an analog value from `0` to `1023`.

### 🎛️ Y-Axis

Provides a second analog input that is monitored through the Serial Monitor.

### 🔘 Joystick Switch

Provides a digital input when the joystick is pressed down.

### ⚙️ Servo Motor

Rotates to the angle calculated from the joystick's X-axis position.

### 🧮 Linear Conversion

Maps the joystick's X-axis range of `0–1023` to a servo angle range of `0°–180°`.

## Concepts Demonstrated

* 🕹️ Joystick input
* 📥 Analog input using `analogRead()`
* 🔘 Digital input using `digitalRead()`
* ⚙️ Servo motor control
* 📚 Using the `Servo` library
* 🧮 Linear mathematical conversion
* 📐 Mapping input values to angles
* 🖥️ Serial communication
* 🔄 Reading multiple inputs

> 🕹️ Move the joystick. Change the value. Control the angle. ⚙️
