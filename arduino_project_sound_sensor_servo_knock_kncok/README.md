# 🔐 Digital Safe — 3-Knock Pattern Lock

## 📌 Project Overview

This project creates a simple **digital safe controlled by a knock pattern**. Instead of using a keypad, RFID card, or password, the user unlocks the safe by making **exactly 3 knocks within 1.5 seconds**.

The system uses:

* 👂 **Sound / vibration sensor** — detects knocks
* ⚙️ **Servo motor** — physically locks and unlocks the safe
* 🔋 **Capacitor** — helps stabilize the Arduino's 5V power line when the servo moves
* 🧠 **Arduino** — processes the knock pattern and controls the servo

### 🔑 Unlock Pattern

> **3 knocks within 1.5 seconds = Access Granted ✅**

Any other number of knocks is rejected:

```text
1 knock   ❌
2 knocks  ❌
3 knocks  ✅ OPEN/CLOSE
4 knocks  ❌
5+ knocks ❌
```

The system also requires the knocks to be separated enough to avoid counting one physical knock multiple times.

---

# 🧩 Components

| Component            | Purpose                            |
| -------------------- | ---------------------------------- |
| Arduino              | Main controller                    |
| Sound / Piezo Sensor | Detects vibrations and knocks      |
| Servo Motor          | Moves the safe's locking mechanism |
| Capacitor            | Stabilizes the 5V power supply     |
| Jumper Wires         | Connections                        |
| Safe mechanism       | Physical locking system            |

---

# 👂 1. Sound / Vibration Sensor

The sensor is connected to:

```cpp
const int soundPin = A0;
```

The Arduino reads its analog signal using:

```cpp
analogRead(soundPin);
```

A knock produces a short vibration, which creates a larger change in the sensor's analog output.

Instead of looking at only one analog reading, the project measures the signal for a short period:

```cpp
while (millis() - startMillis < 25) {
    int sample = analogRead(soundPin);
    ...
}
```

During these 25 ms, the program records:

* 📈 Highest signal value
* 📉 Lowest signal value

Then it calculates:

```cpp
int peakToPeak = signalMax - signalMin;
```

### 📊 Peak-to-Peak Measurement

For example, if the sensor produces:

```text
Minimum = 420
Maximum = 550
```

then:

```text
Peak-to-Peak = 550 - 420
             = 130
```

A larger value indicates a stronger vibration.

The project uses:

```cpp
const int threshold = 100;
```

Therefore:

```text
Peak-to-Peak > 100 → Knock detected
Peak-to-Peak ≤ 100 → Ignore
```

This approach is useful because the sensor naturally produces small fluctuations even when nobody is knocking.

---

# 🔊 Why Peak-to-Peak Instead of One Reading?

A sound or vibration sensor does not necessarily produce one clean value when a knock occurs.

The signal can look approximately like:

```text
        /\ 
       /  \      /\
______/    \____/  \____
```

The Arduino captures the highest and lowest values during a short sampling window.

Therefore:

```text
Peak-to-Peak = Maximum - Minimum
```

gives an indication of how strongly the sensor signal changed.

This makes the system more suitable for detecting short vibration events such as knocking.

---

# ⚙️ 2. Servo Motor

The servo is connected to:

```cpp
const int servoPin = 9;
```

and controlled using:

```cpp
#include <Servo.h>
```

The servo object is:

```cpp
Servo myServo;
```

It is attached with:

```cpp
myServo.attach(servoPin);
```

The initial position is:

```cpp
myServo.write(0);
```

So the safe starts in the **locked position**.

When the correct pattern is detected:

```cpp
myServo.write(90);
```

the servo moves to 90° and opens the lock.

---

## 🔄 Lock State

The project uses:

```cpp
bool isOpen = false;
```

This remembers whether the safe is currently open.

When exactly three knocks are detected:

```cpp
isOpen = !isOpen;
myServo.write(isOpen ? 90 : 0);
```

The `!` operator reverses the state:

```text
false → true
true  → false
```

Therefore, the same three-knock pattern works as a **toggle**:

```text
🔒 Locked
   ↓
👊 👊 👊
   ↓
🔓 Unlocked
   ↓
👊 👊 👊
   ↓
🔒 Locked
```

---

# 🔋 3. Why a Capacitor Is Used

The capacitor is connected across the Arduino's:

```text
5V ──── Capacitor ──── GND
```

power lines.

The servo and sound sensor are also connected to this same power rail.

### Why?

A servo can require a relatively large amount of current when it starts moving, especially if it is under mechanical load.

The Arduino's 5V supply may experience a temporary voltage drop when the servo suddenly demands current.

This can cause:

* ⚠️ Arduino resets
* ⚠️ Sensor readings becoming unstable
* ⚠️ Servo jitter
* ⚠️ Unexpected behavior

The capacitor acts as a small temporary energy reservoir.

Conceptually:

```text
                 ┌── Servo
                 │
5V ──────────────┼── Sound Sensor
                 │
                 └── Capacitor
                         │
GND ─────────────────────┘
```

When the power line is stable, the capacitor stores charge.

When the servo suddenly demands current, the capacitor can help supply some of that transient demand and reduce short voltage fluctuations.

### ⚠️ Important

A capacitor **does not replace a proper external power supply** for a servo that requires more current than the Arduino can safely provide.

For larger servos or heavily loaded mechanisms, an external regulated 5V supply is generally the better solution, with **common ground** between the external supply and Arduino.

---

# ⏱️ 4. Detecting Individual Knocks

The project contains:

```cpp
unsigned long lastKnockTime = 0;
```

and checks:

```cpp
if (now - lastKnockTime > 120)
```

This creates a **120 ms debounce / separation period**.

Why is this necessary?

A single physical knock may cause several rapid vibrations:

```text
REAL KNOCK
    ↓
sensor vibration
    ↓
signal spike
    ↓
another small spike
    ↓
another spike
```

Without protection, the Arduino could interpret:

```text
👊
```

as:

```text
👊 👊 👊
```

The 120 ms guard prevents extremely close signals from being counted as separate knocks.

---

# 🔢 5. Counting the Knocks

Every valid knock increases:

```cpp
knockCount++;
```

For example:

```text
First knock  → count = 1
Second knock → count = 2
Third knock  → count = 3
```

When the first knock occurs, the program stores its time:

```cpp
firstKnockTime = now;
```

This starts the **1.5-second evaluation window**.

---

# ⏱️ 6. The 1.5-Second Pattern Window

The code checks:

```cpp
if (knockCount > 0 && (millis() - firstKnockTime > 1500))
```

This means:

> Once the first knock happens, the Arduino gives the user 1.5 seconds to complete the pattern.

After that period, the Arduino evaluates the result.

### Correct Pattern

```text
0.0s       0.5s       1.0s
 👊          👊          👊
 │           │           │
 └───────────┴───────────┘
       within 1.5 sec

          ✅ ACCESS
```

### Too Few Knocks

```text
👊       👊
──────────────→ 1.5 sec

❌ ACCESS DENIED
```

### Too Many Knocks

```text
👊 👊 👊 👊
──────────────→ 1.5 sec

❌ ACCESS DENIED
```

The condition is deliberately:

```cpp
if (knockCount == 3)
```

rather than:

```cpp
if (knockCount >= 3)
```

This makes the security pattern **strict**.

---

# 🔐 7. Access Control Logic

The complete decision is essentially:

```text
            Knock detected
                  │
                  ▼
          Start 1.5s timer
                  │
                  ▼
          Count valid knocks
                  │
                  ▼
            Timer expires
                  │
          ┌───────┴───────┐
          │               │
      Count == 3       Count != 3
          │               │
          ▼               ▼
     ✅ GRANTED         ❌ DENIED
          │
          ▼
    Toggle servo
    0° ↔ 90°
```

---

# 🧠 8. Why `millis()` Is Used

The project uses:

```cpp
millis()
```

instead of relying entirely on long `delay()` calls.

`millis()` returns the number of milliseconds since the Arduino started running.

For example:

```cpp
millis() - firstKnockTime
```

tells us how much time has passed since the first knock.

This allows the program to continue sampling the sensor while the 1.5-second pattern window is active.

---

# 📡 9. Serial Monitor

The project communicates with the computer at:

```cpp
Serial.begin(115200);
```

When a knock is detected, it prints:

```text
Knock detected! Total count: 1
Knock detected! Total count: 2
Knock detected! Total count: 3
```

If exactly three knocks were detected:

```text
>>> ACCESS GRANTED (Exact 3 knocks)! Toggling lock... <<<
```

Otherwise:

```text
>>> ACCESS DENIED! Knock count was: 2
```

This is useful for debugging the sensor and adjusting the threshold.

---

# 🛠️ 10. Adjusting the Sensitivity

The most important parameter for the sound sensor is:

```cpp
const int threshold = 100;
```

The correct value depends on the actual sensor, its sensitivity, mounting surface, and environment.

For example:

### Too sensitive

If random sounds trigger the safe:

```cpp
threshold = 150;
```

or higher may help.

### Not sensitive enough

If normal knocks are not detected:

```cpp
threshold = 70;
```

or another lower value may work better.

The exact number is **hardware-dependent**.

Different sound sensors, microphones, piezo elements, mounting surfaces, and electrical conditions can produce very different analog values.

---

# 🔌 Pin Connections

| Component        |          Arduino Pin | Purpose                 |
| ---------------- | -------------------: | ----------------------- |
| Sound Sensor OUT |                   A0 | Analog vibration signal |
| Sound Sensor VCC |                   5V | Power                   |
| Sound Sensor GND |                  GND | Ground                  |
| Servo Signal     |                   D9 | Servo control           |
| Servo VCC        | 5V / suitable supply | Servo power             |
| Servo GND        |                  GND | Common ground           |
| Capacitor +      |                   5V | Power stabilization     |
| Capacitor −      |                  GND | Power stabilization     |

> ⚠️ If using an electrolytic capacitor, polarity matters: the `+` terminal goes to 5V and the `−` terminal goes to GND.

---

# 🧪 11. How the Complete System Works

### Step 1 — Startup

The servo moves to:

```text
0°
```

which represents the locked position.

### Step 2 — Listen

The Arduino continuously samples the sound/vibration sensor.

### Step 3 — Detect

The Arduino calculates the peak-to-peak signal.

```text
Peak-to-Peak > 100
        ↓
   Knock detected
```

### Step 4 — Count

Valid knocks are counted while the 1.5-second window is active.

### Step 5 — Verify

After 1.5 seconds:

```text
Exactly 3 → ✅
Anything else → ❌
```

### Step 6 — Actuate

If correct:

```text
Servo 0° → 90°
```

If the safe was already open, it changes back:

```text
Servo 90° → 0°
```

### Step 7 — Reset

The knock counter returns to zero and the system waits for another attempt.

---

# 🧠 Main Programming Concepts

This project combines several useful embedded-systems concepts:

* 🎤 Analog sensor input
* 📈 Peak-to-peak signal measurement
* 🔐 Pattern-based access control
* 🔢 Event counting
* ⏱️ `millis()` timing
* 🛡️ Debouncing / noise filtering
* ⚙️ Servo motor control
* 🔋 Power stabilization
* 📟 Serial debugging
* 🔄 Boolean state management
* 📊 Threshold-based decision making

---

## 🎯 Project Goal

The main purpose of this project is to demonstrate that a digital lock does not necessarily need a keypad or RFID reader.

A simple vibration/sound sensor can be used as an **input device**, while software determines whether the detected sequence matches a predefined pattern.

The complete system can be summarized as:

```text
👊 Knock
   ↓
🎤 Sound/Vibration Sensor
   ↓
📈 Peak-to-Peak Analysis
   ↓
🔢 Knock Counter
   ↓
⏱️ 1.5 Second Window
   ↓
🔐 Pattern Verification
   ↓
 ┌───────────────┐
 │ Exactly 3 ?   │
 └───────┬───────┘
         │
    ┌────┴────┐
    ▼         ▼
   YES        NO
    │         │
    ▼         ▼
   🔓        ❌
  Servo      Denied
   90°
```

> **🔑 Security Pattern: Exactly 3 knocks within 1.5 seconds.**
>
> **1, 2, 4, or more knocks are rejected.**
