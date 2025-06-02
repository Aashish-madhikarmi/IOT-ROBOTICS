int DataPin = 2;   // Data Pin is connected to Pin No. 2
int ClockPin = 3;  // Clock Pin is connected to Pin No. 3
int LatchPin = 4;  // Latch Pin is connected to Pin No. 4
byte Data = 0;     // 6-bit data to be sent through DataPin

void setup() {
    pinMode(DataPin, OUTPUT);  // All 3 pins are output
    pinMode(ClockPin, OUTPUT);
    pinMode(LatchPin, OUTPUT);
}

void loop() {
    increment();  // LEDs increment from 0 - 5
    delay(100);
    clearRegisters();  // Clear LED states
    delay(500);
}

// Function to send data to shift register
void shiftData(byte dataOut) {
    digitalWrite(LatchPin, LOW); // Prepare shift register for data
    shiftOut(DataPin, ClockPin, MSBFIRST, dataOut); // Send data
    digitalWrite(LatchPin, HIGH); // Output data to LEDs
}

// Function to increment LED sequence
void increment() {
    for (int i = 0; i < 6; i++) { // Assuming 6-bit data
        Data = (1 << i); // Shift bit to light up LEDs sequentially
        shiftData(Data);
        delay(200);
    }
}

// Function to clear all registers (turn off LEDs)
void clearRegisters() {
    Data = 0;
    shiftData(Data);
}
