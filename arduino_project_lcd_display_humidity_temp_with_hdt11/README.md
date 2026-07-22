# Arduino Project 18: DHT11 Temperature & Humidity Monitor 🌡️💧

This project demonstrates how to use a **DHT11 temperature and humidity sensor 🌡️💧** with an **Arduino 🧠** and a **16×2 LCD 📟**.

The DHT11 measures:

* 🌡️ Temperature
* 💧 Relative humidity

The Arduino reads the sensor values and displays them on the LCD.

```text id="q7m3x8"
🌡️ DHT11 Sensor
       ↓
   📥 Sensor Data
       ↓
    🧠 Arduino
       ↓
   📟 16×2 LCD
       ↓
🌡️ Temperature + 💧 Humidity
```

The display updates every **2 seconds**:

```text id="m5r8k2"
Humidity: 45%
Temp: 25 C
```

## How the Project Works

The DHT11 sensor is connected to digital pin **2**.

The LCD uses:

```text id="v3p9q6"
RS → 7
E  → 8
D4 → 9
D5 → 10
D6 → 11
D7 → 12
```

The complete project flow is:

```text id="x8k2m4"
🌡️ DHT11
    │
    ▼
📥 Read Temperature
📥 Read Humidity
    │
    ▼
🧠 Arduino
    │
    ▼
📟 LCD
    │
    ├── 🌡️ Temperature
    └── 💧 Humidity
```

## What Is the DHT11 Sensor? 🌡️💧

The **DHT11** is a digital sensor that measures both:

```text id="n6p4r9"
🌡️ Temperature
        +
💧 Humidity
```

It sends the measured data to the Arduino through a single data pin.

```text id="a3m8q1"
🌡️ DHT11
    │
    │ Digital Data
    ▼
🧠 Arduino
```

Unlike a potentiometer or photoresistor, the DHT11 does not simply output a raw analog value between `0` and `1023`.

Instead, the sensor and library process the measurement and provide meaningful values such as:

```text id="k5x7p2"
Temperature → 25°C
Humidity    → 45%
```

## What Is Temperature? 🌡️

Temperature describes how hot or cold the environment is.

This project reads temperature in Celsius:

```cpp id="r4m9q6"
tempC = ht.readTemperature();
```

Example:

```text id="v7n2k8"
tempC = 25
```

The LCD displays:

```text id="q2v7m4"
Temp: 25 C
```

The DHT library can also read temperature in Fahrenheit:

```cpp id="a8m5r2"
ht.readTemperature(true);
```

However, this project uses Celsius.

## What Is Humidity? 💧

**Relative humidity** describes how much water vapor is present in the air compared to the maximum amount the air can hold at that temperature.

It is represented as a percentage:

```text id="w5p9k3"
0%   → Very Dry
50%  → Moderate Humidity
100% → Fully Saturated Air
```

The project reads humidity using:

```cpp id="m7x2q8"
humidity = ht.readHumidity();
```

Example:

```text id="c4n8v1"
humidity = 45
```

The LCD displays:

```text id="r3m6p9"
Humidity: 45%
```

## DHT11 Library 📚

The project uses:

```cpp id="x8q2k5"
#include <DHT.h>
```

The DHT library makes it easier to communicate with the sensor.

The sensor type is defined using:

```cpp id="v6m3p8"
#define Type DHT11
```

This tells the library:

```text id="k9p4x2"
🧠 Arduino
      ↓
📚 DHT Library
      ↓
🌡️ DHT11 Sensor
```

## Creating the DHT Object

The sensor is initialized with:

```cpp id="r7x2m6"
DHT ht(sensePin, Type);
```

This tells the program:

```text id="p3k8q5"
Data Pin → 2
Sensor   → DHT11
```

```text id="a9m4v1"
DHT ht(2, DHT11);
```

The name of the sensor object is:

```text id="x6p2q8"
ht
```

## Starting the Sensor

In `setup()`:

```cpp id="m8r3k5"
ht.begin();
```

This initializes communication between the Arduino and the DHT11.

```text id="q4v7n2"
🧠 Arduino
      ↓
  ht.begin()
      ↓
🌡️ DHT11 Ready
```

## Reading Humidity

The program uses:

```cpp id="p9m2x6"
humidity = ht.readHumidity();
```

The sensor returns the relative humidity percentage.

```text id="c7k4r8"
DHT11
  ↓
💧 Humidity Data
  ↓
humidity
```

Example:

```text id="j5q2x9"
humidity = 60.0
```

The LCD displays:

```text id="a6m9p4"
Humidity: 60%
```

## Reading Temperature

The program reads Celsius temperature using:

```cpp id="v3n8m1"
tempC = ht.readTemperature();
```

The value is stored in:

```text id="s5p8k2"
tempC
```

Example:

```text id="q6m4r8"
tempC = 27.0
```

The LCD displays:

```text id="n8x3p5"
Temp: 27 C
```

## Why Are `float` Variables Used?

The sensor values are declared as:

```cpp id="m4q7k2"
float humidity;
float tempC;
float tempF;
```

A `float` can store decimal values:

```text id="r9m2v6"
25.5
48.7
72.3
```

This is useful because temperature and humidity measurements may contain decimal values.

However, this project displays:

```cpp id="x5k8p3"
int(humidity)
int(tempC)
```

This converts the values into whole numbers.

For example:

```text id="a7m4q9"
25.8 → 25
48.6 → 48
```

Therefore, the LCD displays simpler integer values.

## Displaying the Data on the LCD 📟

The LCD is cleared before showing new readings:

```cpp id="j2p6x8"
lcd.clear();
```

Then the cursor is placed on the first row:

```cpp id="v4n8m2"
lcd.setCursor(0, 0);
```

The humidity is displayed:

```cpp id="q3m7x5"
lcd.print("Humidity: ");
lcd.print(int(humidity));
lcd.print("%");
```

The second row is selected:

```cpp id="k8p2r6"
lcd.setCursor(0, 1);
```

The temperature is displayed:

```cpp id="s9m4v1"
lcd.print("Temp: ");
lcd.print(int(tempC));
lcd.print(" C");
```

The final LCD output looks like:

```text id="n5x8q2"
┌────────────────┐
│ Humidity: 45%  │
│ Temp: 25 C     │
└────────────────┘
```

## Updating the Display

The project uses:

```cpp id="c4m7p9"
int dt = 2000;
```

and:

```cpp id="r2k6v8"
delay(dt);
```

This means the Arduino waits:

```text id="j7m3x5"
2000 milliseconds
       ↓
    2 seconds
```

The sensor data is therefore refreshed approximately every two seconds.

```text id="p8q4m1"
📥 Read Sensor
      ↓
📟 Display Data
      ↓
⏳ Wait 2 Seconds
      ↓
🔄 Read Again
```

## Complete Project Flow

```text id="v6n2k9"
       🌡️ DHT11
           ↓
   📥 Read Humidity
           ↓
   📥 Read Temperature
           ↓
        🧠 Arduino
           ↓
      🧹 Clear LCD
           ↓
    ┌──────────────┐
    │ Humidity: 45%│
    │ Temp: 25 C   │
    └──────────────┘
           ↓
      ⏳ Wait 2 sec
           ↓
          🔄 Repeat
```

## Example Output

Example sensor readings:

```text id="a5m8q3"
Humidity: 52%
Temp: 24 C
```

After the environment changes:

```text id="k2r7m4"
Humidity: 55%
Temp: 25 C
```

The values may change depending on:

* 🌡️ Room temperature
* 💧 Moisture in the air
* 📍 Sensor location
* 🌬️ Air movement
* ⏱️ Time of measurement

## Important Note About DHT11 Readings ⚠️

The DHT11 is designed for basic environmental measurements and is not a high-precision scientific instrument.

The readings can vary depending on:

```text id="x8m3p6"
🌡️ Environment
📍 Sensor Position
🌬️ Airflow
💧 Humidity Conditions
⏱️ Measurement Time
```

Different sensors and different environments may produce slightly different values.

## Components

* 🧠 Arduino board
* 🌡️ DHT11 temperature and humidity sensor
* 📟 16×2 LCD
* 🧱 Breadboard
* 🔌 Jumper wires
* 🔋 Power supply

## Key Components & Functions

### 🌡️ DHT11

Measures temperature and relative humidity.

### 💧 Humidity

Measures the amount of water vapor in the air as a percentage.

### 🌡️ Temperature

Measures how hot or cold the environment is.

### 📟 16×2 LCD

Displays the sensor readings.

### `ht.begin()`

Initializes the DHT11 sensor.

### `readHumidity()`

Reads the relative humidity percentage.

### `readTemperature()`

Reads the temperature in Celsius by default.

### `lcd.clear()`

Clears the previous LCD content.

### `lcd.setCursor()`

Sets the position of the next text.

### `lcd.print()`

Displays text and values on the LCD.

## Concepts Demonstrated

* 🌡️ Temperature sensing
* 💧 Humidity sensing
* 📡 Digital sensor communication
* 📟 LCD display
* 📚 External Arduino libraries
* `DHT.h`
* `LiquidCrystal.h`
* `readHumidity()`
* `readTemperature()`
* `ht.begin()`
* `float` variables
* Data conversion using `int()`
* Periodic sensor readings

> 🌡️ Measure the environment. 💧 Read the data. 📟 Display the results. 🧠 Monitor the world around you.
