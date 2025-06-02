#include <LedControl.h>

LedControl lc = LedControl(11, 13, 10, 1); // DIN, CLK, CS, No. of matrices

byte heart[] = {
  0b00100100,
  0b01111110,
  0b01111110,
  0b01111110,
  0b00111100,
  0b00011000,
  0b00000000,
  0b00000000
};

void setup() {
  lc.shutdown(0, false);  
  lc.setIntensity(0, 5); 
  lc.clearDisplay(0);
}

void loop() {
  displayPattern(heart);
}

void displayPattern(byte pattern[]) {
  for (int row = 0; row < 8; row++) {
    lc.setRow(0, row, pattern[row]);
  }
}
