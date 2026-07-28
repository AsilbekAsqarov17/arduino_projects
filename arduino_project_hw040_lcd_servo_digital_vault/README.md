# 🔐 Arduino Project 29: Digital Safe Using Rotary Encoder, LCD, and Servo Motor

This project simulates a **digital safe lock** using an **HW-040 rotary encoder** as the input device, a **16×2 LCD** for user interaction, and a **servo motor** to represent the locking mechanism.

Instead of entering a password with a keypad, the user rotates the encoder to select each digit of a **4-digit passcode**. Pressing the encoder's built-in pushbutton confirms each digit. Once all four digits have been entered, the Arduino compares the entered code with the stored password.

If the password is correct, the servo rotates to unlock the safe for a few seconds before automatically locking again. If the password is incorrect, an error message is displayed.

```text
🎛️ Rotary Encoder
        │
        ▼
🧠 Arduino Uno
        │
        ▼
🔍 Password Verification
        │
   ┌────┴────┐
   ▼         ▼
📺 LCD    ⚙️ Servo Lock
```

---

# ⚙️ How It Works

The system stores a predefined password:

```cpp
const int passcode[4] = {4, 7, 3, 5};
```

The user enters four digits one at a time.

### 📝 Password Entry Steps

1. 🔄 Rotate the encoder to choose a number from **0–9**.
2. 🔘 Press the encoder button to confirm the selected digit.
3. 🔁 Repeat until all four digits have been entered.

The entered digits are stored inside:

```cpp
int enteredcode[4];
```

After all digits are entered, the program compares both arrays.

If every digit matches:

```text
✅ Access Granted!
```

Otherwise:

```text
❌ Wrong Password!
```

---

# 🔍 Password Verification

The comparison is performed by:

```cpp
bool matching(const int passcode[], const int enteredcode[])
```

The function checks every digit individually.

```cpp
for(int i = 0; i < 4; i++)
```

If any digit is different:

```cpp
return false;
```

Otherwise:

```cpp
return true;
```

💡 This is a simple example of **array comparison**, which is commonly used for password verification.

---

# 🎛️ HW-040 Rotary Encoder

The **HW-040 Rotary Encoder Module** is a digital input device that detects **rotation** instead of position.

Unlike a potentiometer, a rotary encoder **does not output an analog voltage**. Instead, it generates digital pulses that allow the Arduino to determine:

* 🔄 Rotation direction
* 🔢 Number of steps
* 🔘 Button presses

### 📌 Module Pins

| Pin | Purpose          |
| --- | ---------------- |
| CLK | Clock output     |
| DT  | Direction output |
| SW  | Pushbutton       |
| VCC | Power            |
| GND | Ground           |

Arduino connections:

| Arduino Pin | Connected To |
| ----------- | ------------ |
| 2           | CLK          |
| 3           | DT           |
| 4           | SW           |

---

# 🔄 Detecting Rotation Direction

The Arduino continuously monitors the CLK signal.

```cpp
currentstate = digitalRead(clk);
```

When CLK changes, the DT pin determines the direction.

Clockwise:

```cpp
counter++;
```

Counter-clockwise:

```cpp
counter--;
```

This allows the Arduino to know exactly which way the knob is turning.

---

# 🔢 Selecting Digits

The selected number is stored inside:

```cpp
counter
```

To keep the value between **0 and 9**, the counter wraps around automatically.

```cpp
if(counter > 9)
    counter = 0;

if(counter < 0)
    counter = 9;
```

```text
0 → 1 → 2 → ... → 9
↑                 ↓
└─────────────────┘
```

💡 This creates an infinite rotating menu.

---

# 🔘 Confirming a Digit

The encoder also contains a built-in pushbutton.

```cpp
pinMode(sw, INPUT_PULLUP);
```

Using `INPUT_PULLUP`:

```text
Released → HIGH
Pressed  → LOW
```

When the button is pressed:

```cpp
enteredcode[i] = counter;
```

The currently selected value becomes part of the password.

---

# 📺 LCD Display

The LCD guides the user throughout the password entry process.

Example:

```text
Digit 1/4
Value: 4
```

After verification:

```text
✅ Access Granted!
```

or

```text
❌ Wrong Password!
```

The LCD provides immediate visual feedback, making the project much easier to use.

---

# ⚙️ Servo Motor (The Lock)

The servo acts as the locking mechanism.

🔒 Initial position:

```cpp
myservo.write(0);
```

🔓 Correct password:

```cpp
myservo.write(90);
```

After **3 seconds**, it automatically returns to:

```cpp
myservo.write(0);
```

In a real project, the servo could move:

* 🔐 A latch
* 🚪 A small door lock
* 📦 A sliding bolt
* 🗄️ A miniature safe mechanism

---

# 📦 Why Arrays Are Used

Instead of storing:

```cpp
digit1
digit2
digit3
digit4
```

the project stores passwords inside arrays:

```cpp
passcode[4]
enteredcode[4]
```

This allows every digit to be checked using a single loop.

💡 If you wanted a **6-digit** or **8-digit** password, you would only need to change the array size.

---

# 🔌 Hardware

## 🎛️ HW-040 Rotary Encoder

| Pin | Arduino |
| --- | ------- |
| CLK | Pin 2   |
| DT  | Pin 3   |
| SW  | Pin 4   |
| VCC | 5V      |
| GND | GND     |

---

## 📺 LCD (16×2)

| LCD Pin | Arduino |
| ------- | ------- |
| RS      | 10      |
| E       | 9       |
| D4      | 8       |
| D5      | 7       |
| D6      | 6       |
| D7      | 5       |

---

## ⚙️ Servo Motor

| Servo Wire | Arduino                         |
| ---------- | ------------------------------- |
| Signal     | Pin 11                          |
| VCC        | 5V *(or external power supply)* |
| GND        | GND                             |

> ⚠️ **Important:** If the servo draws more current than the Arduino can safely provide, use an external power supply and connect its **GND** to the Arduino **GND**.

---

# 🚀 Possible Improvements

* 🔑 Allow users to change the password.
* 💾 Store the password in EEPROM.
* 🔔 Add a buzzer for feedback.
* 🚨 Lock the system after multiple incorrect attempts.
* 📱 Add Bluetooth or RFID authentication.
* 👆 Replace the rotary encoder with a fingerprint sensor.

---

# 📌 What You'll Learn

After completing this project, you'll understand:

* 🎛️ How a rotary encoder works.
* 🔄 How rotation direction is detected.
* 🔘 How to use the encoder's pushbutton.
* 📺 How to display information on a 16×2 LCD.
* 📦 How arrays simplify password storage.
* 🧠 How functions improve code organization.
* ⚙️ How a servo motor simulates a locking mechanism.
* 🔐 The fundamentals of electronic access control systems.

---

# 💡 Project Concept

```text
🔄 Rotate Encoder
        │
        ▼
🎛️ Select Current Digit
        │
        ▼
🔘 Press Button
        │
        ▼
💾 Store Digit
        │
        ▼
Repeat ×4
        │
        ▼
🔍 Compare Password
        │
   ┌────┴────┐
   ▼         ▼
✅ Correct   ❌ Wrong
   │         │
   ▼         ▼
🔓 Unlock   📺 Error
   │
   ▼
🔒 Auto Lock After 3 Seconds
```

This project combines **user input**, **password verification**, **LCD interaction**, and **servo motor control** into a complete embedded system. It is an excellent introduction to how electronic safes, smart locks, and access control systems work in real-world applications.
