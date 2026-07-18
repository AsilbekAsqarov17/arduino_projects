int leds[] = {8, 9, 10, 11};
int numLEDs = 4;

void convertDecimalToBinaryArray(const int decimal_nums[], String binary_nums[], int size) {
    
    for (int i = 0; i < size; i++) {
        int num = decimal_nums[i];
        String binaryString = "";
        
        if (num == 0) {
            binaryString = "0";
        } else {
            while (num > 0) {
                int remainder = num % 2;
                binaryString = String(remainder) + binaryString;
                num /= 2;
            }
        }
        
        while (binaryString.length() < 4) {
            binaryString = "0" + binaryString;
        }
        
        binary_nums[i] = binaryString;
    }
}


void setup(){

  for (int i = 0; i < numLEDs; i++) {
    pinMode(leds[i], OUTPUT);
  }

}

void loop(){

   int decimalArray[] = {0,1,2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    const int size = sizeof(decimalArray) / sizeof(decimalArray[0]);
    
    String binaryArray[size];
    
    convertDecimalToBinaryArray(decimalArray, binaryArray, size);
    
    for (int i = 0; i < size; i++) {
        for (int bit = 0; bit < 4; bit++) {
         digitalWrite(leds[bit], binaryArray[i][bit] == '1' ? HIGH : LOW);
      }
      delay(1000);
    }
  delay(2000);

}