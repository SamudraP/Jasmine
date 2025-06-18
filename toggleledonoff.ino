#include <ESP8266WiFi.h>

const char* ssid = "Nokia 5.3";         // Replace with your WiFi SSID
const char* password = "Jachu123@@"; // Replace with your WiFi Password

WiFiServer server(80);

int ledPin = LED_BUILTIN; // Built-in LED (GPIO2 / D4)
bool ledState = false;    // false = OFF, true = ON

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH); // OFF (Active LOW)

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected to WiFi");
  Serial.println("IP Address: " + WiFi.localIP().toString());

  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (!client) return;

  while (!client.available()) delay(1);

  String request = client.readStringUntil('\r');
  Serial.println("Request: " + request);
  client.flush();

  if (request.indexOf("/toggle") != -1) {
    ledState = !ledState;
    digitalWrite(ledPin, ledState ? LOW : HIGH); // Active LOW
  }

  // HTML Response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("Connection: close");
  client.println();
  client.println("<!DOCTYPE html>");
  client.println("<html><head><title>LED Toggle</title></head><body style='text-align:center;'>");
  client.println("<h1>NodeMCU LED Control</h1>");
  client.println("<p>LED is currently: <strong>" + String(ledState ? "ON" : "OFF") + "</strong></p>");
  client.println("<a href='/toggle'><button style='padding:10px 20px;font-size:16px;'>Toggle LED</button></a>");
  client.println("</body></html>");

  delay(1);
}