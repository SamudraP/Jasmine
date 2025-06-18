#include <ESP8266WiFi.h>

const char* ssid = "Nokia 5.3";       // Replace with your Wi-Fi SSID
const char* password = "Jachu123@@";   // Replace with your Wi-Fi Password

WiFiServer server(80);

int ledPin = LED_BUILTIN; // Built-in LED (D4 -> GPIO2)
String ledStatus = "OFF";

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH); // LED OFF (active LOW)

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected to WiFi");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    String request = client.readStringUntil('\r');
    Serial.println(request);
    client.flush();

    // Handle LED control
    if (request.indexOf("/LED=ON") != -1) {
      digitalWrite(ledPin, LOW); // Turn ON (active LOW)
      ledStatus = "ON";
    }
    if (request.indexOf("/LED=OFF") != -1) {
      digitalWrite(ledPin, HIGH); // Turn OFF
      ledStatus = "OFF";
    }

    // Send HTML response
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("Connection: close");
    client.println();

    client.println("<!DOCTYPE html>");
    client.println("<html>");
    client.println("<head><title>NodeMCU LED Control</title></head>");
    client.println("<body style='text-align:center;'>");
    client.println("<h1>NodeMCU LED Control</h1>");
    client.println("<p>Status: <strong>" + ledStatus + "</strong></p>");
    client.println("<a href=\"/LED=ON\"><button>Turn ON</button></a>");
    client.println("<a href=\"/LED=OFF\"><button>Turn OFF</button></a>");
    client.println("</body></html>");
    
    delay(1);
  }
}