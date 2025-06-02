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
    runningBarEffect();  // Call the running bar effect
    delay(200);
}

// Function to send data to shift register
void shiftData(byte dataOut) {
    digitalWrite(LatchPin, LOW);  // Prepare shift register for data
    shiftOut(DataPin, ClockPin, MSBFIRST, dataOut);  // Send data
    digitalWrite(LatchPin, HIGH); // Output data to LEDs
}

// Function to create a running bar effect
void runningBarEffect() {
    // Move LED bar forward
    for (int i = 0; i < 4; i++) {  
        Data = (0b111 << i);  // 3 LEDs ON in a row
        shiftData(Data);
        delay(200);
    }

    // Move LED bar backward
    for (int i = 3; i >= 0; i--) {  
        Data = (0b111 << i);
        shiftData(Data);
        delay(200);
    }
}
