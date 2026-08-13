#include <Servo.h>

Servo myServo;

const int soundPin = A0;
const int servoPin = 9;

// Piezo / Microphone sensitivity threshold
const int threshold = 100; 

int knockCount = 0;
unsigned long firstKnockTime = 0;
unsigned long lastKnockTime = 0;
bool isOpen = false;

void setup() {
  myServo.attach(servoPin);
  myServo.write(0); // Initial locked position (0 degrees)
  Serial.begin(115200);
  Serial.println("=== Strict 3-Knock Lock System Ready! ===");
}

void loop() {
  // Peak-to-Peak analog reading to capture vibration spikes
  unsigned long startMillis = millis();
  unsigned int signalMax = 0, signalMin = 1024;

  while (millis() - startMillis < 25) {
    int sample = analogRead(soundPin);
    if (sample < 1024) {
      if (sample > signalMax) signalMax = sample;
      if (sample < signalMin) signalMin = sample;
    }
  }

  int peakToPeak = signalMax - signalMin;

  // Knock detected
  if (peakToPeak > threshold) {
    unsigned long now = millis();

    // Debounce guard to avoid echo/false double triggers (120ms gap)
    if (now - lastKnockTime > 120) {
      if (knockCount == 0) {
        firstKnockTime = now; // Start the 1.5-second evaluation window
      }
      
      knockCount++;
      lastKnockTime = now;

      Serial.print("Knock detected! Total count: ");
      Serial.println(knockCount);
    }
  }

  // TIME EXPIRED: 1.5 seconds passed since the first knock — Evaluate passcode
  if (knockCount > 0 && (millis() - firstKnockTime > 1500)) {
    
    if (knockCount == 3) {
      // Exactly 3 knocks registered
      Serial.println(">>> ACCESS GRANTED (Exact 3 knocks)! Toggling lock... <<<");
      isOpen = !isOpen;
      myServo.write(isOpen ? 90 : 0);
      delay(500); // Pause for servo motion stabilization
    } else {
      // Deny access for 1, 2, 4, or more knocks
      Serial.print(">>> ACCESS DENIED! Knock count was: ");
      Serial.print(knockCount);
      Serial.println(" (Requires exactly 3 knocks) <<<");
    }

    // Reset counters for the next attempt
    knockCount = 0;
  }
}