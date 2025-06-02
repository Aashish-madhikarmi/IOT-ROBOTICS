int DataPin = 2;   // Data Pin connected to Pin 2
int ClockPin = 3;  // Clock Pin connected to Pin 3
int LatchPin = 4;  // Latch Pin connected to Pin 4
byte Data = 0;     // Data to be sent to shift register

void setup() {
    pinMode(DataPin, OUTPUT);
    pinMode(ClockPin, OUTPUT);
    pinMode(LatchPin, OUTPUT);
}

void loop() {
    fillLEDs();   // Fill LEDs one by one
    delay(500);
    clearLEDs();  // Clear LEDs one by one
    delay(500);
}

// Function to send data to shift register
void shiftData(byte dataOut) {
    digitalWrite(LatchPin, LOW);  // Prepare shift register for data
    shiftOut(DataPin, ClockPin, MSBFIRST, dataOut);  // Send data
    digitalWrite(LatchPin, HIGH); // Output data to LEDs
}

// Function to fill LEDs one by one
void fillLEDs() {
    for (int i = 0; i < 6; i++) {  
        Data |= (1 << i); // Turn on LEDs one by one
        shiftData(Data);
        delay(200);
    }
}

// Function to clear LEDs one by one
void clearLEDs() {
    for (int i = 5; i >= 0; i--) {  
        Data &= ~(1 << i); // Turn off LEDs one by one
        shiftData(Data);
        delay(200);
    }
}
