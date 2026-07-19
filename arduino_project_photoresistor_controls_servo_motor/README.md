# Arduino Project 10: Light-Controlled Servo Motor 🌞⚙️

This project demonstrates how a **photoresistor (LDR)** can be used to control the position of a **servo motor** based on the amount of light detected.

As the environment becomes brighter, the servo rotates toward **180°**. As the light level decreases, the servo angle also decreases.

```text
🌞 More Light
     ↓
📷 Photoresistor
     ↓
🧠 Arduino Reads Light Level
     ↓
🧮 Convert Light Value to Angle
     ↓
⚙️ Servo Rotates
```

## How It Works

The photoresistor is connected to analog pin **A5**, while the servo motor is connected to digital pin **9**.

The Arduino continuously reads the light level:

```text
🌑 Darker Environment
        ↓
  Lower Light Value
        ↓
  Smaller Servo Angle
        ↓
      ⚙️ 0°
```

```text
🌞 Brighter Environment
        ↓
  Higher Light Value
        ↓
  Larger Servo Angle
        ↓
     ⚙️ 180°
```

The project uses the following measured photoresistor range:

```text
Light Value
    50 ─────────────────────► 900
  Darkest                  Brightest
```

This range is converted into the servo's angle range:

```text
Servo Angle
    0° ────────────────────► 180°
```

The relationship is therefore:

```text
Photoresistor Value        Servo Position

       50       ─────────►       0°
      ~475      ─────────►      90°
       900      ─────────►     180°
```

## The Mathematical Conversion

The servo angle is calculated using:

```cpp
servoPos = (180. / 900.) * resVal;
```

However, before the conversion, the code limits the photoresistor value:

```cpp
if (resVal > 900) resVal = 900;
if (resVal < 0)   resVal = 0;
```

The intended mapping is:

```text
50  →  0°
900 →  180°
```

Conceptually, this can be represented using a linear equation:

```text
x₁ = 50
x₂ = 900

y₁ = 0°
y₂ = 180°
```

Using the slope formula:

```text
m = (y₂ - y₁) / (x₂ - x₁)
```

The conversion can be written as:

```text
servo angle = ((light value - 50) / (900 - 50)) × 180
```

This creates a direct relationship between the detected brightness and the servo position.

> Note: The exact minimum and maximum values from a photoresistor can vary depending on the surrounding light conditions and the specific circuit. Therefore, the values `50` and `900` were based on the values measured during this experiment.

## What Is a Photoresistor?

A **photoresistor**, also called an **LDR (Light-Dependent Resistor)**, is a resistor whose resistance changes depending on the amount of light it receives.

```text
🌞 More Light  →  Lower Resistance
🌑 Less Light  →  Higher Resistance
```

Because its resistance changes, the voltage in the circuit also changes. The Arduino can detect this changing voltage using an analog input.

```text
🌞 Light Changes
       ↓
📷 LDR Resistance Changes
       ↓
⚡ Voltage Changes
       ↓
🧠 Arduino Reads Analog Value
       ↓
⚙️ Servo Position Changes
```

## What Is a Servo Motor?

A **servo motor ⚙️** is a motor designed to move to a specific position.

Unlike a normal DC motor, which continuously rotates, a servo can be commanded to move to a particular angle.

In this project, the servo position depends on the detected light level:

```text
🌑 Darker
   ↓
Lower Value
   ↓
⚙️ Smaller Angle

🌞 Brighter
   ↓
Higher Value
   ↓
⚙️ Larger Angle
```

## Project Logic

```text
🌞 Light Level Changes
          ↓
   📷 Photoresistor
          ↓
    📥 analogRead()
          ↓
   🧮 Convert Value
          ↓
    0° ───────► 180°
          ↓
      ⚙️ Servo
```

The current photoresistor value is also displayed in the **Serial Monitor**:

```cpp
Serial.println(resVal);
```

This makes it possible to observe how the sensor value changes as the lighting conditions change.

## Real-World Calibration

When building a project with a photoresistor, the measured values may not always be exactly the same.

The sensor readings can change depending on:

* 🌞 The intensity of the surrounding light
* 💡 The type of light source
* 📷 The specific photoresistor being used
* 🧱 The resistor used in the circuit
* 📐 The position and direction of the sensor
* 🌤️ The surrounding environmental conditions

For example, one setup might produce:

```text
Minimum Light Value → 50
Maximum Light Value → 900
```

While another setup might produce:

```text
Minimum Light Value → 80
Maximum Light Value → 950
```

Because of this, it is often useful to first observe the sensor values using the Serial Monitor and then adjust the minimum and maximum values in the program.

This process is called **calibration**.

## Components

* 🧠 Arduino board
* 📷 Photoresistor (LDR)
* ⚙️ Servo motor
* 🧱 Resistor
* 🧩 Breadboard
* 🔌 Jumper wires

## Key Components & Functions

### 📷 Photoresistor (LDR)

Detects changes in the surrounding light level and provides a variable analog value.

### ⚙️ Servo Motor

Rotates to an angle based on the amount of light detected.

### 🧠 Arduino

Reads the sensor value, converts it into an angle, and controls the servo.

### 🧮 Linear Mapping

Converts the photoresistor's measured light range into the servo's angle range.

### 🖥️ Serial Monitor

Displays the current photoresistor value and helps with testing and calibration.

## Concepts Demonstrated

* 📷 Light detection using a photoresistor
* 📥 Analog input using `analogRead()`
* ⚙️ Servo motor control
* 📚 Using the `Servo` library
* 🧮 Linear mathematical conversion
* 📐 Range mapping
* 🛠️ Sensor calibration
* 🌞 Using environmental conditions to control a physical device

> 🌞 The brighter the light, the greater the angle. A simple sensor turns changing daylight into movement. ⚙️
