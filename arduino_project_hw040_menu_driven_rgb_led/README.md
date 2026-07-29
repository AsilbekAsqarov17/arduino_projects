# 🎨 Arduino Project 30: Menu-Driven RGB LED Controller Using Rotary Encoder and LCD

This project combines an **HW-040 Rotary Encoder**, a **16×2 LCD**, and an **RGB LED** to create a simple **menu-driven user interface**. Instead of using multiple buttons or a remote control, the rotary encoder allows the user to navigate through a menu, select an LED color, and adjust its brightness interactively.

The LCD provides real-time feedback by displaying the current menu option and brightness level, while the RGB LED instantly reflects the selected settings. This project introduces the concept of **embedded user interfaces (UI)**, demonstrating how a single input device can control multiple functions through menus.

```text
🎛️ Rotate Encoder
        │
        ▼
📺 LCD Menu Navigation
        │
        ▼
🧠 Arduino Processes Selection
        │
   ┌────┴─────────────┐
   ▼                  ▼
🎨 Select Color   🔆 Adjust Brightness
        │                  │
        └──────────┬───────┘
                   ▼
              💡 RGB LED
```

---

# ⚙️ How It Works

When the Arduino starts, the LCD displays a welcome message before entering the main menu.

```text
Menu:
Red
```

The rotary encoder is used to scroll through four menu options:

* 🔴 Red
* 🟢 Green
* 🔵 Blue
* 🔆 Brightness

Rotating the encoder moves through the menu, while pressing the encoder button selects the highlighted option.

If a color is selected, the RGB LED immediately changes to that color.

If **Brightness** is selected, the encoder changes the LED brightness instead of navigating through menu items.

---

# 🎛️ HW-040 Rotary Encoder

The **HW-040 Rotary Encoder** replaces multiple buttons with a single multifunction controller.

It can:

* 🔄 Detect clockwise rotation
* 🔁 Detect counter-clockwise rotation
* 🔘 Detect button presses

Unlike a potentiometer, the encoder does **not** measure its physical position. Instead, it generates digital pulses whenever it rotates, allowing the Arduino to determine both **direction** and **number of steps**.

### 📌 Encoder Connections

| Encoder Pin | Arduino |
| ----------- | ------- |
| CLK         | Pin 8   |
| DT          | Pin 12  |
| SW          | Pin 13  |
| VCC         | 5V      |
| GND         | GND     |

---

# 📺 LCD User Interface

The **16×2 LCD** acts as the project's graphical interface.

Instead of relying on the Serial Monitor, all important information is shown directly on the display.

Examples include:

```text
Menu:
Green
```

or

```text
Set Brightness:
Level: 180 / 255
```

The LCD continuously updates only when values change, reducing unnecessary screen flickering.

---

# 🎨 RGB LED

An RGB LED actually contains **three separate LEDs** inside one package:

* 🔴 Red
* 🟢 Green
* 🔵 Blue

Each color has its own Arduino PWM output.

By changing the brightness of each individual color, almost any visible color can be created.

In this project only one color is active at a time, making it easier to understand how RGB LEDs work before combining colors in future projects.

---

# 🔆 PWM Brightness Control

Brightness is controlled using Arduino's **PWM (Pulse Width Modulation)** outputs.

```cpp
analogWrite(redPin, red);
analogWrite(greenPin, green);
analogWrite(bluePin, blue);
```

PWM does **not** lower the output voltage. Instead, it rapidly switches the output between HIGH and LOW.

The longer the signal stays HIGH during each cycle, the brighter the LED appears.

Brightness ranges from:

```text
0   → LED OFF
255 → Maximum Brightness
```

The rotary encoder increases or decreases brightness by **15** each step.

```cpp
brightness += 15;
brightness -= 15;
```

The value is limited so it always remains within the valid PWM range.

```cpp
0 ≤ Brightness ≤ 255
```

---

# 🧠 Menu System

The menu options are stored inside a string array.

```cpp
const String menu[4] =
{
    "Red",
    "Green",
    "Blue",
    "Brightness"
};
```

Instead of writing separate LCD code for every menu item, the program simply displays:

```cpp
menu[position]
```

This makes the code cleaner and much easier to expand.

For example, adding a **White** option would only require adding another element to the array.

---

# 📦 Why Arrays Are Used

Arrays allow multiple related values to be stored together.

Instead of writing:

```cpp
String color1;
String color2;
String color3;
String color4;
```

the project stores everything inside one array.

```cpp
menu[4]
```

This allows the rotary encoder to scroll through options simply by changing the array index.

---

# ⚙️ Functions Used

The project is divided into reusable functions.

### 🎨 `updateLED()`

Determines which color should currently be displayed.

```cpp
updateLED();
```

Depending on the selected menu option, it sends the proper RGB values to the LED.

---

### 💡 `setColor()`

```cpp
setColor(red, green, blue);
```

This function writes PWM values to each LED channel.

Example:

```cpp
setColor(255,0,0);
```

Produces pure red.

```cpp
setColor(0,255,0);
```

Produces green.

```cpp
setColor(0,0,255);
```

Produces blue.

Using a function avoids repeating the same three `analogWrite()` calls throughout the program.

---

# 🔄 Rotary Navigation Logic

Every encoder movement changes the menu position.

Clockwise:

```cpp
position++;
```

Counter-clockwise:

```cpp
position--;
```

The menu wraps around automatically.

```text
🔴 Red
      ↓
🟢 Green
      ↓
🔵 Blue
      ↓
🔆 Brightness
      ↓
🔴 Red
```

This creates an infinite circular menu.

---

# 🔘 Selecting an Option

Pressing the encoder button confirms the highlighted menu item.

Two different actions are possible:

### 🎨 Color Selected

The RGB LED immediately changes to the selected color.

Example:

```text
Color Set To:
Blue
```

---

### 🔆 Brightness Selected

The menu switches into brightness adjustment mode.

The encoder no longer changes menu options.

Instead, every rotation changes the brightness level.

```text
Set Brightness:
Level: 210 / 255
```

This demonstrates how one input device can perform multiple tasks depending on the current program state.

---

# 🔌 Hardware Connections

## 🎛️ HW-040 Rotary Encoder

| Pin | Arduino |
| --- | ------- |
| CLK | 8       |
| DT  | 12      |
| SW  | 13      |
| VCC | 5V      |
| GND | GND     |

---

## 📺 LCD (16×2)

| LCD Pin | Arduino |
| ------- | ------- |
| RS      | 7       |
| E       | 6       |
| D4      | 5       |
| D5      | 4       |
| D6      | 3       |
| D7      | 2       |

---

## 💡 RGB LED

| LED Pin | Arduino                                                            |
| ------- | ------------------------------------------------------------------ |
| Red     | 11 (PWM)                                                           |
| Green   | 10 (PWM)                                                           |
| Blue    | 9 (PWM)                                                            |
| Common  | GND *(common cathode)* or 5V *(common anode, with inverted logic)* |

> ⚠️ **Important:** Always use current-limiting resistors (typically **220–330 Ω**) with each RGB LED channel to protect both the LED and the Arduino.

---

# 📚 Concepts Learned

After completing this project, you'll understand:

* 🎛️ How a rotary encoder can replace multiple buttons.
* 📺 How to build a simple menu-driven interface.
* 💡 How PWM controls LED brightness.
* 🌈 How RGB LEDs produce different colors.
* 📦 How arrays simplify menu management.
* ⚙️ How functions improve code readability and reusability.
* 🧠 How state-based programming changes the behavior of a single input device.
* 🖥️ How embedded systems implement interactive user interfaces.

---

# 🚀 Possible Improvements

* 🌈 Mix multiple RGB channels to create millions of colors.
* 💾 Save the selected color and brightness in EEPROM.
* 🎵 Add a buzzer for menu navigation feedback.
* 📱 Control the menu through Bluetooth or Wi-Fi.
* 📲 Replace the LCD with an OLED display.
* ✨ Add smooth fade animations between colors.
* 🕹️ Add more menu pages for lighting effects such as Rainbow, Pulse, or Breathing Mode.

---

# 📌 Project Concept

```text
🎛️ Rotate Encoder
        │
        ▼
📺 Navigate LCD Menu
        │
        ▼
🔘 Press Encoder Button
        │
   ┌────┴─────────────┐
   ▼                  ▼
🎨 Select Color   🔆 Brightness Mode
        │                  │
        └──────────┬───────┘
                   ▼
          💡 Update RGB LED
                   │
                   ▼
        📺 Display Current Status
```

This project is an excellent introduction to **menu-driven embedded systems**, combining **user input**, **LCD interfaces**, **PWM control**, and **modular programming** into a practical application. The same design principles are used in many real-world devices such as thermostats, laboratory equipment, industrial controllers, and consumer electronics, where a single rotary encoder is used to navigate settings and configure system behavior.
