int DataPin = 2;   // Data Pin connected to Pin 2
int ClockPin = 3;  // Clock Pin connected to Pin 3
int LatchPin = 4;  // Latch Pin connected to Pin 4
byte Data = 0;     // Data to be sent to shift register

void setup() {
    pinMode(DataPin, OUTPUT);
    pinMode(ClockPin, OUTPUT);
    pinMode(LatchPin, OUTPUT);
    randomSeed(analogRead(0)); // Seed random number generator
}

void loop() {
    twinkleEffect();  // Call the twinkle effect
    delay(200);
}

// Function to send data to shift register
void shiftData(byte dataOut) {
    digitalWrite(LatchPin, LOW);  // Prepare shift register for data
    shiftOut(DataPin, ClockPin, MSBFIRST, dataOut);  // Send data
    digitalWrite(LatchPin, HIGH); // Output data to LEDs
}

// Function to create a twinkling effect
void twinkleEffect() {
    for (int i = 0; i < 10; i++) {  // Run twinkle effect multiple times
        Data = random(0, 64);  // Generate a random pattern (0 to 63 for 6-bit LEDs)
        shiftData(Data);
        delay(150);
    }
}
