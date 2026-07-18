# Arduino Project 6: Potentiometer-Controlled Buzzer Frequency 🎛️🔊

This project demonstrates how a potentiometer can be used to control the sound frequency of a buzzer.

Unlike the previous project, where the buzzer was simply turned **ON or OFF**, this project continuously changes the buzzer's timing based on the potentiometer position.

Turning the potentiometer changes the sound produced by the buzzer.

## How It Works

```text id="4b0xly"
🎛️ Potentiometer
   Analog Value
    0 → 1023
        ↓
   Mathematical
    Conversion
        ↓
  Buzzer Timing
  60 → 10000 μs
        ↓
🔊 Different Sound
   Frequencies
```

The potentiometer provides an analog value between:

```text id="c3ut2r"
0 ───────────────────────► 1023
Minimum                     Maximum
```

This value is converted into a buzzer timing value between approximately:

```text id="8ov34a"
60 μs ─────────────────► 10000 μs
High Frequency            Low Frequency
Higher Pitch              Lower Pitch
```

## The Mathematical Formula

The conversion is performed using:

```cpp id="x6j1br"
buzzTime = (9940. / 1023.) * potVal + 60;
```

This formula is based on the equation of a straight line.

### Input Range

```text id="n5b1yq"
Potentiometer Value:
x₁ = 0
x₂ = 1023
```

### Output Range

```text id="0i7yqy"
Buzzer Timing:
y₁ = 60 μs
y₂ = 10000 μs
```

The goal is to create a linear relationship between these two ranges:

```text id="q8u4v9"
Potentiometer Value        Buzzer Time
       0       ─────────►      60 μs
      1023     ─────────►   10000 μs
```

Using the slope formula:

```text id="r0k6eu"
m = (y₂ - y₁) / (x₂ - x₁)
```

Substituting the values:

```text id="l9k1f2"
m = (10000 - 60) / (1023 - 0)

m = 9940 / 1023
```

Therefore:

```text id="q2d6s8"
y = (9940 / 1023)x + 60
```

This produces the formula used in the Arduino code:

```cpp id="6kz3h4"
buzzTime = (9940. / 1023.) * potVal + 60;
```

## How the Buzzer Produces Sound

The Arduino rapidly switches the buzzer between HIGH and LOW:

```text id="k4r8w2"
HIGH ───────┐      ┌───────
            │      │
LOW         └──────┘

       ← buzzTime →
```

The cycle is:

```text id="v1d5s9"
HIGH
 ↓
Delay: buzzTime
 ↓
LOW
 ↓
Delay: buzzTime
 ↓
Repeat
```

The potentiometer controls the value of `buzzTime`.

Changing the delay changes how quickly the signal switches between HIGH and LOW, which changes the frequency of the sound.

## Components

* Arduino board
* Potentiometer
* Buzzer
* Breadboard
* Jumper wires

## Key Components & Functions

### 🎛️ Potentiometer

Provides an analog input value from `0` to `1023`.

### 🔊 Buzzer

Produces sound based on the frequency of the electrical signal it receives.

### 🧠 Arduino

Reads the potentiometer value, applies the mathematical conversion, and generates the buzzer signal.

### 🧮 Linear Equation

Converts the potentiometer's input range into the desired buzzer timing range.

### 🖥️ Serial Monitor

Displays the current potentiometer value for observation and testing.

## Concepts Demonstrated

* Analog input using `analogRead()`
* PWM-like signal generation using digital output
* `delayMicroseconds()`
* Frequency and pitch control
* Linear equations
* Slope of a line
* Point-slope form
* Range conversion
* Mathematical mapping of input and output values
* Serial communication

> From turning a potentiometer to applying the equation of a line — mathematics becomes sound. 🎛️📐🔊
