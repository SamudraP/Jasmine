#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DHT.h>

// WiFi credentials
const char* ssid = "Nokia 5.3";
const char* password = "Jachu123@@";

// DHT configuration
#define DHTPIN 2

#define DHTTYPE DHT11  // or DHT22

DHT dht(DHTPIN, DHTTYPE);
ESP8266WebServer server(80); // HTTP server on port 80

// Handle root page
void handleRoot() {
  float temp = dht.readTemperature();

  Serial.print(temp);


  String html = "<html><head><title>Temperature</title></head><body>";
  html += "<h2>NodeMCU Web Server</h2>";
  html += "<p><strong>Current Temperature:</strong> ";

  if (isnan(temp)) {
    html += "Error reading temperature";
  } else {
    html += String(temp) + " &deg;C";
  }

  html += "</p></body></html>";
  server.send(200, "text/html", html);
}

void setup() {
  Serial.begin(115200);
  dht.begin();

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Define server route
  server.on("/", handleRoot);
  server.begin();
  Serial.println("Web server started");
}

void loop() {
  server.handleClient();
}