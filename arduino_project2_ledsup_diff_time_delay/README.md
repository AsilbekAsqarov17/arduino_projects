# Arduino Project 2: LEDs with Different Blink Speeds 💡

#Project goal

This project demonstrates how multiple LEDs can be programmed to blink at different speeds by using different delay intervals.

Each LED blinks **5 times**, but the duration of its ON and OFF states changes:

| LED      | Arduino Pin | Delay  | Blink Speed |
| -------- | ----------- | ------ | ----------- |
| 🔴 Red   | 8           | 50 ms  | Fast        |
| 🟢 Green | 9           | 250 ms | Medium      |
| 🔵 Blue  | 10          | 500 ms | Slow        |

## Sequence

```text
🔴 Red    →  × 5  → Fast
🟢 Green  →  × 5  → Medium
🔵 Blue   →  × 5  → Slow

⏸️ Pause: 2 seconds
        ↻ Repeat
```

For each LED:

```text
ON → Delay → OFF → Delay
```

The sequence runs continuously, with a **2-second pause** after all three LEDs complete their blinking cycles.

## Components

* Arduino board
* 3 LEDs
* 3 Resistors
* Breadboard
* Jumper wires

## Concepts Demonstrated

* Digital output control
* Different timing intervals using `delay()`
* `for` loops
* Sequential LED control
* Creating different blink speeds
* Using variables to manage pin numbers and timing values

> One sequence. Three LEDs. Three different speeds. ⚡
