# 🔐 Arduino Project 36 — Keypad Digital Door Lock

A password-protected digital locking system built with an **Arduino, 4×4 matrix keypad, servo motor, and LED**. The keypad is used to enter a password, while the servo acts as the physical locking mechanism.

---

## 📌 Project Overview

This project demonstrates how an Arduino can combine **user input, password validation, and physical movement** to create a simple electronic security system.

The system works as follows:

1. 🔢 Enter a password using the **4×4 keypad**.
2. `#` is used to **submit** the password.
3. `*` is used to **clear** the entered password.
4. ✅ If the password is correct:

   * The servo rotates to **90°**.
   * The LED turns ON.
   * The door remains unlocked for **3 seconds**.
   * The servo returns to **0°** and locks again.
5. ❌ If the password is incorrect:

   * The servo does not move.
   * The LED flashes **5 times**.
6. 💡 The LED also provides feedback whenever keys are pressed.

### 🔑 Default Password

```text
1234
```

The password is defined in the code:

```cpp
const String CORRECT_PASSWORD = "1234";
```

---

## 🧩 Components Used

| Component            | Purpose                    |
| -------------------- | -------------------------- |
| 🧠 Arduino           | Main controller            |
| 🔢 4×4 Matrix Keypad | Password input             |
| ⚙️ Servo Motor       | Physical locking mechanism |
| 💡 LED               | Status and user feedback   |
| 🔌 Jumper Wires      | Connections                |

---

# 🔢 1. 4×4 Matrix Keypad

The most important input device in this project is the **4×4 matrix keypad**.

It contains **16 buttons** arranged as:

```text
┌─────┬─────┬─────┬─────┐
│  1  │  2  │  3  │  A  │
├─────┼─────┼─────┼─────┤
│  4  │  5  │  6  │  B  │
├─────┼─────┼─────┼─────┤
│  7  │  8  │  9  │  C  │
├─────┼─────┼─────┼─────┤
│  *  │  0  │  #  │  D  │
└─────┴─────┴─────┴─────┘
```

Although there are **16 buttons**, the keypad does not require 16 Arduino pins.

Instead, it uses:

* **4 row pins**
* **4 column pins**

Total:

```text
4 + 4 = 8 pins
```

This is called a **matrix keypad**.

---

## 🧠 How Matrix Keypads Work

Each button connects one **row** to one **column** when it is pressed.

For example:

```text
        C1   C2   C3   C4
        │    │    │    │
R1 ─────1────2────3────A
R2 ─────4────5────6────B
R3 ─────7────8────9────C
R4 ─────*────0────#────D
```

For example, pressing `5` connects:

```text
R2 + C2
```

The Arduino can determine which key was pressed by scanning the rows and columns.

This is much more efficient than connecting every button individually.

---

# 📚 Keypad Library

The project uses:

```cpp
#include <Keypad.h>
```

The **Keypad library** handles the matrix scanning for us.

Without the library, we would need to manually:

1. Configure rows and columns.
2. Activate one row at a time.
3. Read the columns.
4. Determine which button is pressed.
5. Deal with button bouncing.
6. Convert the row/column combination into a character.

The library provides convenient functions that handle most of this work.

---

## 🗺️ Keypad Configuration

The button layout is defined here:

```cpp
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
```

This tells the library which character belongs to each row/column position.

The dimensions are:

```cpp
const byte ROWS = 4;
const byte COLS = 4;
```

The physical Arduino pins are then assigned:

```cpp
byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};
```

So:

### Rows

```text
R1 → Arduino 9
R2 → Arduino 8
R3 → Arduino 7
R4 → Arduino 6
```

### Columns

```text
C1 → Arduino 5
C2 → Arduino 4
C3 → Arduino 3
C4 → Arduino 2
```

---

## ⚙️ Creating the Keypad Object

```cpp
Keypad keypad = Keypad(
  makeKeymap(keys),
  rowPins,
  colPins,
  ROWS,
  COLS
);
```

This creates a `Keypad` object and tells the library:

* what characters exist,
* which pins are rows,
* which pins are columns,
* how many rows there are,
* how many columns there are.

---

## 🔍 `keypad.getKey()`

The main function used to read the keypad is:

```cpp
char key = keypad.getKey();
```

If no key is pressed:

```text
key → NO_KEY
```

If a key is pressed:

```text
key → '1'
key → '5'
key → 'A'
key → '#'
```

Therefore:

```cpp
if (key) {
```

means:

> "If a key was detected, process it."

---

# 🔐 2. Password System

The correct password is stored in:

```cpp
const String CORRECT_PASSWORD = "1234";
```

The currently entered password is stored in:

```cpp
String inputPassword = "";
```

When the user presses a normal key:

```cpp
inputPassword += key;
```

For example:

```text
Press 1
↓
"1"

Press 2
↓
"12"

Press 3
↓
"123"

Press 4
↓
"1234"
```

Then pressing `#` calls:

```cpp
checkPassword();
```

---

# #️⃣ Submit Button

The `#` key acts as the **Enter/Submit** button.

```cpp
if (key == '#') {
  checkPassword();
}
```

The password is then compared:

```cpp
if (inputPassword == CORRECT_PASSWORD)
```

If:

```text
inputPassword = "1234"
CORRECT_PASSWORD = "1234"
```

the condition is true.

---

# ⭐ Clear Button

The `*` key works as a **Clear/Reset** button:

```cpp
else if (key == '*') {
  inputPassword = "";
  flashLED(2, 100);
}
```

For example:

```text
Entered: 128
Press *
Result: ""
```

This allows the user to correct their input without submitting the wrong password.

---

# ⚙️ Password Length Limit

The program contains:

```cpp
if (inputPassword.length() < 8) {
  inputPassword += key;
}
```

This means the user can enter a maximum of **8 characters** before pressing `#`.

The actual password can still be shorter, such as:

```text
1234
```

---

# ⚙️ 3. Servo Motor — Electronic Lock

The servo is used as the physical locking mechanism.

```cpp
Servo doorLock;
```

The library is included with:

```cpp
#include <Servo.h>
```

The servo is connected to:

```cpp
const int SERVO_PIN = 10;
```

Two positions are defined:

```cpp
const int LOCKED_POS = 0;
const int UNLOCKED_POS = 90;
```

So:

```text
0°  → 🔒 Locked
90° → 🔓 Unlocked
```

---

## 🔧 Initial Servo Position

During `setup()`:

```cpp
doorLock.attach(SERVO_PIN);
doorLock.write(LOCKED_POS);
```

This connects the Servo library to Arduino pin 10 and immediately moves the servo to:

```text
0°
```

Therefore, when the Arduino starts, the lock begins in the **locked position**.

---

## 🔓 Unlocking

When the correct password is entered:

```cpp
doorLock.write(UNLOCKED_POS);
```

The servo moves to:

```text
90°
```

The lock is therefore opened.

The program then waits:

```cpp
delay(3000);
```

After 3 seconds:

```cpp
doorLock.write(LOCKED_POS);
```

The servo returns to:

```text
0°
```

and the door locks again.

### Sequence

```text
🔢 Enter 1234
       ↓
   # Submit
       ↓
   ✅ Correct
       ↓
Servo → 90°
       ↓
   🔓 UNLOCK
       ↓
   Wait 3 sec
       ↓
Servo → 0°
       ↓
   🔒 LOCK
```

---

# 💡 4. LED Feedback

The LED is connected to:

```cpp
const int LED_PIN = 13;
```

It provides visual feedback to the user.

### Correct password

```cpp
digitalWrite(LED_PIN, HIGH);
```

The LED stays ON while the lock is unlocked.

### Incorrect password

```cpp
flashLED(5, 80);
```

The LED flashes five times.

### Key pressed

```cpp
flashLED(1, 50);
```

The LED gives one short flash.

### Clear button

```cpp
flashLED(2, 100);
```

The LED flashes twice.

---

# 🔄 `flashLED()` Function

Instead of repeatedly writing the same LED code, a separate function was created:

```cpp
void flashLED(int times, int speedMs)
```

For example:

```cpp
flashLED(5, 80);
```

means:

```text
5 flashes
80 ms ON
80 ms OFF
```

The function contains:

```cpp
for (int i = 0; i < times; i++) {
  digitalWrite(LED_PIN, HIGH);
  delay(speedMs);
  digitalWrite(LED_PIN, LOW);
  delay(speedMs);
}
```

This is a good example of **code reuse**.

---

# 🧠 Complete Program Logic

The overall program can be represented as:

```text
          🔌 Arduino starts
                 │
                 ▼
          🔒 Servo → 0°
                 │
                 ▼
        🔢 Wait for keypad
                 │
        ┌────────┼────────┐
        ▼        ▼        ▼
      Normal     *        #
       key      Clear    Submit
        │        │        │
        ▼        ▼        ▼
    Add key    Reset    Check
        │        │      password
        │        │        │
        │        │    ┌───┴────┐
        │        │    ▼        ▼
        │        │   ✅       ❌
        │        │ Correct   Wrong
        │        │    │        │
        │        │    ▼        ▼
        │        │ Servo 90°  💡💡💡💡💡
        │        │    │
        │        │  3 sec
        │        │    │
        │        │    ▼
        │        │ Servo 0°
        │        │
        └────────┴──────────────► Repeat
```

---

# 🔌 Pin Configuration

| Component       | Arduino Pin | Purpose              |
| --------------- | ----------: | -------------------- |
| Keypad Row 1    |          D9 | Matrix row           |
| Keypad Row 2    |          D8 | Matrix row           |
| Keypad Row 3    |          D7 | Matrix row           |
| Keypad Row 4    |          D6 | Matrix row           |
| Keypad Column 1 |          D5 | Matrix column        |
| Keypad Column 2 |          D4 | Matrix column        |
| Keypad Column 3 |          D3 | Matrix column        |
| Keypad Column 4 |          D2 | Matrix column        |
| Servo           |         D10 | Servo control signal |
| LED             |         D13 | Status indicator     |

---

# 📚 Libraries Used

### `Keypad.h`

Used for communicating with the **4×4 matrix keypad**.

Important functionality:

```cpp
makeKeymap()
```

Creates a keypad character mapping.

```cpp
keypad.getKey()
```

Checks whether a key has been pressed and returns its character.

---

### `Servo.h`

Used to control the servo motor.

Important functions:

```cpp
doorLock.attach(10);
```

Connects the Servo object to Arduino pin 10.

```cpp
doorLock.write(0);
```

Moves the servo to approximately 0°.

```cpp
doorLock.write(90);
```

Moves the servo to approximately 90°.

The Servo library handles the timing of the control signal required by the servo, so we don't have to manually generate the servo pulses.

---

# 🔋 Power Considerations

The **servo motor should be treated separately from the Arduino's logic circuitry when designing a larger or more reliable lock**.

Servos can draw significantly more current when:

* starting to move,
* changing direction,
* carrying a mechanical load,
* being held against resistance.

If the servo causes the Arduino to reset or behave unpredictably, use an appropriate external power supply for the servo and connect the grounds together.

For a real door-lock mechanism, also use a mechanically appropriate actuator rather than relying on a small hobby servo to hold a physical door securely.

---

# 🧪 Example Interaction

### Correct Password

```text
🔢 1
🔢 2
🔢 3
🔢 4
#️⃣

       ↓

✅ PASSWORD CORRECT
💡 LED ON
🔓 Servo → 90°
⏳ 3 seconds
🔒 Servo → 0°
```

### Wrong Password

```text
🔢 1
🔢 2
🔢 5
🔢 6
#️⃣

       ↓

❌ WRONG PASSWORD
💡💡💡💡💡
🔒 Servo remains locked
```

### Clearing Input

```text
🔢 1
🔢 2
🔢 8
⭐ *

       ↓

Input cleared
💡💡
```

---

## 🎯 What This Project Demonstrates

This project combines several important Arduino concepts:

* 🔢 **Matrix keypad scanning**
* 📚 **Using external Arduino libraries**
* 🔐 **Password validation**
* 🧠 **String handling**
* ⚙️ **Servo motor control**
* 💡 **LED feedback**
* 🔄 **Functions and loops**
* 🧩 **Combining multiple hardware components**
* 🔌 **Digital input and output**
* 🏗️ **Designing a simple embedded security system**

> **Project 36 — Keypad Digital Door Lock** demonstrates how a simple Arduino program can turn a keypad into a user interface and a servo into a physical security mechanism.
