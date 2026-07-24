# Arduino Project 22: Traffic Light Simulation 🚦🟢🟡🔴

This project simulates a basic **traffic light system 🚦** using an Arduino and three LEDs:

* 🟢 Green LED — Go
* 🟡 Yellow LED — Transition / Warning
* 🔴 Red LED — Stop

The LEDs turn on and off in a sequence similar to a real traffic light.

```text id="q7m3x8"
🟢 GREEN
   ↓
🟢 GREEN BLINKS
   ↓
🟡 YELLOW
   ↓
🔴 RED
   ↓
🟡 YELLOW
   ↓
🔄 REPEAT
```

## How the Project Works

The project uses three LEDs connected to:

```text id="m5r8k2"
🟢 Green  → Pin 11
🟡 Yellow → Pin 10
🔴 Red    → Pin 9
```

The traffic light follows this sequence:

```text id="v3p9q6"
🟢 Green ON
     ↓
⏳ Wait 8 seconds
     ↓
🟢 Green BLINKS 3 times
     ↓
🟡 Yellow ON
     ↓
⏳ Wait 2 seconds
     ↓
🔴 Red ON
     ↓
⏳ Wait 8 seconds
     ↓
🟡 Yellow ON
     ↓
⏳ Wait 1.5 seconds
     ↓
🔄 Repeat
```

## Traffic Light Sequence 🚦

```text id="x8k2m4"
┌─────────────────────────┐
│ 🟢 GREEN                │
│                         │
│ Cars may move           │
└─────────────────────────┘
            ↓
      🟢 BLINKS 3×
            ↓
┌─────────────────────────┐
│ 🟡 YELLOW               │
│                         │
│ Transition / Warning    │
└─────────────────────────┘
            ↓
┌─────────────────────────┐
│ 🔴 RED                  │
│                         │
│ Stop                    │
└─────────────────────────┘
            ↓
        🟡 YELLOW
            ↓
          🔄 Repeat
```

## LED Pin Configuration 🔌

The pins are defined using constants:

```cpp id="n6p4r9"
const int GREEN_LED  = 11;
const int YELLOW_LED = 10;
const int RED_LED    = 9;
```

Using constants makes the code easier to read:

```text id="a3m8q1"
GREEN_LED
     ↓
Pin 11
```

Instead of repeatedly writing:

```cpp id="r4m9q6"
digitalWrite(11, HIGH);
```

the code can use:

```cpp id="v7n2k8"
digitalWrite(GREEN_LED, HIGH);
```

This makes the program more understandable.

## Timing Constants ⏱️

The project stores the timing values in constants:

```cpp id="q2v7m4"
const unsigned long GREEN_TIME  = 8000;
const unsigned long RED_TIME    = 8000;
const unsigned long TRANSITION  = 2000;
const unsigned long BLINK_SPEED = 400;
```

The values are measured in milliseconds.

```text id="a8m5r2"
1000 milliseconds = 1 second
```

Therefore:

```text id="w5p9k3"
GREEN_TIME  = 8000 ms → 8 seconds
RED_TIME    = 8000 ms → 8 seconds
TRANSITION  = 2000 ms → 2 seconds
BLINK_SPEED = 400 ms  → 0.4 seconds
```

```text id="m7x2q8"
🟢 8 sec
   ↓
🟡 2 sec
   ↓
🔴 8 sec
```

## Why `unsigned long` Is Used

The timing variables use:

```cpp id="c4n8v1"
unsigned long
```

Arduino's `millis()` function and many time-related values use `unsigned long`.

Although the values in this project are relatively small, using `unsigned long` is a good practice for storing time values.

```text id="r3m6p9"
unsigned long
      ↓
Suitable for time values
```

## The `blinkLED()` Function 💡

The project creates a reusable function:

```cpp id="x8q2k5"
void blinkLED(int pin, int times, int duration)
```

This function receives three values:

```text id="v6m3p8"
pin      → Which LED should blink?
times    → How many times?
duration → How fast should it blink?
```

For example:

```cpp id="k9p4x2"
blinkLED(GREEN_LED, 3, BLINK_SPEED);
```

means:

```text id="r7x2m6"
🟢 Green LED
      ↓
💡 Blink 3 times
      ↓
⏱️ 400 ms speed
```

## How the Function Works

The function uses a `for` loop:

```cpp id="p3k8q5"
for (int i = 0; i < times; i++)
```

If:

```text id="a9m4v1"
times = 3
```

the loop runs:

```text id="x6p2q8"
i = 0 → Blink 1
i = 1 → Blink 2
i = 2 → Blink 3
```

Each blink follows:

```text id="m8r3k5"
LED HIGH
   ↓
⏳ Wait
   ↓
LED LOW
   ↓
⏳ Wait
```

The function:

```cpp id="p9m2x6"
digitalWrite(pin, HIGH);
delay(duration);
digitalWrite(pin, LOW);
delay(duration);
```

creates the blinking effect.

```text id="c7k4r8"
💡 ON
  ↓
⏳ 400 ms
  ↓
💡 OFF
  ↓
⏳ 400 ms
  ↓
🔄 Repeat
```

## Green Light Phase 🟢

The green LED turns on:

```cpp id="j5q2x9"
digitalWrite(GREEN_LED, HIGH);
```

The program waits:

```cpp id="a6m9p4"
delay(GREEN_TIME);
```

Since:

```text id="v3n8m1"
GREEN_TIME = 8000 ms
```

the green LED remains on for:

```text id="s5p8k2"
8 seconds
```

Then it turns off:

```cpp id="q6m4r8"
digitalWrite(GREEN_LED, LOW);
```

## Green Warning Blink 🟢💡

After the green light has been on for 8 seconds:

```cpp id="m4q7k2"
blinkLED(GREEN_LED, 3, BLINK_SPEED);
```

is called.

The green LED blinks:

```text id="r9m2v6"
💡 ON → OFF
💡 ON → OFF
💡 ON → OFF
```

This simulates a warning that the green phase is about to end.

```text id="x5k8p3"
🟢 GREEN
    ↓
🟢 💡 💡 💡
    ↓
🟡 YELLOW
```

## Yellow Transition Phase 🟡

The yellow LED turns on:

```cpp id="a7m4q9"
digitalWrite(YELLOW_LED, HIGH);
```

The Arduino waits:

```cpp id="j2p6x8"
delay(TRANSITION);
```

Since:

```text id="v4n8m2"
TRANSITION = 2000 ms
```

the yellow light remains on for:

```text id="q3m7x5"
2 seconds
```

Then it turns off:

```cpp id="k8p2r6"
digitalWrite(YELLOW_LED, LOW);
```

```text id="s9m4v1"
🟢 Green
    ↓
🟡 Yellow
    ↓
🔴 Red
```

## Red Light Phase 🔴

The red LED turns on:

```cpp id="n5x8q2"
digitalWrite(RED_LED, HIGH);
```

The program waits:

```cpp id="c4m7p9"
delay(RED_TIME);
```

Since:

```text id="r2k6v8"
RED_TIME = 8000 ms
```

the red light remains on for:

```text id="j7m3x5"
8 seconds
```

During this phase:

```text id="p8q4m1"
🔴 RED = ON
🟢 GREEN = OFF
🟡 YELLOW = OFF
```

## Red-to-Green Transition 🔴🟡

After the red phase:

```cpp id="v6n2k9"
digitalWrite(YELLOW_LED, HIGH);
delay(1500);
```

The yellow LED turns on for:

```text id="a5m8q3"
1500 ms = 1.5 seconds
```

This creates:

```text id="k2r7m4"
🔴 Red
  +
🟡 Yellow
```

for a short period before the cycle restarts.

This is similar to a real traffic light transition in some systems.

## Turning the LEDs OFF

After the transition:

```cpp id="x8m3p6"
digitalWrite(RED_LED, LOW);
digitalWrite(YELLOW_LED, LOW);
```

The cycle finishes.

Then `loop()` automatically starts again:

```text id="j4n6w8"
🔄 Start Again
    ↓
🟢 Green
    ↓
🟡 Yellow
    ↓
🔴 Red
    ↓
🔄 Repeat
```

## Complete Project Flow

```text id="m7p3x9"
        🟢 GREEN ON
             ↓
          ⏳ 8 sec
             ↓
      🟢 GREEN BLINKS
          3 TIMES
             ↓
        🟡 YELLOW ON
             ↓
          ⏳ 2 sec
             ↓
         🔴 RED ON
             ↓
          ⏳ 8 sec
             ↓
     🟡 YELLOW ON
             ↓
          ⏳ 1.5 sec
             ↓
            🔄
```

## Example Timeline ⏱️

```text id="q5k8r2"
0s  ───────────────► 🟢 Green ON

8s  ───────────────► 🟢 Green Blinks 3 Times

~10.4s ────────────► 🟡 Yellow ON

~12.4s ────────────► 🔴 Red ON

~20.4s ────────────► 🟡 Yellow ON

~21.9s ────────────► 🔄 Restart
```

The exact total time can be slightly different because the blinking function adds its own delays.

## Why Use a Function? 🧠

Instead of writing:

```cpp id="n4m8q2"
digitalWrite(GREEN_LED, HIGH);
delay(400);
digitalWrite(GREEN_LED, LOW);
delay(400);
```

three separate times, the program uses:

```cpp id="v6n2k9"
blinkLED(GREEN_LED, 3, BLINK_SPEED);
```

This makes the code:

* 🧹 Cleaner
* 📖 Easier to read
* ♻️ Reusable
* 🛠️ Easier to modify

The same function could be used for any LED:

```cpp id="a5m8q3"
blinkLED(RED_LED, 5, 200);
blinkLED(YELLOW_LED, 2, 500);
```

## Components

* 🧠 Arduino board
* 🟢 Green LED
* 🟡 Yellow LED
* 🔴 Red LED
* 🧱 Breadboard
* 🔌 Jumper wires
* ⚡ Current-limiting resistors

## Key Components & Functions

### 🟢 Green LED

Represents the go phase.

### 🟡 Yellow LED

Represents a transition or warning phase.

### 🔴 Red LED

Represents the stop phase.

### `digitalWrite()`

Turns LEDs ON or OFF.

```text id="k2r7m4"
HIGH → ON
LOW  → OFF
```

### `delay()`

Pauses the program for a specified amount of time.

### `for` Loop

Repeats the blinking operation a specified number of times.

### `blinkLED()`

A custom reusable function for blinking an LED.

### `const`

Creates values that should not be changed during the program.

## Concepts Demonstrated

* 🚦 Traffic light logic
* 💡 Controlling multiple LEDs
* ⏱️ Timing with `delay()`
* 🔁 Sequential execution
* 🔄 `for` loops
* 🧠 Custom functions
* ♻️ Reusable code
* `const` variables
* `unsigned long`
* `digitalWrite()`

> 🚦 Green means go. 🟡 Yellow means prepare. 🔴 Red means stop.

