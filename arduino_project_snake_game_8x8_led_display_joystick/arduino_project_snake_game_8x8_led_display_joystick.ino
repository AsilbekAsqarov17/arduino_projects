#include <LedControl.h>

// Pins for MAX7219 LED Matrix
const int DIN_PIN = 11;
const int CS_PIN  = 10;
const int CLK_PIN = 13;

// Pins for Joystick
const int VRX_PIN = A0;
const int VRY_PIN = A1;

LedControl lc = LedControl(DIN_PIN, CLK_PIN, CS_PIN, 1);

enum Direction { UP, DOWN, LEFT, RIGHT };
Direction dir = RIGHT;

struct Point {
  int x, y;
};

Point snake[64]; 
int snakeLength = 3;

Point food;
bool gameOver = false;
unsigned long lastMoveTime = 0;
const int gameSpeed = 300; 

void spawnFood() {
  bool valid = false;
  while (!valid) {
    food.x = random(0, 8);
    food.y = random(0, 8);
    valid = true;
    for (int i = 0; i < snakeLength; i++) {
      if (snake[i].x == food.x && snake[i].y == food.y) {
        valid = false;
        break;
      }
    }
  }
}

void resetGame() {
  snakeLength = 3;
  snake[0] = {3, 3}; 
  snake[1] = {2, 3};
  snake[2] = {1, 3};
  dir = RIGHT;
  gameOver = false;
  spawnFood();
}

void setup() {
  lc.shutdown(0, false);
  lc.setIntensity(0, 5); 
  lc.clearDisplay(0);
  
  randomSeed(analogRead(A2)); 
  resetGame();
}

void readJoystick() {
  int xVal = analogRead(VRX_PIN);
  int yVal = analogRead(VRY_PIN);

  if (xVal < 300 && dir != RIGHT) dir = LEFT;
  else if (xVal > 700 && dir != LEFT) dir = RIGHT;
  else if (yVal < 300 && dir != DOWN) dir = UP;
  else if (yVal > 700 && dir != UP) dir = DOWN;
}

void updateGame() {
  Point newHead = snake[0];
  if (dir == UP)    newHead.y--;
  if (dir == DOWN)  newHead.y++;
  if (dir == LEFT)  newHead.x--;
  if (dir == RIGHT) newHead.x++;

  if (newHead.x < 0 || newHead.x >= 8 || newHead.y < 0 || newHead.y >= 8) {
    gameOver = true;
    return;
  }

  for (int i = 0; i < snakeLength; i++) {
    if (snake[i].x == newHead.x && snake[i].y == newHead.y) {
      gameOver = true;
      return;
    }
  }

  for (int i = snakeLength - 1; i > 0; i--) {
    snake[i] = snake[i - 1];
  }
  snake[0] = newHead;

  if (newHead.x == food.x && newHead.y == food.y) {
    if (snakeLength < 64) {
      snakeLength++;
    }
    spawnFood();
  }
}

void draw() {
  lc.clearDisplay(0);

  for (int i = 0; i < snakeLength; i++) {
    lc.setLed(0, snake[i].y, snake[i].x, true);
  }

  static bool foodState = true;
  if (millis() % 200 < 100) {
    lc.setLed(0, food.y, food.x, true);
  }
}

void flashGameOver() {
  for (int i = 0; i < 3; i++) {
    for (int r = 0; r < 8; r++) lc.setRow(0, r, 0xFF);
    delay(200);
    lc.clearDisplay(0);
    delay(200);
  }
}

void loop() {
  if (gameOver) {
    flashGameOver();
    resetGame();
    return;
  }

  readJoystick();

  if (millis() - lastMoveTime > gameSpeed) {
    lastMoveTime = millis();
    updateGame();
  }

  draw();
}