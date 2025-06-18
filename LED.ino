#define LED_PIN 5  // Replace D1 with 5 (GPIO5)

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  Serial.println("Type ON or OFF to control the LED.");
}

void loop() {
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    command.trim();

    if (command.equalsIgnoreCase("ON")) {
      digitalWrite(LED_PIN, HIGH);
      Serial.println("LED ON");
    } else if (command.equalsIgnoreCase("OFF")) {
      digitalWrite(LED_PIN, LOW);
      Serial.println("LED OFF");
    } else {
      Serial.println("Invalid command.");
    }
  }
}
