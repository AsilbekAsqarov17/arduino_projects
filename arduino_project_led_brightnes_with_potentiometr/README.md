# Arduino Project 4: Potentiometer-Controlled LED Brightness 🎛️💡

This project demonstrates how an analog input can be used to control the brightness of an LED.

A **potentiometer** is used to adjust the input value, and the Arduino converts this value into a corresponding PWM output to control the LED brightness.

## How It Works

The potentiometer is connected to analog pin **A5**, while the green LED is connected to digital pin **3**.

When the potentiometer is rotated:

```text
🎛️ Potentiometer
       ↓
  Analog Input
   0 → 1023
       ↓
   Arduino
       ↓
   PWM Output
   0 → 255
       ↓
💡 LED Brightness
```

Turning the potentiometer changes the analog input value. The Arduino then maps this value to a PWM output:

```text
Minimum Value                 Maximum Value
     0          ───────────►      1023
     │                            │
     ▼                            ▼
LED OFF  ◄──────────────────►  LED BRIGHT
     0                            255
```

The current potentiometer value and calculated LED value are also displayed in the **Serial Monitor**.

## What Is a Potentiometer?

A **potentiometer** is a variable resistor with three terminals. It can be used as an adjustable voltage divider.

As the knob is rotated, the voltage at its middle pin changes. The Arduino reads this changing voltage using `analogRead()`.

On a typical Arduino:

```text
Analog Input:  0 ───────────────► 1023
               0V                5V
```

## Components

* Arduino board
* Potentiometer
* Green LED
* Resistor
* Breadboard
* Jumper wires

## Key Components & Functions

### 🎛️ Potentiometer

Acts as an adjustable analog input. Its position determines the voltage read by the Arduino.

### 💡 LED

The LED brightness is controlled using PWM through `analogWrite()`.

### 🧠 Arduino

Reads the potentiometer value, converts it to a suitable PWM value, and controls the LED.

### 🖥️ Serial Monitor

Displays the raw potentiometer value and the calculated LED output value.

## Concepts Demonstrated

* Analog input using `analogRead()`
* PWM output using `analogWrite()`
* Mapping analog values to output values
* Potentiometer operation
* Serial communication
* Variable data types such as `int` and `float`

> Turn the knob. Change the input. Control the light. 🎛️⚡
