#include <DHT.h>

// --- Pin Setup ---
#define DHTPIN 2           // DHT11 data pin
#define DHTTYPE DHT11      // DHT sensor type
#define SOIL_PIN A0        // Soil sensor analog pin
#define SPRAY_PIN 8        // Pump or spray control (relay)

// --- Thresholds ---
const int soilDryThreshold = 700;   // Above this = dry
const float humidityLowThreshold = 40.0;  // Below this = low humidity

// --- Sensor Objects ---
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();

  pinMode(SPRAY_PIN, OUTPUT);
  digitalWrite(SPRAY_PIN, LOW);  // Start with spray OFF
}

void loop() {
  // Read soil and humidity
  int soilValue = analogRead(SOIL_PIN);
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Print sensor data
  Serial.print("Soil: ");
  Serial.print(soilValue);
  Serial.print(" | Humidity: ");
  Serial.print(humidity);
  Serial.print("% | Temp: ");
  Serial.println(temperature);

  // Condition to spray: soil is dry AND humidity is low
  if (soilValue > soilDryThreshold && humidity < humidityLowThreshold) {
    Serial.println(">> Soil is dry & air is dry — Spraying...");
    digitalWrite(SPRAY_PIN, HIGH);  // Turn ON sprayer
    delay(5000);                    // Spray for 5 seconds
    digitalWrite(SPRAY_PIN, LOW);   // Turn OFF sprayer
  } else {
    Serial.println(">> Conditions not met — No spray");
    digitalWrite(SPRAY_PIN, LOW);
  }

  delay(2000); // Wait 2 seconds before next check
}
