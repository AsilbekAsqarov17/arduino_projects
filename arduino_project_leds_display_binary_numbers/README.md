# Arduino Project 3: Decimal to Binary LED Display 🔢💡

This project demonstrates how four LEDs can be used to display decimal numbers in their **4-bit binary representation**.

The Arduino converts decimal numbers from **0 to 15** into binary and displays each result using four LEDs.

## How It Works

Four LEDs are connected to digital pins **8, 9, 10, and 11**.

Each LED represents one binary bit:

```text
LED 1   LED 2   LED 3   LED 4
  8       4       2       1
```

The project counts through the following sequence:

```text
Decimal     Binary     LEDs
   0        0000       ○ ○ ○ ○
   1        0001       ○ ○ ○ ●
   2        0010       ○ ○ ● ○
   3        0011       ○ ○ ● ●
   4        0100       ○ ● ○ ○
   ...       ...       ...
  15        1111       ● ● ● ●
```

Each binary number is displayed for **1 second** before moving to the next number.

After displaying all values from **0 to 15**, the Arduino waits for **2 seconds** and then starts the sequence again.

## Components

* Arduino board
* 4 LEDs
* 4 Resistors
* Breadboard
* Jumper wires

## Concepts Demonstrated

* Decimal-to-binary conversion
* Binary number representation
* Arrays
* Functions
* `for` and `while` loops
* String manipulation
* Digital output control
* Bit representation using LEDs

> Four LEDs. Sixteen numbers. One simple introduction to binary counting. 🔢⚡
