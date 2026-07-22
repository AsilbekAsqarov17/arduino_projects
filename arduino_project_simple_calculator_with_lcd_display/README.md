# Arduino Project 16: 8-Bit Binary Counter with 74HC595 🔢💡

This project demonstrates how to use a **74HC595 shift register 🔌** to control multiple outputs using only a few Arduino pins.

The Arduino sends an 8-bit binary value to the shift register. The 74HC595 then outputs the binary pattern through its eight output pins.

```text id="p8x3m5"
🧠 Arduino
    │
    │ 3 Control Pins
    ▼
🔌 74HC595 Shift Register
    │
    ├── Q0
    ├── Q1
    ├── Q2
    ├── Q3
    ├── Q4
    ├── Q5
    ├── Q6
    └── Q7
```

The program continuously increases the value of:

```cpp id="r4n7k2"
byte count = 0x00;
```

and sends it to the shift register.

```text id="v6m2q9"
0 → 1 → 2 → 3 → ... → 255
```

The outputs represent these numbers in binary.

```text id="a8p3x5"
Decimal       Binary
   0       00000000
   1       00000001
   2       00000010
   3       00000011
   4       00000100
   ...
 255       11111111
```

## How the Project Works

The Arduino uses three pins to communicate with the 74HC595:

```text id="k7m3q8"
Arduino          74HC595
────────────────────────────
Pin 12  ───────► SER / DATA
Pin 9   ───────► SRCLK / CLOCK
Pin 11  ───────► RCLK / LATCH
```

The communication flow is:

```text id="n4x8p2"
🧠 Arduino
     ↓
📤 Send 8-Bit Data
     ↓
🔌 74HC595
     ↓
💡 8 Output Pins
```

## What Is a Shift Register? 🔌

A **shift register** is an electronic component that can store and move digital data.

The **74HC595** is an **8-bit serial-in, parallel-out shift register**.

This means:

```text id="m5r9k3"
Serial Data
    │
    │ One Bit at a Time
    ▼
🔌 74HC595
    │
    │ 8 Outputs at Once
    ▼
Q0 Q1 Q2 Q3 Q4 Q5 Q6 Q7
```

Instead of needing eight Arduino pins to control eight outputs, the Arduino can use only three communication pins.

```text id="c2v7p6"
Without Shift Register:
🧠 Arduino ─────► 8 Output Pins

With 74HC595:
🧠 Arduino ─────► 3 Pins ─────► 🔌 74HC595 ─────► 8 Outputs
```

This makes the 74HC595 useful when you need to control many digital outputs.

## The Three Main Control Pins

### 📤 Data Pin

```text id="j8p3m5"
dataPin = 12
```

The data pin sends the binary information to the shift register.

The data is sent one bit at a time:

```text id="x4n7q2"
1 → 0 → 1 → 1 → 0 → 0 → 1 → 0
```

---

### ⏱️ Clock Pin

```text id="r6m2k8"
clockPin = 9
```

The clock tells the shift register when to read each bit.

```text id="v3p8m1"
📤 Data Bit
     +
⏱️ Clock Pulse
     ↓
🔌 Shift Register Stores Bit
```

The data is shifted into the register with each clock pulse.

---

### 🔒 Latch Pin

```text id="q5x9m4"
latchPin = 11
```

The latch controls when the newly received data appears on the output pins.

The process is:

```text id="a7k2p8"
🔒 Latch LOW
      ↓
📤 Send Data
      ↓
⏱️ Clock Shifts Data
      ↓
🔒 Latch HIGH
      ↓
💡 Outputs Update
```

This allows the data to be prepared first and then displayed at the same time.

## The `shiftOut()` Function

The main function used in this project is:

```cpp id="m8q4r2"
shiftOut(dataPin, clockPin, LSBFIRST, count);
```

The function sends the value of `count` to the shift register.

It contains four important parts:

```text id="s3n7v5"
shiftOut(
    dataPin,
    clockPin,
    bitOrder,
    data
)
```

### 📤 `dataPin`

The pin used to send the data.

```text id="f9k2x6"
dataPin = 12
```

### ⏱️ `clockPin`

The pin used to send clock pulses.

```text id="p4m8q1"
clockPin = 9
```

### 🔢 `LSBFIRST`

This determines the order in which the bits are sent.

```text id="w6r3n9"
LSBFIRST
```

means:

```text id="k5p2x8"
Least Significant Bit
        ↓
      First
```

For example:

```text id="c8m4q7"
Binary: 10110010
        ↑
      Sent first
```

The opposite option is:

```text id="n2v7p5"
MSBFIRST
```

which sends the most significant bit first.

## What Is a Byte? 🔢

The variable:

```cpp id="x7m3p9"
byte count = 0x00;
```

stores an 8-bit value.

A byte contains:

```text id="r5k8q2"
8 Bits
```

Each bit can have two possible states:

```text id="m4v9p1"
0 → LOW  → OFF
1 → HIGH → ON
```

Therefore, one byte can represent:

```text id="j6x2q8"
00000000 → 0
11111111 → 255
```

This is why the counter goes from:

```text id="s8p3m5"
0 → 255
```

After reaching `255`, the byte overflows and returns to:

```text id="a2k7v9"
0
```

The sequence becomes:

```text id="q4m8x1"
0 → 1 → 2 → ... → 254 → 255 → 0 → 1 → ...
```

## The `count++` Operation

Each time the loop runs:

```cpp id="v9r3m6"
count++;
```

increases the value by one.

```text id="h5p2k8"
count = 0
      ↓
count = 1
      ↓
count = 2
      ↓
count = 3
      ↓
...
```

Each new number creates a new binary pattern.

```text id="m7x4q2"
Decimal 3

Binary:
00000011

Output:
💡💡💡💡💡💡🔴🔴
```

The exact visual output depends on whether LEDs or another output device is connected to the 74HC595.

## Why Is the Latch Set LOW First?

Before sending new data:

```cpp id="k3n8p5"
digitalWrite(latchPin, LOW);
```

The latch is disabled.

The Arduino then sends the new data:

```cpp id="r6m2v9"
shiftOut(...);
```

After the data has been completely sent:

```cpp id="p8x4q1"
digitalWrite(latchPin, HIGH);
```

The shift register updates its output pins.

```text id="n5m7k2"
🔒 LOW
  ↓
📤 Data Is Shifted In
  ↓
🔒 HIGH
  ↓
💡 Outputs Update
```

This prevents the outputs from changing one bit at a time while the data is being transferred.

## Complete Project Flow

```text id="c4x8m1"
      🔢 count
          ↓
    Convert to Binary
          ↓
     8-Bit Data
          ↓
  📤 Data Pin + ⏱️ Clock
          ↓
      🔌 74HC595
          ↓
       🔒 Latch
          ↓
    💡 8 Outputs
          ↓
    Binary Pattern
```

The counter continuously produces:

```text id="v2p9q5"
00000000
00000001
00000010
00000011
00000100
    ↓
    ↓
11111111
    ↓
00000000
```

## Components

* 🧠 Arduino board
* 🔌 74HC595 shift register
* 💡 LEDs or other output devices
* 🧱 Breadboard
* 🔌 Jumper wires
* ⚡ Resistors for LEDs

## Key Components & Functions

### 🔌 74HC595

An 8-bit shift register that allows the Arduino to control eight outputs using only three control pins.

### 📤 Data

Sends binary information into the shift register.

### ⏱️ Clock

Controls when each bit is read and shifted.

### 🔒 Latch

Transfers the completed data from the internal shift register to the output pins.

### 🔢 Byte

Stores 8 bits and can represent values from `0` to `255`.

### `shiftOut()`

Sends a byte of data to the shift register.

### `LSBFIRST`

Sends the least significant bit first.

## Concepts Demonstrated

* 🔌 Shift registers
* 🔢 Binary numbers
* 💾 Bytes and bits
* 📤 Serial data communication
* ⏱️ Clock signals
* 🔒 Latching data
* `shiftOut()`
* `LSBFIRST`
* `byte`
* Incrementing values
* Binary counting
* Digital output expansion

> 🔢 One byte. Three Arduino pins. Eight outputs. A complete binary counter. 🔌💡
