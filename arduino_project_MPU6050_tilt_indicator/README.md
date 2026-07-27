# MPU-6050 Tilt Level Indicator

This project uses the **MPU-6050 accelerometer and gyroscope sensor** to detect the tilt of a device and display its current orientation using three LEDs.

The MPU-6050 measures motion and orientation through:

* 📐 **Accelerometer** — measures linear acceleration, including the effect of gravity.
* 🔄 **Gyroscope** — measures rotational velocity around the X, Y, and Z axes.

In this project, the accelerometer values are used to estimate the tilt of the sensor. The program reads the acceleration on the **X** and **Y** axes and classifies the device into three states:

| State           | Condition                       | LED       |
| --------------- | ------------------------------- | --------- |
| Balanced        | `tiltX < 0.5` and `tiltY < 0.5` | 🟢 Green  |
| Slightly Tilted | `tiltX < 2.5` and `tiltY < 2.5` | 🟡 Yellow |
| Highly Tilted   | Otherwise                       | 🔴 Red    |

The values are measured in **m/s²**.

---

## How It Works

The sensor continuously sends acceleration data to the Arduino:

```cpp
mpu.getEvent(&a, &g, &temp);
```

The accelerometer data is stored in:

```cpp
a.acceleration.x
a.acceleration.y
a.acceleration.z
```

This project uses:

```cpp
float tiltX = abs(a.acceleration.x);
float tiltY = abs(a.acceleration.y);
```

The `abs()` function converts negative values into positive values. This allows the program to focus on the **amount of tilt** rather than the direction of the tilt.

For example:

```text
X = -2.0 m/s² → 2.0
X =  2.0 m/s² → 2.0
```

Both values represent the same amount of acceleration for this project's classification logic.

---

## Tilt Detection Logic

### 🟢 Balanced

```cpp
if(tiltX < 0.5 && tiltY < 0.5)
```

When the acceleration values on both axes are very small, the device is considered:

```text
Balanced!
```

The green LED turns on.

---

### 🟡 Slightly Tilted

```cpp
else if(tiltX < 2.5 && tiltY < 2.5)
```

If the acceleration values are higher than the balanced threshold but still relatively low, the device is considered:

```text
Slightly Tilted!
```

The yellow LED turns on.

---

### 🔴 Highly Tilted

If neither of the previous conditions is true:

```cpp
else
```

the device is classified as:

```text
Highly Tilted!
```

The red LED turns on.

---

## Hardware

### MPU-6050

| MPU-6050 Pin | Arduino Connection         | Purpose   |
| ------------ | -------------------------- | --------- |
| `VCC`        | `5V` or appropriate supply | Power     |
| `GND`        | `GND`                      | Ground    |
| `SCL`        | `A5` on Arduino Uno        | I²C clock |
| `SDA`        | `A4` on Arduino Uno        | I²C data  |

### LEDs

| LED       | Arduino Pin |
| --------- | ----------- |
| 🔴 Red    | `8`         |
| 🟡 Yellow | `9`         |
| 🟢 Green  | `10`        |

> ⚠️ Each LED should normally be connected with an appropriate current-limiting resistor.

---

## Why the MPU-6050 Is Useful

The MPU-6050 is a popular **6-axis motion sensor**. It combines:

### 📐 3-Axis Accelerometer

Measures acceleration along:

```text
X-axis
Y-axis
Z-axis
```

The accelerometer can detect:

* Tilting
* Movement
* Acceleration
* Device orientation
* Gravity direction

### 🔄 3-Axis Gyroscope

Measures rotation around:

```text
X-axis → Roll
Y-axis → Pitch
Z-axis → Yaw
```

This allows the MPU-6050 to be used in:

* 🤖 Robots
* 🚁 Drones
* 🎮 Motion controllers
* 🕹️ Game controllers
* 📱 Orientation systems
* 🛞 Self-balancing robots

---

## Important Note About This Project

This project uses the **accelerometer values** to estimate the tilt level.

The values used here:

```cpp
0.5
2.5
```

are threshold values selected for this particular setup. They are not universal values that will work perfectly in every situation.

The results may change depending on:

* The physical orientation of the MPU-6050
* The surface where the sensor is placed
* Sensor noise
* Wiring
* Power supply
* Sensor calibration
* The selected accelerometer range

Therefore, when building your own project, you may need to adjust the thresholds:

```cpp
if(tiltX < 0.5 && tiltY < 0.5)
```

and:

```cpp
else if(tiltX < 2.5 && tiltY < 2.5)
```

to match your specific hardware and desired behavior.

---

## Project Concept

This project demonstrates a simple but practical example of converting **sensor data into a physical response**:

```text
MPU-6050
    ↓
Acceleration Data
    ↓
Tilt Classification
    ↓
Arduino Decision
    ↓
LED Indicator
```

The MPU-6050 provides the data, the Arduino processes it, and the LEDs communicate the result visually.

This is a basic example of how motion sensors can be used as the foundation for more advanced systems such as electronic leveling tools, robot orientation systems, and balance detection devices.
