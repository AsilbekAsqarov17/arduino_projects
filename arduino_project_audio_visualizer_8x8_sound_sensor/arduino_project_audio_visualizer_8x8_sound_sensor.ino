#include <LedControl.h>

// MAX7219 Pins
const int DIN_PIN = 11;
const int CS_PIN  = 10;
const int CLK_PIN = 13;

// Microphone Sensor Pin
const int MIC_PIN = A0;

LedControl lc = LedControl(DIN_PIN, CLK_PIN, CS_PIN, 1);

static int history[8] = {0};

const int NOISE_FLOOR = 14; 

void setup() {
  Serial.begin(9600);
  
  lc.shutdown(0, false);
  lc.setIntensity(0, 8); 
  lc.clearDisplay(0);

  for (int row = 0; row < 8; row++) {
    lc.setRow(0, row, 0xFF);
  }
  delay(300);
  lc.clearDisplay(0);
}

void loop() {
  int signalMax = 0;
  int signalMin = 1024;

  unsigned long startMillis = millis();
  while (millis() - startMillis < 30) {
    int sample = analogRead(MIC_PIN);
    if (sample > signalMax) signalMax = sample;
    if (sample < signalMin) signalMin = sample;
  }

  int peakToPeak = signalMax - signalMin;

  Serial.print("Peak-to-Peak: ");
  Serial.println(peakToPeak);

  int barHeight = 0;

  if (peakToPeak > NOISE_FLOOR) {
    barHeight = map(peakToPeak, NOISE_FLOOR + 1, 45, 1, 8);
    barHeight = constrain(barHeight, 0, 8);
  }

  for (int i = 0; i < 7; i++) {
    history[i] = history[i + 1];
  }
  history[7] = barHeight;

  for (int col = 0; col < 8; col++) {
    byte columnBits = 0;
    
    for (int bit = 0; bit < history[col]; bit++) {
      columnBits |= (1 << bit);
    }
    
    lc.setColumn(0, col, columnBits);
  }
}