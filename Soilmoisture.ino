#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11
#define SOIL_PIN A0
#define RELAY_PIN 3

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH); // Relay OFF by default
}

void loop() {
  int soilValue = analogRead(SOIL_PIN);
  float soilPercent = map(soilValue, 1023, 0, 0, 100); // Adjust based on calibration

  float temp = dht.readTemperature();

  Serial.print("Soil Moisture: ");
  Serial.print(soilPercent);
  Serial.print("% | Temp: ");
  Serial.print(temp);
  Serial.println("°C");

  // Condition to trigger pump
  if (soilPercent < 30 || temp > 36) {
    digitalWrite(RELAY_PIN, LOW);  // Turn ON relay
    Serial.println("Pump ON");
  } else {
    digitalWrite(RELAY_PIN, HIGH); // Turn OFF relay
    Serial.println("Pump OFF");
  }

  delay(2000); // Delay 2 seconds
}
 