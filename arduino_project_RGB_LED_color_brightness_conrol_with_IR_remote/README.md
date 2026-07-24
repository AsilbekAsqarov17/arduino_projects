# Arduino Project 21: IR Remote Controlled RGB LED 🎮📡🌈

This project demonstrates how to control an **RGB LED 🌈** using an **infrared remote control 📡** and an **Arduino 🧠**.

The remote control allows the user to:

* 🔴 Select red
* 🟢 Select green
* 🔵 Select blue
* 🟦 Select cyan
* 🟣 Select magenta
* 🟡 Select yellow
* ⚪ Select white
* ⬆️ Increase brightness
* ⬇️ Decrease brightness
* ⏻ Turn the LED off

```text id="q7m3x8"
🎮 IR Remote
      ↓
📡 Infrared Signal
      ↓
📥 IR Receiver
      ↓
🧠 Arduino
      ↓
🌈 RGB LED
```

The project creates a simple wireless RGB lighting controller.

## How the Project Works

The remote sends an infrared signal whenever a button is pressed.

```text id="m5r8k2"
🎮 Press Remote Button
        ↓
📡 IR Signal Sent
        ↓
📥 Receiver Detects Signal
        ↓
🧠 Arduino Reads Command
        ↓
🎨 Select Color / Change Brightness
        ↓
🌈 RGB LED Updates
```

Each button on the remote has a specific command code.

For example:

```text id="v3p9q6"
Remote Button → Command Code → Action
```

The Arduino reads the command code and decides what action should happen.

## What Is Infrared? 📡

**Infrared (IR)** is a type of electromagnetic radiation that is invisible to the human eye.

An infrared remote control uses an IR LED to transmit information.

```text id="x8k2m4"
🎮 Remote
    │
    │ Invisible IR Signal
    ▼
📥 IR Receiver
    │
    ▼
🧠 Arduino
```

When a button is pressed, the remote sends a coded infrared signal.

The IR receiver detects this signal and allows the Arduino to decode it.

## IR Receiver 📥

The receiver is connected to:

```cpp id="n6p4r9"
int receiverPin = 9;
```

The IR receiver is initialized with:

```cpp id="a3m8q1"
IrReceiver.begin(receiverPin, ENABLE_LED_FEEDBACK);
```

This prepares the receiver to detect infrared signals.

```text id="k5x7p2"
📥 IR Receiver
       ↓
   Detect Signal
       ↓
🧠 Arduino
```

## The IRremote Library 📚

The project uses:

```cpp id="r4m9q6"
#include <IRremote.hpp>
```

The **IRremote library** provides functions for:

* 📥 Receiving IR signals
* 🔢 Reading command codes
* 🧠 Decoding remote button presses

The main function used to check for a received signal is:

```cpp id="v7n2k8"
IrReceiver.decode()
```

The program checks:

```cpp id="q2v7m4"
if (IrReceiver.decode()) {
```

This means:

```text id="a8m5r2"
📡 Is a new IR signal available?
          ↓
      Yes → Read Command
      No  → Keep Waiting
```

## Reading the Remote Command 🔢

The command is stored using:

```cpp id="w5p9k3"
command = IrReceiver.decodedIRData.command;
```

Each button has its own hexadecimal command value.

For example:

```text id="m7x2q8"
0x45 → 🔴 Red
0x46 → 🟢 Green
0x47 → 🔵 Blue
```

The program compares the received command:

```cpp id="c4n8v1"
if(command == 0x45) {
  color = "Red";
}
```

The flow is:

```text id="r3m6p9"
🎮 Button Press
      ↓
🔢 Command Code
      ↓
if / else if
      ↓
🎨 Select Action
```

## Remote Control Commands 🎮

The remote is mapped to different functions.

```text id="x8q2k5"
Command       Action
────────────────────────────
0x16       ⚪ White
0x0D       ⏻ OFF
0x45       🔴 Red
0x46       🟢 Green
0x47       🔵 Blue
0x44       🟦 Cyan
0x40       🟣 Magenta
0x43       🟡 Yellow
0x18       ⬆️ Increase Brightness
0x52       ⬇️ Decrease Brightness
```

The exact command codes can vary depending on the remote control.

## What Is an RGB LED? 🌈

An RGB LED contains three LEDs inside one component:

```text id="v6m3p8"
🔴 Red
🟢 Green
🔵 Blue
```

By controlling the brightness of each color separately, many different colors can be created.

```text id="k9p4x2"
🔴 + 🟢 = 🟡 Yellow
🟢 + 🔵 = 🟦 Cyan
🔴 + 🔵 = 🟣 Magenta
🔴 + 🟢 + 🔵 = ⚪ White
```

The three LED channels are connected to:

```text id="r7x2m6"
Red   → Pin 6
Green → Pin 5
Blue  → Pin 10
```

All three pins support PWM.

## Creating Colors with RGB Values 🎨

The project uses:

```cpp id="p3k8q5"
setColor(red, green, blue);
```

Each color is represented by three values:

```text id="a9m4v1"
Red   → 0–255
Green → 0–255
Blue  → 0–255
```

### 🔴 Red

```cpp id="x6p2q8"
setColor(brightness, 0, 0);
```

```text id="m8r3k5"
🔴 255
🟢 0
🔵 0
```

### 🟢 Green

```cpp id="p9m2x6"
setColor(0, brightness, 0);
```

### 🔵 Blue

```cpp id="c7k4r8"
setColor(0, 0, brightness);
```

### 🟦 Cyan

```cpp id="j5q2x9"
setColor(0, brightness, brightness);
```

```text id="a6m9p4"
🟢 + 🔵 = 🟦
```

### 🟣 Magenta

```cpp id="v3n8m1"
setColor(brightness, 0, brightness);
```

```text id="s5p8k2"
🔴 + 🔵 = 🟣
```

### 🟡 Yellow

```cpp id="q6m4r8"
setColor(brightness, brightness, 0);
```

```text id="n8x3p5"
🔴 + 🟢 = 🟡
```

### ⚪ White

```cpp id="m4q7k2"
setColor(brightness, brightness, brightness);
```

All three channels are turned on equally.

## Brightness Control ⚡

The project stores the current brightness in:

```cpp id="r9m2v6"
int brightness = 255;
```

The brightness range is:

```text id="x5k8p3"
0 ───────────────────► 255
OFF                  Maximum
```

The brightness changes in steps of:

```text id="a7m4q9"
15
```

### Increasing Brightness ⬆️

When the increase command is received:

```cpp id="j2p6x8"
brightness += 15;
```

Example:

```text id="v4n8m2"
150 → 165 → 180 → 195 → ...
```

The code prevents the value from exceeding `255`:

```cpp id="q3m7x5"
if(brightness <= 240) {
  brightness += 15;
}
```

This keeps the brightness within the valid PWM range.

### Decreasing Brightness ⬇️

When the decrease command is received:

```cpp id="k8p2r6"
brightness -= 15;
```

The code prevents the value from becoming negative:

```cpp id="s9m4v1"
if(brightness >= 15) {
  brightness -= 15;
}
```

```text id="n5x8q2"
0 ≤ brightness ≤ 255
```

## What Is PWM? ⚡

The Arduino uses **PWM (Pulse Width Modulation)** to control the brightness of the RGB LED.

The function:

```cpp id="c4m7p9"
analogWrite(pin, value);
```

uses values from:

```text id="r2k6v8"
0 ───────────────► 255
OFF               Full Brightness
```

For example:

```text id="j7m3x5"
analogWrite(redPin, 255);
```

means maximum brightness.

```cpp id="p8q4m1"
analogWrite(redPin, 100);
```

means lower brightness.

```text id="v6n2k9"
PWM = 0    → 💡 OFF
PWM = 128  → 💡 Medium Brightness
PWM = 255  → 💡 Maximum Brightness
```

## The `updateLED()` Function 🧠

The function:

```cpp id="a5m8q3"
updateLED();
```

checks the current color and applies the correct RGB values.

```text id="k2r7m4"
Current Color
      ↓
updateLED()
      ↓
Choose RGB Values
      ↓
setColor()
      ↓
🌈 RGB LED
```

For example:

```text id="x8m3p6"
color = "Blue"
```

The function executes:

```cpp id="j4n6w8"
setColor(0, 0, brightness);
```

The blue channel is turned on while red and green are turned off.

## The `setColor()` Function 🎨

The function:

```cpp id="m7p3x9"
void setColor(int red, int green, int blue)
```

receives three brightness values.

For example:

```text id="q5k8r2"
setColor(255, 100, 0);
```

means:

```text id="n4m8q2"
🔴 Red   → 255
🟢 Green → 100
🔵 Blue  → 0
```

The function sends these values to the RGB LED:

```cpp id="v6n2k9"
analogWrite(redPin, red);
analogWrite(greenPin, green);
analogWrite(bluePin, blue);
```

```text id="a5m8q3"
RGB Values
    ↓
🎨 setColor()
    ↓
⚡ PWM
    ↓
🌈 RGB LED
```

## Turning the LED OFF ⏻

When the OFF command is received:

```cpp id="k2r7m4"
color = "OFF";
```

The `updateLED()` function calls:

```cpp id="x8m3p6"
setColor(0, 0, 0);
```

```text id="j4n6w8"
🔴 0
🟢 0
🔵 0
   ↓
⏻ LED OFF
```

## Remembering the Selected Color 🧠

The project uses:

```cpp id="m7p3x9"
String color = "OFF";
```

This variable stores the currently selected color.

For example:

```text id="q5k8r2"
color = "Red"
```

Then:

```text id="n4m8q2"
⬆️ Brightness
```

can increase the brightness of the currently selected red color.

This means the brightness control works with different colors without needing separate brightness variables.

```text id="v6n2k9"
🎨 Selected Color
      +
⚡ Brightness
      ↓
🌈 Final LED Output
```

## Important: Brightness Is Shared Between Colors

The variable:

```cpp id="a5m8q3"
int brightness = 255;
```

stores one brightness value for the selected color.

For example:

```text id="k2r7m4"
Select Red
    ↓
Brightness = 255
    ↓
⬇️ Press Brightness Down
    ↓
Brightness = 240
```

Then if the user selects blue:

```text id="x8m3p6"
🔵 Blue
    ↓
Brightness = 240
```

The blue LED also uses the current brightness value.

```text id="j4n6w8"
🎨 Color Selection
      +
⚡ Shared Brightness
      ↓
🌈 Output
```

## Serial Monitor Output 💻

The program displays the received information:

```cpp id="m7p3x9"
Serial.print("Command: ");
Serial.println(command, HEX);
```

The command is printed in hexadecimal format.

Example:

```text id="q5k8r2"
Command: 45
```

The current color is also displayed:

```text id="n4m8q2"
Color: Red
```

And the current brightness:

```text id="v6n2k9"
Brightness: 240
```

Example output:

```text id="a5m8q3"
Command: 45
Color: Red
Brightness: 255
----------------------
```

This is useful for debugging and understanding what the Arduino is receiving.

## Resuming IR Reception 🔄

After processing the command:

```cpp id="k2r7m4"
IrReceiver.resume();
```

allows the receiver to listen for the next infrared signal.

```text id="x8m3p6"
📥 Receive Signal
      ↓
🧠 Process Command
      ↓
🌈 Update LED
      ↓
🔄 Resume Receiver
      ↓
📥 Wait for Next Command
```

## Complete Project Flow

```text id="j4n6w8"
       🎮 IR Remote
             ↓
       📡 IR Signal
             ↓
       📥 Receiver
             ↓
    🔢 Read Command Code
             ↓
       🧠 Arduino
             ↓
    ┌────────┴────────┐
    │                 │
🎨 Change Color   ⚡ Change Brightness
    │                 │
    └────────┬────────┘
             ↓
        updateLED()
             ↓
         setColor()
             ↓
          🌈 RGB LED
```

## Example Interaction

```text id="m7p3x9"
1️⃣ Press 🔴 Red
        ↓
   color = "Red"
        ↓
   🔴 LED Turns Red

2️⃣ Press ⬇️ Brightness
        ↓
   brightness -= 15
        ↓
   🔴 LED Becomes Dimmer

3️⃣ Press 🟢 Green
        ↓
   color = "Green"
        ↓
   🟢 LED Turns Green

4️⃣ Press ⬆️ Brightness
        ↓
   brightness += 15
        ↓
   🟢 LED Becomes Brighter
```

## Components

* 🧠 Arduino board
* 🎮 Infrared remote control
* 📥 IR receiver
* 🌈 RGB LED
* 🧱 Breadboard
* 🔌 Jumper wires
* ⚡ Resistors for the RGB LED

## Key Components & Functions

### 📡 IR Remote

Sends coded infrared commands.

### 📥 IR Receiver

Receives and decodes infrared signals.

### 🌈 RGB LED

Produces different colors by combining red, green, and blue light.

### 📚 IRremote Library

Provides functions for receiving and decoding IR signals.

### `IrReceiver.decode()`

Checks whether a new IR signal has been received.

### `IrReceiver.decodedIRData.command`

Reads the command code from the remote.

### `IrReceiver.resume()`

Prepares the receiver to receive the next signal.

### `analogWrite()`

Uses PWM to control LED brightness.

### `updateLED()`

Updates the LED based on the selected color.

### `setColor()`

Applies the RGB brightness values to the LED.

## Concepts Demonstrated

* 📡 Infrared communication
* 🎮 Remote control input
* 📥 IR signal decoding
* 🌈 RGB color mixing
* ⚡ PWM brightness control
* 🔢 Hexadecimal command codes
* `IRremote.hpp`
* `IrReceiver.decode()`
* `IrReceiver.resume()`
* `analogWrite()`
* `if / else if`
* Functions
* `String` variables
* State management
* Brightness limits

> 🎮 Press a button. 📡 Send a signal. 🧠 Decode the command. 🌈 Control the light.
