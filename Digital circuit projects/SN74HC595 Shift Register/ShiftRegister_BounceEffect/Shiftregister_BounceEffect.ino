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
    bouncingEffect();  // Call bouncing LED function
    delay(200);
}

// Function to send data to shift register
void shiftData(byte dataOut) {
    digitalWrite(LatchPin, LOW);  // Prepare shift register for data
    shiftOut(DataPin, ClockPin, MSBFIRST, dataOut);  // Send data
    digitalWrite(LatchPin, HIGH); // Output data to LEDs
}

// Function to create bouncing LED effect
void bouncingEffect() {
    // Move LED forward
    for (int i = 0; i < 6; i++) {  
        Data = (1 << i);  // Light up one LED at a time
        shiftData(Data);
        delay(150);
    }

    // Move LED backward
    for (int i = 5; i > 0; i--) {  
        Data = (1 << i);
        shiftData(Data);
        delay(150);
    }
}
