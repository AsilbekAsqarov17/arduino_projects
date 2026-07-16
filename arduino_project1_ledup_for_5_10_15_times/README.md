# Arduino Project 1: LED Blink Sequence 💡

## Project goal

A simple Arduino project that demonstrates how multiple LEDs can be controlled using digital output pins and `for` loops.

## How It Works

Three LEDs are connected to digital pins **8, 9, and 10**. Each LED blinks a specific number of times before the next LED starts:

| LED   | Arduino Pin | Blink Count |
| ----- | ----------- | ----------- |
| LED 1 | 8           | 5 times     |
| LED 2 | 9           | 10 times    |
| LED 3 | 10          | 15 times    |

Each blink consists of:

**ON → 500 ms → OFF → 500 ms**

The sequence then repeats continuously:

```text
LED 1  →  💡 × 5
LED 2  →  💡 × 10
LED 3  →  💡 × 15
        ↻ Repeat
```

## Components

* Arduino board
* 3 LEDs
* 3 Resistors
* Breadboard
* Jumper wires

## Concepts Demonstrated

* Digital output control
* `pinMode()`
* `digitalWrite()`
* `delay()`
* `for` loops
* Repetitive execution using `loop()`

> A simple project demonstrating how programming logic can control physical components in a sequence.

