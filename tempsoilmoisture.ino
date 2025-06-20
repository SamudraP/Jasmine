#include <DHT.h>

// ----- Pin Definitions -----
#define DHTPIN 2            // DHT sensor connected to digital pin 2
#define DHTTYPE DHT11       // Or DHT22
#define SOIL_PIN A0         // Soil moisture sensor connected to analog pin A0
#define PUMP_PIN 3        // Relay control connected to digital pin 8
int rawSoil;
int soilMoisturePercent;

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);             // Serial Monitor
  dht.begin();                    // Initialize DHT sensor

  pinMode(PUMP_PIN, OUTPUT);      // Set pump relay pin as output
  digitalWrite(PUMP_PIN, LOW);    // Make sure pump is off at start

  Serial.println("Arduino UNO - Pump Control System Initialized");
}

void loop() {
  // Read temperature
  float temperature = dht.readTemperature(); // in Celsius
  float soilMoisturepercent();

  rawSoil = analogRead(SOIL_PIN);
  soilMoisturePercent = map(rawSoil, 452, 203, 0, 100);
  

  // Read soil moisture sensor
  // Serial.print(rawSoil);
   Serial.print("temparature : ");    
   Serial.print(temperature);  
   Serial.print("Moisture : ");           // Raw reading (0-1023)
   Serial.println(soilMoisturePercent); // % conversion

  // Display sensor data
  //Serial.print("Soil Moisture: ");
  //Serial.print(soilMoisturePercent);
 // Serial.print("% | Temperature: ");
  //Serial.print(temperature);
 // Serial.println("°C");

  // Trigger pump based on conditions
  if (soilMoisturePercent < 30 ) {
    digitalWrite(PUMP_PIN, HIGH);  // Turn pump ON
    Serial.println("Pump Status: ON");
  } else {
    digitalWrite(PUMP_PIN, LOW);   // Turn pump OFF
    Serial.println("Pump Status: OFF");
  }

  delay(2000); // Wait 2 seconds before next check
}