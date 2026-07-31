# 📡 Arduino Project 31: RFID Access Control System Using MFRC522 and SPI Communication

This project demonstrates a simple **RFID-based access control system** using the **MFRC522 RFID reader**, an **RFID card (or key fob)**, and two LEDs to indicate whether access is granted or denied.

When an RFID tag is brought near the reader, the Arduino reads the card's **Unique Identifier (UID)** through the **SPI (Serial Peripheral Interface)** communication protocol. The UID is then compared with a predefined authorized UID stored in the program.

If the scanned UID matches the authorized one, the **green LED** lights up, indicating successful authentication. Otherwise, the **red LED** lights up to indicate access denial.

This project introduces one of the most common identification technologies used in modern security systems and provides an excellent introduction to **RFID**, **SPI communication**, and **hardware interfaces**.

```text
📇 RFID Card / Key Fob
          │
          ▼
📡 MFRC522 RFID Reader
          │
   SPI Hardware Protocol
          │
          ▼
🧠 Arduino Uno
          │
     ┌────┴────┐
     ▼         ▼
🟢 Access   🔴 Access
 Granted     Denied
```

---

# ⚙️ How It Works

When the Arduino powers on, it initializes the SPI communication bus and prepares the MFRC522 reader.

```cpp
SPI.begin();
mfrc522.PCD_Init();
```

The program continuously waits for an RFID tag.

```cpp
mfrc522.PICC_IsNewCardPresent()
```

If no card is detected, the loop simply starts again.

Once a card enters the reader's magnetic field, the Arduino reads its UID.

```cpp
mfrc522.PICC_ReadCardSerial();
```

Example output:

```text
Card Type: MIFARE 1K
Card UID: 90 3F F9 55
```

The scanned UID is then compared against the authorized UID stored inside the code.

If they match:

```text
✅ Access Granted!
🟢 Green LED ON
```

Otherwise:

```text
❌ Access Denied!
🔴 Red LED ON
```

---

# 📡 What is RFID?

**RFID (Radio Frequency Identification)** is a wireless technology used to identify objects without physical contact.

Unlike barcodes, RFID tags do not need to be directly visible to the reader. They communicate using **radio waves**, allowing data to be exchanged quickly and reliably.

An RFID system typically consists of three components:

* 📇 RFID Tag (Card or Key Fob)
* 📡 RFID Reader (MFRC522)
* 🧠 Microcontroller (Arduino)

When a tag enters the reader's electromagnetic field:

1. 📡 The reader generates a radio frequency field.
2. ⚡ The passive RFID tag receives power from this field.
3. 📨 The tag sends its stored UID back to the reader.
4. 🧠 The Arduino processes the received UID.

---

# 📇 RFID Tags

Most beginner RFID kits include **MIFARE Classic** cards or key fobs operating at **13.56 MHz**.

Each tag contains a unique identification number called the **UID (Unique Identifier)**.

Example:

```text
90 3F F9 55
```

This UID works similarly to a fingerprint—it uniquely identifies the card being scanned.

In this project, the authorized UID is:

```cpp
"90 3F F9 55"
```

Only this card is allowed to "unlock" the system.

---

# 📡 MFRC522 RFID Reader

The **MFRC522** is a popular RFID reader module designed for **13.56 MHz** RFID tags.

It handles all of the low-level radio communication with RFID cards, allowing the Arduino to simply request information such as the card type and UID.

### ✨ Main Features

* 📡 Reads 13.56 MHz RFID cards
* 📇 Reads UID of RFID tags
* 💾 Can read and write compatible RFID memory blocks
* ⚡ Low power consumption
* 🚀 Fast communication using SPI

---

# 🔌 MFRC522 Pins

| MFRC522 Pin | Arduino Uno |
| ----------- | ----------- |
| SDA (SS)    | Pin 10      |
| SCK         | Pin 13      |
| MOSI        | Pin 11      |
| MISO        | Pin 12      |
| RST         | Pin 9       |
| 3.3V        | 3.3V ⚠️     |
| GND         | GND         |

> ⚠️ **Important:** The MFRC522 module is designed to operate at **3.3V**, **not 5V**. Connecting VCC directly to 5V may permanently damage the module. Always power it from the Arduino's **3.3V pin**.

---

# 🛰️ Understanding SPI (Serial Peripheral Interface)

One of the most important concepts in this project is **SPI (Serial Peripheral Interface)**.

SPI is a **hardware communication protocol** designed for extremely fast communication between a **master** device and one or more **slave** devices.

In this project:

* 🧠 Arduino Uno → Master
* 📡 MFRC522 → Slave

Unlike **I²C**, where all devices share one data line, SPI uses separate lines for sending and receiving data simultaneously. This makes SPI one of the fastest communication protocols available on Arduino.

```text
          🧠 Arduino (Master)
                 │
 ┌───────────────┼───────────────┐
 │               │               │
 ▼               ▼               ▼
MOSI           MISO            SCK
 │               ▲               │
 └───────────────┼───────────────┘
                 │
                 ▼
          📡 MFRC522 (Slave)
```

---

# 📚 SPI Signal Lines

SPI communication uses four primary signals.

## 📨 MOSI (Master Out Slave In)

Data travels **from the Arduino to the RFID module**.

The Arduino uses this line whenever it needs to send commands.

Example:

```text
Arduino ─────────► MFRC522
```

---

## 📥 MISO (Master In Slave Out)

Data travels **from the RFID module back to the Arduino**.

The UID received from the RFID card ultimately reaches the Arduino through this line.

```text
Arduino ◄───────── MFRC522
```

---

## ⏱️ SCK (Serial Clock)

The clock synchronizes communication.

Every pulse generated by the Arduino tells both devices exactly when to transmit the next bit of information.

Without the clock, both devices would lose synchronization.

---

## 🎯 SS (Slave Select)

The **Slave Select (SS)** pin tells the Arduino which SPI device it wants to communicate with.

Since multiple SPI devices can share the same bus, only the device whose SS pin is LOW responds to communication.

In this project:

```cpp
#define ss 10
```

Pin **10** selects the MFRC522 module.

---

# ⚡ Hardware SPI on Arduino Uno

Unlike protocols that rely entirely on software, SPI is built directly into the ATmega328P microcontroller used on the Arduino Uno.

This dedicated hardware allows data to be transferred much faster and more efficiently than manually toggling digital pins.

The SPI pins are fixed:

| Arduino Pin | SPI Function      |
| ----------- | ----------------- |
| 10          | SS (Slave Select) |
| 11          | MOSI              |
| 12          | MISO              |
| 13          | SCK               |

Because these pins are connected directly to the microcontroller's SPI hardware, they **cannot be reassigned** like ordinary digital pins when using the hardware SPI interface.

---

# 📚 Libraries Used

## 📦 SPI.h

```cpp
#include <SPI.h>
```

This is Arduino's built-in library for communicating with SPI devices.

It configures the hardware SPI peripheral inside the microcontroller and manages data transfers.

The most important function used in this project is:

```cpp
SPI.begin();
```

This initializes the SPI hardware and prepares the Arduino to communicate with SPI devices such as the MFRC522.

---

## 📦 MFRC522.h

```cpp
#include <MFRC522.h>
```

This library builds on top of `SPI.h` and provides convenient, high-level functions specifically for the MFRC522 RFID reader.

Instead of manually sending raw SPI commands and decoding responses, the library handles these tasks internally, allowing you to interact with the reader using simple function calls.

---

# 🛠️ Important Functions

### 📡 Initialize the RFID reader

```cpp
mfrc522.PCD_Init();
```

Configures the MFRC522 and prepares it for operation.

---

### 📇 Detect a new RFID tag

```cpp
mfrc522.PICC_IsNewCardPresent();
```

Checks whether a new RFID card has entered the reader's field.

Returns `true` only when a new card is detected.

---

### 📖 Read the card's UID

```cpp
mfrc522.PICC_ReadCardSerial();
```

Retrieves the UID and stores it in the library's internal data structure.

---

### 🏷️ Determine the card type

```cpp
mfrc522.PICC_GetType()
```

Returns the detected RFID tag type, such as **MIFARE Classic 1K**.

---

### 🛑 End communication

```cpp
mfrc522.PICC_HaltA();
```

Stops communication with the current RFID tag.

---

### 🔒 Stop encrypted communication

```cpp
mfrc522.PCD_StopCrypto1();
```

Disables the reader's cryptographic session, ensuring the module is ready for the next card.

---

# 💡 Green and Red LEDs

The LEDs provide immediate visual feedback.

🟢 **Green LED**

* ✅ Authorized card detected
* 🔓 Access granted
* 💚 Lights for three seconds

🔴 **Red LED**

* ❌ Unknown card detected
* 🚫 Access denied
* ❤️ Lights for three seconds

Using LEDs makes the system easier to understand without constantly watching the Serial Monitor.

---

# 📚 Concepts Learned

After completing this project, you'll understand:

* 📡 How RFID identification works.
* 📇 What a UID is and how it is used for authentication.
* 🛰️ How the SPI hardware protocol transfers data.
* ⚡ The difference between hardware communication and software processing.
* 📚 How external libraries simplify complex hardware interactions.
* 💡 How LEDs provide user feedback in embedded systems.
* 🔐 The basic principles behind RFID-based access control systems.

---

# 🚀 Possible Improvements

* 🔒 Control a servo motor to create an electronic door lock.
* 📺 Display the user's status on a 16×2 LCD or OLED display.
* 🔔 Add a buzzer for audible feedback.
* 💾 Store multiple authorized UIDs in EEPROM.
* 🌐 Connect to Wi-Fi and log entry attempts.
* 📱 Send notifications when unauthorized cards are scanned.
* 👥 Implement multiple user access levels.

---

# 📌 Project Concept

```text
📇 RFID Card
      │
      ▼
📡 MFRC522 Reader
      │
      ▼
🛰️ SPI Communication
      │
      ▼
🧠 Arduino Uno
      │
      ▼
🔍 Compare UID
      │
 ┌────┴────┐
 ▼         ▼
✅ Match   ❌ No Match
 │          │
 ▼          ▼
🟢 Green   🔴 Red
 LED        LED
```

This project introduces one of the most widely used technologies in modern access control systems. By combining **RFID identification**, **SPI hardware communication**, **external libraries**, and **visual feedback**, it demonstrates how embedded systems authenticate users and make real-time access decisions. The same principles are used in office entry systems, hotel key cards, public transportation passes, and contactless payment devices.
