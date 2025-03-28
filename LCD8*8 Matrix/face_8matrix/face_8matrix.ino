#include <LedControl.h>

// Create an instance of LedControl (DIN, CLK, CS, num of MAX7219 chips)
LedControl lc = LedControl(11, 13, 10, 1);

void setup() {
    lc.shutdown(0, false);  // Wake up the display
    lc.setIntensity(0, 8);  // Set brightness level (0-15)
    lc.clearDisplay(0);     // Clear the display
}

void loop() {
    // Example pattern: Smiley Face
    byte smiley[8] = {
        B00111100,
        B01000010,
        B10100101,
        B10000001,
        B10100101,
        B10011001,
        B01000010,
        B00111100
    };
    displayPattern(smiley);
    delay(1000);
}

void displayPattern(byte pattern[8]) {
    for (int i = 0; i < 8; i++) {
        lc.setRow(0, i, pattern[i]);
    }
}
