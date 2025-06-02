#include <DHT.h>

#define DHTPIN 2     // Change if needed
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
  Serial.println("DHT11 sensor test");
}

void loop() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
  } else {
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.print("%, Temp: ");
    Serial.print(temperature);
    Serial.println(" *C");
  }
  delay(2000); // Wait 2 seconds between readings
}