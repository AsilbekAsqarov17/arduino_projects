# 🐍 Arduino Snake Game — 8×8 LED Matrix & Joystick

## 📌 Project Overview

This project recreates the classic **Snake game** using an Arduino, an **8×8 MAX7219 LED matrix**, and a **joystick module**.

The LED matrix acts as the entire game screen:

* 🟩 **Snake** — represented by illuminated LEDs
* 🍎 **Food** — appears as a blinking LED
* 🎮 **Joystick** — controls the snake's direction
* 💀 **Game Over** — the matrix flashes three times before restarting

The project is a practical combination of **hardware control, arrays, structures, enums, random number generation, collision detection, timing with `millis()`, and LED-matrix control**.

---

## 🔌 Components

| Component              | Purpose                 |
| ---------------------- | ----------------------- |
| Arduino                | Main controller         |
| 8×8 MAX7219 LED Matrix | Game display            |
| Joystick Module        | Snake direction control |
| Jumper Wires           | Connections             |
| USB Power              | Arduino power           |

---

## 🟦 1. MAX7219 8×8 LED Matrix

The display contains **64 individual LEDs**, arranged as:

```text
8 columns × 8 rows = 64 LEDs
```

Instead of controlling 64 Arduino pins individually, the project uses a **MAX7219 driver**.

The MAX7219 handles the electrical control of the LEDs and allows the Arduino to send display data using only a few communication lines.

### MAX7219 pins used

| MAX7219 | Arduino |
| ------- | ------: |
| DIN     |     D11 |
| CS      |     D10 |
| CLK     |     D13 |
| VCC     |      5V |
| GND     |     GND |

The important communication pins are:

* **DIN (Data In)** — receives data from Arduino
* **CLK (Clock)** — synchronizes data transmission
* **CS (Chip Select)** — tells the MAX7219 when data is being sent

This is an **SPI-style serial communication interface**.

The project uses:

```cpp
#include <LedControl.h>
```

and creates the display object:

```cpp
LedControl lc = LedControl(DIN_PIN, CLK_PIN, CS_PIN, 1);
```

The final `1` means that the Arduino is controlling **one MAX7219 device**.

### Useful `LedControl` functions

```cpp
lc.shutdown(0, false);
```

Turns the display on.

```cpp
lc.setIntensity(0, 5);
```

Sets the LED brightness.

```cpp
lc.clearDisplay(0);
```

Turns all LEDs off.

```cpp
lc.setLed(0, row, column, true);
```

Turns on one specific LED.

```cpp
lc.setRow(0, row, data);
```

Controls an entire row using a byte.

```cpp
lc.setColumn(0, column, data);
```

Controls an entire column using a byte.

---

# 🎮 2. Joystick Module

The joystick provides two analog values representing its position:

```cpp
const int VRX_PIN = A0;
const int VRY_PIN = A1;
```

### Joystick axes

| Pin | Function |
| --- | -------- |
| VRX | X-axis   |
| VRY | Y-axis   |
| VCC | Power    |
| GND | Ground   |

The Arduino reads the two axes using:

```cpp
analogRead(VRX_PIN);
analogRead(VRY_PIN);
```

The normal Arduino analog range is:

```text
0 ───────── 512 ───────── 1023
        center
```

The code uses thresholds:

```cpp
if (xVal < 300)
```

and

```cpp
if (xVal > 700)
```

to detect movement.

For example:

```text
             UP
              ↑
              |
LEFT ←────── CENTER ──────→ RIGHT
              |
              ↓
            DOWN
```

This allows the joystick to control the snake without needing separate buttons for each direction.

---

# 🐍 3. Representing the Snake

One of the most interesting parts of this project is how the snake is stored.

The code defines a structure:

```cpp
struct Point {
  int x, y;
};
```

A `Point` represents one position on the 8×8 display.

For example:

```text
Point {3, 4}
```

means:

```text
x = 3
y = 4
```

The snake itself is an array of points:

```cpp
Point snake[64];
```

Because the matrix contains 64 positions, the maximum possible snake length is 64.

Initially:

```cpp
int snakeLength = 3;
```

So the snake starts with three segments.

---

# 🧭 4. Direction Using `enum`

The project uses an enumeration:

```cpp
enum Direction { UP, DOWN, LEFT, RIGHT };
```

This makes the code easier to understand than using numbers such as `0`, `1`, `2`, and `3`.

The initial direction is:

```cpp
Direction dir = RIGHT;
```

So the snake starts moving to the right.

The joystick changes this value:

```cpp
dir = LEFT;
dir = RIGHT;
dir = UP;
dir = DOWN;
```

The program also prevents the snake from immediately turning into itself.

For example:

```cpp
if (xVal < 300 && dir != RIGHT)
```

means that the snake can turn left only if it is not currently moving right.

---

# 🍎 5. Food Generation

The food is represented by another `Point`:

```cpp
Point food;
```

Its coordinates are generated randomly:

```cpp
food.x = random(0, 8);
food.y = random(0, 8);
```

This gives coordinates from:

```text
0 ─ 7
```

which correspond to the eight columns and eight rows of the matrix.

The program also checks whether the generated position is already occupied by the snake.

If it is, another position is generated.

This prevents food from spawning directly inside the snake.

---

# 🎲 6. Random Number Generation

The project uses:

```cpp
randomSeed(analogRead(A2));
```

This provides a changing starting point for the random number generator.

A floating analog input such as `A2` can produce small variations caused by electrical noise.

That variation is used as the seed so the food does not always appear in exactly the same sequence.

---

# 🚶 7. Moving the Snake

The head is copied first:

```cpp
Point newHead = snake[0];
```

Then its position is changed depending on the direction.

For example:

```cpp
if (dir == RIGHT) newHead.x++;
```

If the snake is moving right, the X coordinate increases.

The body follows the previous segment:

```cpp
for (int i = snakeLength - 1; i > 0; i--) {
  snake[i] = snake[i - 1];
}
```

Conceptually:

```text
Before:

HEAD →  ● ● ●

After moving:

NEW HEAD → ● ● ●
             ↑
          body follows
```

Finally:

```cpp
snake[0] = newHead;
```

sets the new head position.

---

# 💥 8. Collision Detection

The game checks two major types of collisions.

### 🧱 Wall collision

The matrix boundaries are:

```text
x = 0 ... 7
y = 0 ... 7
```

If the snake moves outside these limits, the game ends.

Conceptually:

```text
┌────────┐
│        │
│  🐍    │
│        │
└────────┘
```

The snake cannot leave the 8×8 screen.

### 🐍 Self-collision

The program also checks whether the new head position is already occupied by another snake segment.

If it is:

```cpp
gameOver = true;
```

The game ends.

---

# 🍎 Eating Food

The program compares the head position with the food position:

```cpp
if (newHead.x == food.x && newHead.y == food.y)
```

If they match:

1. The snake grows.
2. New food is generated.

```cpp
snakeLength++;
spawnFood();
```

Therefore, the objective is simple:

> 🎯 Move the snake around the matrix, eat food, grow longer, and avoid the walls and yourself.

---

# 💡 9. Drawing the Game

Before drawing a new frame:

```cpp
lc.clearDisplay(0);
```

clears the previous image.

Then every snake segment is drawn:

```cpp
for (int i = 0; i < snakeLength; i++) {
  lc.setLed(0, snake[i].y, snake[i].x, true);
}
```

The food is also displayed.

It is intentionally made to blink:

```cpp
if (millis() % 200 < 100)
```

This creates a simple flashing effect without using `delay()`.

So the player can distinguish the food from the snake.

---

# ⏱️ 10. Why `millis()` Is Used

The game uses:

```cpp
millis()
```

to control the movement speed.

```cpp
if (millis() - lastMoveTime > gameSpeed)
```

with:

```cpp
const int gameSpeed = 300;
```

This means the snake moves approximately every **300 ms**.

Using `millis()` is better here than repeatedly using:

```cpp
delay(300);
```

because the program can continue reading the joystick and updating the display while waiting for the next movement.

This creates a more responsive game.

---

# 💀 11. Game Over Animation

When the snake crashes:

```cpp
if (gameOver) {
  flashGameOver();
  resetGame();
  return;
}
```

The entire matrix flashes three times.

The function:

```cpp
flashGameOver()
```

turns every row on:

```cpp
lc.setRow(0, r, 0xFF);
```

`0xFF` is:

```text
11111111
```

so all eight LEDs in that row turn on.

The result is:

```text
████████
████████
████████
████████
████████
████████
████████
████████
```

After three flashes, the game resets.

---

# 🔄 12. Game Reset

The game is restarted by:

```cpp
resetGame();
```

It restores:

* Snake length → 3
* Starting position
* Direction → RIGHT
* Game-over state → false
* New food position

The starting snake is:

```cpp
snake[0] = {3, 3};
snake[1] = {2, 3};
snake[2] = {1, 3};
```

So it initially looks approximately like:

```text
........
........
........
.🐍🐍🐍....
........
........
........
........
```

---

## 🧠 Main Programming Concepts

This project combines several important Arduino and C++ concepts:

* 🎮 Analog input with `analogRead()`
* 💡 LED matrix control
* 📡 Serial communication with the MAX7219
* 🧱 Arrays
* 📦 `struct`
* 🧭 `enum`
* 🔀 Conditional statements
* 🔄 Loops
* 🎲 Random number generation
* 💥 Collision detection
* ⏱️ Non-blocking timing with `millis()`
* 📍 Coordinate systems
* 🧠 Game-state management
* 📚 External libraries

---

## 🔗 Component Relationship

```text
                 ┌─────────────────┐
                 │     Arduino     │
                 │                 │
                 │   Game Logic    │
                 └───────┬─────────┘
                         │
              ┌──────────┴──────────┐
              │                     │
              ▼                     ▼
       ┌─────────────┐       ┌─────────────┐
       │  Joystick   │       │  MAX7219    │
       │             │       │   Matrix    │
       │ X → A0      │       │             │
       │ Y → A1      │       │   8 × 8     │
       └─────────────┘       └─────────────┘
              │                     │
              │                     │
        Player Input           Game Output
```

---

## ⚙️ Important Note

The joystick thresholds:

```cpp
xVal < 300
xVal > 700
yVal < 300
yVal > 700
```

may need to be adjusted depending on the particular joystick module and its center values.

Likewise, the matrix orientation can differ depending on the MAX7219 module. If the snake appears mirrored or rotated, the X/Y coordinates can be adjusted in the drawing logic.

---

## 🎯 Project Goal

The main purpose of this project is not only to create a playable Snake game, but to understand how a relatively complex interactive system can be built from simple hardware and programming concepts.

It demonstrates how **input → processing → output** works:

```text
🎮 Joystick
     ↓
Read X/Y values
     ↓
Determine direction
     ↓
Update snake position
     ↓
Check collisions / food
     ↓
Update game state
     ↓
💡 8×8 LED Matrix
```

This makes the project a good step toward larger embedded systems and game-development projects.
