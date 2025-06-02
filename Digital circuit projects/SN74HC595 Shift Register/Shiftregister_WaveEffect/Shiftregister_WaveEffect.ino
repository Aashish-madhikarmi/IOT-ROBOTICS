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
    waveEffect();  // Call wave effect function
    delay(500);
}

// Function to send data to shift register
void shiftData(byte dataOut) {
    digitalWrite(LatchPin, LOW);  // Prepare shift register for data
    shiftOut(DataPin, ClockPin, MSBFIRST, dataOut);  // Send data
    digitalWrite(LatchPin, HIGH); // Output data to LEDs
}

// Function to create a wave effect
void waveEffect() {
    for (int i = 0; i < 6; i++) {  // Assuming 6-bit LEDs
        Data = (1 << i) | (1 << (i + 1)); // Two adjacent LEDs ON
        shiftData(Data);
        delay(200);
    }
    
    for (int i = 6; i > 0; i--) {  // Move wave backward
        Data = (1 << i) | (1 << (i - 1));
        shiftData(Data);
        delay(200);
    }
}
