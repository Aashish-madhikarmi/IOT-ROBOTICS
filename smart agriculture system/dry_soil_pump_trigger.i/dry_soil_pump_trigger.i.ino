const int soilPin = A0;        // Analog input pin for soil sensor
const int pumpPin = 8;         // Digital output pin to control the water pump (via relay or transistor)
int soilValue = 0;

void setup() {
  Serial.begin(9600);
  pinMode(pumpPin, OUTPUT);
  digitalWrite(pumpPin, LOW);  // Make sure pump is OFF at start
}

void loop() {
  soilValue = analogRead(soilPin);

  // Print the raw analog value
  Serial.print("Soil Moisture Value: ");
  Serial.println(soilValue);

  // Interpret value and control pump
  if (soilValue < 300) {
    Serial.println("Soil is Wet");
    digitalWrite(pumpPin, LOW);  // Turn pump OFF
  } 
  else if (soilValue < 700) {
    Serial.println("Soil is Moist");
    digitalWrite(pumpPin, LOW);  // Turn pump OFF
  } 
  else {
    Serial.println("Soil is Dry - Pump ON");
    digitalWrite(pumpPin, HIGH);  // Turn pump ON
    delay(5000);                  // Run pump for 5 seconds
    digitalWrite(pumpPin, LOW);   // Turn pump OFF
  }

  delay(2000);  // Check every 2 seconds
}
