# 📡 Arduino Radar Scanner

A real-time **Arduino Radar Scanner** built using an **HC-SR04 ultrasonic distance sensor**, a **servo motor**, and **Processing IDE**.

The servo rotates the HC-SR04 sensor from **15° to 165°**, allowing the sensor to scan the surrounding area. At every angle, the HC-SR04 measures the distance to an object and sends the angle and distance data to the computer through the Arduino's Serial Monitor connection.

**Processing IDE** receives this serial data and converts it into a graphical radar interface that displays:

* 📐 Current scanning angle
* 📏 Distance to the detected object
* 🟢 Green radar scanning line
* 🔴 Red detected-object indicator
* 📡 Radar arcs representing different distances
* 🔢 Angle markings from 30° to 150°
* ⚠️ Object detection within a 40 cm range

---

## 📸 Project Overview

The physical structure of the project consists of an **HC-SR04 ultrasonic sensor mounted on top of a servo motor**.

As the servo rotates, the HC-SR04 rotates with it. This allows the sensor to measure objects at different directions rather than measuring only one fixed direction.

The servo motor is powered separately using a **4×AA battery pack (approximately 6 V)** because the servo can require more current than it is practical to draw directly from the Arduino board.

The Arduino controls the servo and reads the HC-SR04, while the computer runs the Processing visualization.

---

# 🎯 Project Goal

The main goal of this project is to create a simple radar-like scanning system.

The system continuously performs the following process:

```text
Servo rotates
      ↓
HC-SR04 points in a new direction
      ↓
Ultrasonic pulse is transmitted
      ↓
Echo returns from an object
      ↓
Arduino calculates distance
      ↓
Arduino sends angle + distance
      ↓
Processing receives the data
      ↓
Radar visualization is updated
```

For example, Arduino can send:

```text
45,23.
```

This means:

```text
Angle    = 45°
Distance = 23 cm
```

Processing reads this information and displays the object at approximately **45° and 23 cm** on the radar.

---

# 🧰 Components Used

| Component                 | Quantity | Purpose                       |
| ------------------------- | -------: | ----------------------------- |
| Arduino Uno               |        1 | Main controller               |
| HC-SR04 Ultrasonic Sensor |        1 | Measures distance             |
| Servo Motor               |        1 | Rotates the sensor            |
| 4×AA Battery Pack         |        1 | External servo power          |
| AA Batteries              |        4 | Provides approximately 6 V    |
| Jumper Wires              |  Several | Connections                   |
| USB Cable                 |        1 | Arduino-to-PC communication   |
| Computer                  |        1 | Runs Processing visualization |

---

# 🔌 Pin Connections

## HC-SR04

The HC-SR04 uses two signal pins:

| HC-SR04 Pin | Arduino Pin |
| ----------- | ----------- |
| VCC         | 5V          |
| GND         | GND         |
| TRIG        | D10         |
| ECHO        | D11         |

The code defines these pins as:

```cpp
#define trigPin 10
#define echoPin 11
```

### TRIG

The Arduino sends a short HIGH pulse to the TRIG pin.

```cpp
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
```

This tells the HC-SR04 to send an ultrasonic pulse.

### ECHO

The ECHO pin becomes HIGH while the ultrasonic pulse travels to an object and returns.

The Arduino measures this time using:

```cpp
duration = pulseIn(echoPin, HIGH, 30000);
```

---

# 🔄 Servo Motor Connection

The servo signal wire is connected to:

```text
Arduino D12
```

The code uses:

```cpp
#define servoPin 12
```

and:

```cpp
myservo.attach(servoPin);
```

### Servo Power

The servo is powered by a separate **4×AA battery pack**, providing approximately **6 V**.

This is important because a servo motor can draw significant current, especially while moving or when it is under mechanical load.

The Arduino is therefore responsible for the **control signal**, while the external battery provides the servo's motor power.

### ⚠️ Common Ground

The external battery ground and Arduino ground should be connected together.

```text
Battery (+)  → Servo VCC
Battery (-)  → Servo GND
Arduino GND  → Servo GND
Arduino D12  → Servo Signal
```

The common ground is necessary so that the Arduino's servo control signal has the same electrical reference as the servo's power supply.

> **Important:** Do not connect the 6 V battery directly to an Arduino I/O pin.

---

# 📡 HC-SR04 Mounted on the Servo

The **HC-SR04 is physically placed on top of the servo motor**.

This is one of the most important mechanical parts of the project.

The servo rotates the sensor:

```text
             HC-SR04
          ┌────────────┐
          │  ○      ○  │
          └────────────┘
                │
                │
          ┌───────────┐
          │   SERVO   │
          └───────────┘
                │
             Base
```

Because the HC-SR04 is attached to the servo, changing the servo angle also changes the direction in which the ultrasonic sensor is facing.

For example:

```text
15°  → scan left side
90°  → scan center
165° → scan right side
```

The physical mounting therefore converts the HC-SR04 from a fixed distance sensor into a simple scanning system.

---

# 🧠 How the HC-SR04 Measures Distance

The HC-SR04 works using ultrasonic sound waves.

The basic process is:

1. Arduino activates the TRIG pin.
2. HC-SR04 sends an ultrasonic pulse.
3. The sound wave travels through the air.
4. The wave hits an object.
5. The wave reflects back toward the sensor.
6. HC-SR04 activates ECHO for the measured travel time.
7. Arduino measures that time.
8. Arduino converts the time into centimeters.

The code uses:

```cpp
distance = duration * 0.034 / 2;
```

### Why divide by 2?

The measured time represents the complete trip:

```text
Sensor → Object → Sensor
```

Therefore, the distance to the object is half of the total traveled distance.

The approximate speed of sound used here is:

```text
0.034 cm/µs
```

So:

```text
Distance = Time × Speed of Sound ÷ 2
```

---

# ⏱️ The `pulseIn()` Timeout

The project uses:

```cpp
duration = pulseIn(echoPin, HIGH, 30000);
```

The `30000` represents a timeout of **30,000 microseconds**, or approximately **30 ms**.

Without a timeout, `pulseIn()` can wait for an echo for a long time if no echo is received.

The timeout prevents the program from waiting indefinitely.

---

# 🔄 Servo Scanning

The servo scans between:

```text
15° → 165°
```

instead of using the complete 0°–180° range.

The forward scan is:

```cpp
for (i = 15; i <= 165; i++)
{
    myservo.write(i);
    delay(30);
    calculateDistance();

    Serial.print(i);
    Serial.print(",");
    Serial.print(distance);
    Serial.print(".");
}
```

At every angle:

1. Servo moves to the angle.
2. Program waits 30 ms.
3. HC-SR04 measures distance.
4. Arduino sends the result to the computer.

For example:

```text
15,35.
16,34.
17,33.
18,32.
...
90,20.
...
165,40.
```

---

# ↩️ Returning Scan

After reaching 165°, the servo scans backward:

```cpp
for (i = 165; i >= 15; i--)
{
    myservo.write(i);
    delay(30);
    calculateDistance();

    Serial.print(i);
    Serial.print(",");
    Serial.print(distance);
    Serial.print(".");
}
```

Therefore, the complete movement is:

```text
15° → 16° → 17° → ... → 165°
                              ↓
165° ← 164° ← 163° ← ... ← 15°
```

Then the process repeats continuously.

This creates the characteristic sweeping motion of the radar.

---

# ⏳ Why Is There a 30 ms Delay?

The code contains:

```cpp
delay(30);
```

after every servo movement.

The delay gives the servo enough time to physically move toward the requested position before the distance measurement is taken.

Without sufficient delay:

```text
Servo moves
↓
Sensor measures immediately
↓
Servo may still be moving
↓
Measurement may not correspond accurately to the displayed angle
```

With the delay:

```text
Servo moves
↓
Wait 30 ms
↓
Servo settles
↓
HC-SR04 measures
↓
Arduino sends angle + distance
```

---

# 💻 Arduino IDE

The Arduino portion of the project is developed using **Arduino IDE**.

Arduino IDE is used to:

* Write the Arduino C++ program
* Compile the code
* Upload the program to the Arduino
* Control the servo
* Read the HC-SR04
* Send sensor data through Serial communication

The required library is:

```cpp
#include <Servo.h>
```

The `Servo` library provides functions such as:

```cpp
myservo.attach(servoPin);
myservo.write(angle);
```

---

# 🖥️ Why Processing IDE Is Used

Arduino itself can measure the distance and control the servo, but it is not designed to create a large, animated graphical radar interface.

The Arduino can easily send data such as:

```text
90,25.
```

but displaying this as a radar requires graphical drawing.

This is where **Processing IDE** is used.

Processing is a programming environment designed for **visual and interactive applications**.

In this project, Processing:

1. Opens the Arduino's serial port.
2. Receives angle and distance values.
3. Separates the values.
4. Converts them into numbers.
5. Draws the radar.
6. Draws the scanning line.
7. Displays detected objects.
8. Displays the current angle and distance.

Therefore:

```text
Arduino
Hardware + Sensors + Measurements
             ↓
        Serial Data
             ↓
Processing IDE
Graphical Radar Visualization
```

Arduino and Processing have different jobs.

---

# 🔗 Serial Communication

The Arduino starts serial communication with:

```cpp
Serial.begin(9600);
```

Processing opens the same communication speed:

```java
myPort = new Serial(this, "COM6", 9600);
```

Both sides must use the same baud rate:

```text
Arduino:    9600
Processing: 9600
```

If they use different speeds, Processing may receive corrupted or unreadable data.

---

# 📤 Arduino Data Format

Arduino sends:

```cpp
Serial.print(i);
Serial.print(",");
Serial.print(distance);
Serial.print(".");
```

The resulting format is:

```text
ANGLE,DISTANCE.
```

For example:

```text
45,23.
```

The comma separates the angle and distance:

```text
45 , 23
↑     ↑
angle distance
```

The period marks the end of one complete measurement.

Processing uses:

```java
myPort.bufferUntil('.');
```

This tells Processing to wait until `.` is received before processing a complete measurement.

---

# 📥 Processing Data Parsing

Processing receives the complete string:

```text
45,23.
```

The period is removed:

```java
data = data.substring(0, data.length()-1);
```

Now:

```text
45,23
```

Processing finds the comma:

```java
index1 = data.indexOf(",");
```

Then it separates the data:

```java
angle = data.substring(0, index1);
distance = data.substring(index1+1, data.length());
```

The result becomes:

```text
angle    = "45"
distance = "23"
```

Finally, the strings are converted into integers:

```java
iAngle = int(angle);
iDistance = int(distance);
```

Now Processing can use them for mathematical calculations and drawing.

---

# 📡 Processing Serial Port

The Processing program contains:

```java
myPort = new Serial(this, "COM6", 9600);
```

`COM6` is the serial port assigned to the Arduino on the computer used for this project.

**The COM port may be different on another computer.**

For example, it could be:

```text
COM3
COM4
COM5
COM6
COM7
```

If Processing cannot connect to the Arduino, check which COM port the Arduino is using in Arduino IDE.

---

# 🟢 Radar Scanning Line

Processing draws the active scanning line using:

```java

The project considers objects within:

```text
40 cm
```

to be inside the displayed detection range.

Processing uses:

```java
if (iDistance<40)
```

If the object is closer than 40 cm, a red line is drawn from the radar origin toward the detected object.

The red section represents:

```text
Detected object
```

The code calculates the object's position using trigonometry:

```java
cos(radians(iAngle))
sin(radians(iAngle))
```

This converts the polar coordinates:

```text
Angle + Distance
```

into screen coordinates:

```text
X + Y
```

---

# 📐 Polar Coordinates
---

rect(0, 0, width, height-height*0.065);
```
This creates a fading effect.
Instead of completely clearing the previous frame, the old image gradually becomes darker.

The result is a radar-style motion trail.


With the effect, the radar looks smoother:

```text
Current scan
     ↓
████████████
  fading trail
Without this effect, the scanning line would appear to instantly disappear after every frame.


```
The Processing program uses a transparent black rectangle:
```java

fill(0, 4);


---

# 🌫️ Motion Blur Effect
```

# 🧩 Main Arduino Functions

## `setup()`

Distance: XX cm


```text
Angle: XX

The bottom section displays:
```cpp
The red line represents an object detected within 40 cm.

### Information panel
The radar naturally works with polar coordinates:
void setup()
### Scanning line
### Detected object


```

Runs once when the Arduino starts.

It:
The green scanning line represents the current position of the servo.


120°
150°

* Configures the HC-SR04 pins
* Attaches the servo
```
---

```text

* Starts Serial communication
Angle = θ
## `loop()`

30°

60°
```cpp
void loop()
```
90°

```text
Distance = r
```

The computer screen, however, uses Cartesian coordinates:

Runs continuously.

The radar displays:

```text
X
40 cm

### Angle lines
```

It:

Y
```

Processing converts between them using:
10 cm
* Scans forward
* Measures distance
* Sends data
* Scans backward
20 cm
30 cm

The arcs represent:

```text
* Measures distance
* Sends data
* Repeats
```text
X = r × cos(θ)
Y = r × sin(θ)
### Radar arcs

```

The green radar style gives the project the appearance of a traditional radar screen.


---

This is why the radar can correctly place an object according to both its distance and direction.

## `calculateDistance()`
---

# 📏 Radar Range

The visualization is configured for a maximum range of:

Otherwise:
```text

```cpp
int calculateDistance()
```

40 cm
```
### Green radar background


```java
iDistance > 40
This function:

1. Triggers the HC-SR04.
2. Measures the echo duration.
# 🎨 Radar Interface

The Processing interface contains several graphical elements.


---
3. Calculates distance.
4. Returns the distance.


```


This keeps the distance-measurement code organized instead of repeating it throughout `loop()`.

is displayed.
In Range
```

---

```text

when:

The radar contains four main distance rings:

# 🧩 Main Processing Functions

## `setup()`

```

```text
Creates the Processing window and establishes serial communication.

```java
Out of Range
```text
10 cm
Processing also displays:
20 cm

size(1200, 700);
```

30 cm
40 cm
```

These are represented visually as concentric arcs.
creates a 1200×700 pixel window.

---


## `draw()`

Objects beyond 40 cm are not shown as detected objects.
drawLine();
```

The line starts from the center-bottom of the radar and extends in the direction of the current servo angle.

Conceptually:
Runs repeatedly and updates the radar animation.


# 🔴 Object Detection

It calls:

```java
```text
drawRadar();
drawLine();
drawObject();
                90°
                 ↑
                 │

---
drawText();
```


---

## `serialEvent()`


Receives and processes incoming Arduino data.


It converts:


```text
ANGLE,DISTANCE.
```


into:

```text
iAngle

iDistance
```


---

## `drawRadar()`

Creates:


* Distance arcs
* Angle lines
* Radar geometry

---


## `drawLine()`

Draws the current green scanning line.

---

## `drawObject()`

Draws a red indication when an object is detected within 40 cm.

---

## `drawText()`


Displays:

* Current angle
* Current distance
* Range status
* Distance labels
* Angle labels

---

# 🔧 Complete System Architecture

The complete project can be understood as three layers.

## 1. Physical Layer

```text
             HC-SR04
                 │
                 │ mounted on
                 ▼
              SERVO
                 │
                 │
          Mechanical rotation
```

The servo physically changes the direction of the ultrasonic sensor.

---

## 2. Arduino Control Layer

```text
HC-SR04
   ↓
Arduino
   ↓
Distance calculation
   ↓
Angle + Distance
   ↓
Serial communication
```

Arduino is responsible for controlling and measuring the hardware.

---

## 3. Computer Visualization Layer

```text
Serial data
     ↓
Processing IDE
     ↓
Parse angle + distance
     ↓
Mathematical conversion
     ↓
Radar graphics
```

Processing turns the numerical sensor data into a visual radar.

---

# 🚀 How to Run the Project

## Step 1 — Build the Hardware

Mount the HC-SR04 securely on top of the servo motor.

Make sure the sensor rotates together with the servo.

---

## Step 2 — Connect the HC-SR04

```text
TRIG → Arduino D10
ECHO → Arduino D11
VCC  → Arduino 5V
GND  → Arduino GND
```

---

## Step 3 — Connect the Servo

```text
Signal → Arduino D12
VCC    → 4×AA battery pack (+)
GND    → Battery (-)
GND    → Arduino GND
```

Make sure the Arduino and external servo supply share a common ground.

---

## Step 4 — Upload the Arduino Code

Open the project in **Arduino IDE**.

Select the correct:

```text
Board
Port
```

Then upload the code.

---

## Step 5 — Check Serial Communication

Open Arduino Serial Monitor and set:

```text
9600 baud
```

You should see data similar to:

```text
15,35.
16,34.
17,34.
18,33.
...
90,20.
...
165,42.
```

This confirms that Arduino is successfully measuring and transmitting data.

---

## Step 6 — Close Serial Monitor

Before running Processing, close Arduino Serial Monitor.

The same serial port generally cannot be controlled by both Serial Monitor and Processing simultaneously.

---

## Step 7 — Open Processing IDE

Open the Processing project.

Check this line:

```java
myPort = new Serial(this, "COM6", 9600);
```

Change `COM6` if your Arduino uses a different COM port.

---

## Step 8 — Run Processing

Press the **Run** button.

A radar window should appear.

The servo should continuously rotate the HC-SR04 while the Processing window displays the scanning movement.

---

# ⚠️ Important Troubleshooting

## Servo Does Not Move

Check:

* Servo signal is connected to D12.
* External 4×AA battery pack is connected correctly.
* Servo ground is connected to Arduino GND.
* Battery pack has sufficient charge.
* Servo is not mechanically blocked.

---

## Arduino Resets When Servo Moves

This can happen when the servo draws a large current from the Arduino's power supply.

Using the external **4×AA battery pack** helps prevent the servo from consuming the Arduino's available power.

Also make sure the grounds are connected together.

---

## HC-SR04 Gives Incorrect Distance

Check:

```text
TRIG → D10
ECHO → D11
```

Also make sure:

* VCC is connected to 5 V.
* GND is connected to GND.
* The sensor is securely mounted.
* The object is within the sensor's practical detection range.

---

## Processing Shows Nothing

Check the COM port:

```java
"COM6"
```

It must match the Arduino's actual serial port.

Also check:

```java
9600
```

Arduino and Processing must use the same baud rate.

---

## Processing Gives a Serial Port Error

Close:

* Arduino Serial Monitor
* Arduino Serial Plotter
* Other programs using the Arduino COM port

Then run Processing again.

---

## Radar Is Not Detecting Objects

The current Processing visualization only displays detected objects when:

```text
distance < 40 cm
```

Therefore, an object farther than approximately 40 cm will be considered:

```text
Out of Range
```

---

# 📌 Important Design Decisions

### Why use a servo?

A stationary HC-SR04 can only measure objects in one direction.

The servo allows the sensor to scan multiple directions.

```text
Fixed sensor:

       Object
         ↑
         │
       HC-SR04


Servo-mounted sensor:

Object ←   HC-SR04   → Object
             ↕
          rotation
```

---

### Why use an external battery for the servo?

The servo is a motor and can require considerably more current than an Arduino I/O pin can provide.

The external 4×AA battery pack supplies the servo's motor power while Arduino provides the control signal.

This makes the system more reliable and reduces the chance of Arduino resets caused by servo power demand.

---

### Why use Processing?

Arduino is excellent for:

* Sensor reading
* Motor control
* Data processing
* Serial communication

Processing is better suited for:

* Graphics
* Animation
* Real-time visualization
* Drawing shapes
* Interactive interfaces

Using both platforms gives the project a clean architecture:

```text
Arduino = Hardware + Data
Processing = Visualization
```

---


# 📊 Data Flow Example

Suppose the servo is currently at:

```text
90°
```

and the HC-SR04 detects an object at:

```text
25 cm
```

Arduino sends:

```text
90,25.
```

Processing receives the data and stores:

```text
iAngle = 90
iDistance = 25

```

The radar then calculates the screen position of the object and displays it along the 90° direction at the corresponding distance.

The result visually represents:

```text
             🔴 Object
                ↑
                │ 25 cm
                │
                │
                │
                ●
             Radar
              90°

```

---

# 🧪 Testing

The project can be tested by placing an object at different positions.


For example:


| Test | Object Position | Expected Result                    |
| ---- | --------------- | ---------------------------------- |
| 1    | ~90°, 10 cm     | Object appears near center         |

| 2    | ~90°, 20 cm     | Object appears farther from center |
| 3    | ~45°, 15 cm     | Object appears around 45°          |
| 4    | ~135°, 25 cm    | Object appears around 135°         |
| 5    | >40 cm          | Processing shows out of range      |


The exact measured angle and distance can vary slightly because of servo positioning, ultrasonic reflections, sensor accuracy, and object shape.

---

# 📁 Project Structure

A recommended project structure is:

```text
Arduino-Radar-Scanner/
│
├── Arduino/
│   └── radar_scanner.ino
│
├── Processing/
│   └── radar_visualization.pde
│
└── README.md
```

### `radar_scanner.ino`

Contains the Arduino code responsible for:

* Servo control
* HC-SR04 measurements
* Distance calculation
* Serial communication

### `radar_visualization.pde`

Contains the Processing code responsible for:

* Serial communication
* Data parsing
* Radar drawing
* Object visualization
* Text information

### `README.md`

Contains the complete project documentation.

---

# 🛠️ Technologies Used

* **Arduino**
* **Arduino IDE**
* **C++**
* **Servo Library**
* **HC-SR04 Ultrasonic Sensor**
* **Servo Motor**
* **Processing IDE**
* **Processing Serial Library**
* **Serial Communication**
* **Trigonometry**
* **Real-time graphical visualization**

---

# 📚 Concepts Demonstrated

This project demonstrates several important electronics and programming concepts:

* Digital input/output
* Ultrasonic distance measurement
* Servo motor control
* External motor power
* Common electrical ground
* Serial communication
* Data parsing
* Real-time visualization
* Coordinate systems
* Polar coordinates
* Cartesian coordinates
* Sine and cosine
* Animation
* Hardware/software integration

---

# 🏁 Final Result

The final system combines mechanical movement, ultrasonic sensing, Arduino programming, serial communication, and graphical visualization.

The **servo motor rotates the HC-SR04**, the **HC-SR04 measures the distance**, the **Arduino calculates and transmits the measurements**, and **Processing converts those measurements into a real-time radar display**.

```text
        ┌─────────────────────┐
        │      HC-SR04        │
        │ Ultrasonic Sensor   │
        └──────────┬──────────┘
                   │
             mounted on
                   │
        ┌──────────▼──────────┐
        │     Servo Motor     │
        └──────────┬──────────┘
                   │
              Control
                   │
        ┌──────────▼──────────┐
        │       Arduino       │
        │                     │
        │ Distance + Angle    │
        └──────────┬──────────┘
                   │
             Serial USB
                   │
        ┌──────────▼──────────┐
        │   Processing IDE    │
        │                     │
        │  Radar Visualization│
        └─────────────────────┘
```

The result is a functional **Arduino-based radar scanning system** capable of detecting objects within approximately **40 cm** and displaying their direction and distance in real time.

---

# 👨‍💻 Project Summary

**Project:** Arduino Radar Scanner
**Controller:** Arduino
**Distance Sensor:** HC-SR04
**Actuator:** Servo Motor
**Servo Power:** 4×AA battery pack (~6 V)
**Sensor Position:** Mounted on top of the servo
**Arduino IDE:** Hardware programming and uploading
**Processing IDE:** Radar visualization
**Communication:** Serial at 9600 baud
**Scanning Range:** 15°–165°
**Visualization Range:** 0–40 cm
**Main Visualization:** Real-time radar interface

