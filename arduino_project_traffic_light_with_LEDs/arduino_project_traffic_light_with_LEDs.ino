const int GREEN_LED  = 11;
const int YELLOW_LED = 10;
const int RED_LED    = 9;

const unsigned long GREEN_TIME  = 8000;  // 8 seconds 
const unsigned long RED_TIME    = 8000;  // 8 seconds 
const unsigned long TRANSITION  = 2000;  // 2 seconds 
const unsigned long BLINK_SPEED = 400;   // 0.4 seconds 

void blinkLED(int pin, int times, int duration) {
  for (int i = 0; i < times; i++) {
    digitalWrite(pin, HIGH);
    delay(duration);
    digitalWrite(pin, LOW);
    delay(duration);
  }
}

void setup() {
  pinMode(GREEN_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
}

void loop() {
  
  digitalWrite(GREEN_LED, HIGH);
  delay(GREEN_TIME);
  digitalWrite(GREEN_LED, LOW);

  blinkLED(GREEN_LED, 3, BLINK_SPEED);

  digitalWrite(YELLOW_LED, HIGH);
  delay(TRANSITION);
  digitalWrite(YELLOW_LED, LOW);

  digitalWrite(RED_LED, HIGH);
  delay(RED_TIME);

  digitalWrite(YELLOW_LED, HIGH);
  delay(1500);

  digitalWrite(RED_LED, LOW);
  digitalWrite(YELLOW_LED, LOW);
}