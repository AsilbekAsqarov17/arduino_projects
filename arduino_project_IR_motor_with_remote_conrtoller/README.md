# Arduino Project 28: IR Remote Controlled DC Motor (ON/OFF Toggle)

This project demonstrates how to control a **DC motor wirelessly** using an **IR remote control**, an **IR receiver**, and an **L293D motor driver**. Pressing a specific button on the remote toggles the motor between **ON** and **OFF**, allowing the motor to start or stop without any physical switches.

The Arduino continuously listens for infrared signals from the remote. When the predefined command is received, it changes the motor's state and drives the motor through the L293D motor driver.

```text
IR Remote
     ↓
IR Receiver
     ↓
Arduino Uno
     ↓
L293D Motor Driver
     ↓
DC Motor
```

---

# How It Works

The IR receiver detects infrared signals emitted by the remote control.

The **IRremote** library decodes the received signal into a unique hexadecimal command.

```cpp
IrReceiver.decode();
```

The program then checks whether the received command matches the desired button:

```cpp
if(IrReceiver.decodedIRData.command == 0x45)
```

If the correct button is pressed, the variable controlling the motor state is toggled:

```cpp
if(isSpinning == 0){
    isSpinning = 1;
}
else{
    isSpinning = 0;
}
```

This creates a **toggle switch**, where one press turns the motor ON and the next press turns it OFF.

Unlike a pushbutton that requires physical contact, the IR remote allows the motor to be controlled remotely using infrared light.

---

# Toggle Logic

Instead of holding a button to keep the motor running, this project remembers the previous state.

```text
First Press
OFF → ON

Second Press
ON → OFF

Third Press
OFF → ON
```

This behavior is implemented using the variable:

```cpp
int isSpinning = 0;
```

where:

```text
0 = Motor OFF
1 = Motor ON
```

---

# Controlling the Motor

When the motor is enabled:

```cpp
digitalWrite(input1Pin, HIGH);
digitalWrite(input2Pin, LOW);
analogWrite(enablePin, 255);
```

The L293D receives:

* **IN1 = HIGH**
* **IN2 = LOW**

which determines the rotation direction.

The Enable pin receives:

```cpp
analogWrite(enablePin, 255);
```

which applies full speed (100% PWM).

When the motor is turned OFF:

```cpp
digitalWrite(input1Pin, LOW);
digitalWrite(input2Pin, LOW);
analogWrite(enablePin, 0);
```

both direction pins are LOW and the enable signal is removed, stopping the motor.

---

# IR Remote Communication

An infrared remote control sends digital commands by rapidly flashing an infrared LED.

Although the light is invisible to the human eye, the IR receiver can detect these flashes and convert them into digital data.

The IRremote library decodes this information automatically.

In this project, the button used has the hexadecimal command:

```text
0x45
```

Whenever this command is received, the Arduino toggles the motor state.

The Serial Monitor also displays useful debugging information:

```text
Protocol: NEC
Command: 0x45
Motor: ON
```

or

```text
Protocol: NEC
Command: 0x45
Motor: OFF
```

This makes it easy to verify that the correct command is being received.

---

# L293D Motor Driver

Since an Arduino pin cannot safely supply enough current to power a DC motor directly, an **L293D motor driver** is used.

The L293D acts as an interface between the Arduino and the motor.

Its responsibilities include:

* Driving motors with higher current than the Arduino can provide.
* Controlling motor direction.
* Controlling motor speed using PWM.
* Protecting the Arduino from motor current.

In this project, only one direction is used, but the L293D is capable of driving the motor in both directions.

---

# PWM Speed Control

Although this project always runs the motor at full speed:

```cpp
analogWrite(enablePin, 255);
```

the Enable pin supports **Pulse Width Modulation (PWM)**.

PWM allows the average voltage supplied to the motor to be adjusted.

Examples:

```text
analogWrite(enablePin, 255); → 100% speed
analogWrite(enablePin, 180); → ~70% speed
analogWrite(enablePin, 128); → ~50% speed
analogWrite(enablePin, 64);  → ~25% speed
analogWrite(enablePin, 0);   → Motor stopped
```

This means the project can easily be expanded to include multiple speed levels.

---

# Hardware

## IR Receiver

| Pin | Connection | Purpose                            |
| --- | ---------- | ---------------------------------- |
| VCC | 5V         | Power                              |
| GND | GND        | Ground                             |
| OUT | Pin 4      | Sends decoded IR signal to Arduino |

---

## L293D Motor Driver

| Pin    | Arduino Pin | Purpose           |
| ------ | ----------- | ----------------- |
| Enable | 11          | PWM speed control |
| IN1    | 10          | Motor direction   |
| IN2    | 9           | Motor direction   |

---

## DC Motor

The DC motor is connected to the output terminals of the L293D motor driver.

The motor receives its power through the driver instead of directly from the Arduino.

> **Note:** If the motor requires more current than the Arduino's 5V pin can safely provide, use an external power supply. Remember to connect the external power supply's **GND** to the Arduino **GND** so both circuits share a common reference.

---

# IRremote Library

This project uses the **IRremote** library to simplify infrared communication.

Some important functions used include:

```cpp
IrReceiver.begin(receiverPin, ENABLE_LED_FEEDBACK);
```

Initializes the IR receiver.

```cpp
IrReceiver.decode();
```

Checks whether a complete IR signal has been received.

```cpp
IrReceiver.decodedIRData.command
```

Returns the decoded command value.

```cpp
IrReceiver.getProtocolString();
```

Returns the communication protocol used by the remote (such as NEC).

```cpp
IrReceiver.resume();
```

Resets the receiver so it can process the next incoming command.

Without calling `resume()`, the receiver would not detect any further button presses.

---

# Possible Improvements

This project provides a foundation for many future enhancements, including:

* 🎚️ Multiple motor speed levels using different remote buttons.
* 🔄 Forward and reverse rotation control.
* ⏱️ Timer-based automatic shutoff.
* 📺 LCD or OLED display showing the current motor status.
* 🌡️ Temperature monitoring to prevent motor overheating.
* 📡 Wireless control of multiple motors using a single remote.

---

# Project Concept

This project combines **infrared communication**, **digital signal processing**, and **motor control** into one simple application.

```text
        IR Remote
             │
             ▼
      IR Receiver Module
             │
             ▼
       Arduino Uno
             │
             ▼
      Toggle ON / OFF
             │
             ▼
      L293D Motor Driver
             │
             ▼
          DC Motor
```

By combining the **IRremote** library with the **L293D motor driver**, this project demonstrates how wireless input can be used to control physical hardware. It also introduces the concept of **state-based programming**, where the Arduino remembers the previous state of the motor and changes it with each button press rather than responding only while the button is held.
