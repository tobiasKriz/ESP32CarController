#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "ESP32-AP";
const char* password = "12345678";

// Define two GPIO pins
const int PIN1 = 8;
const int PIN2 = 9;

WebServer server(80);

// Handle button state
void handleButton() {
  String pin = server.arg("pin");
  String state = server.arg("state");
  Serial.println("Received pin: " + pin + ", state: " + state);

  // Control the appropriate pin based on request
  if (pin == "1") {
    if (state == "off") digitalWrite(PIN1, LOW);
    else digitalWrite(PIN1, HIGH);
  } 
  else if (pin == "2") {
    if (state == "off") digitalWrite(PIN2, LOW);
    else digitalWrite(PIN2, HIGH);
  }

  server.send(200, "text/plain", "OK");
}

void setup() {
  Serial.begin(9600);
  pinMode(PIN1, OUTPUT);
  pinMode(PIN2, OUTPUT);

  // Start Wi-Fi in Access Point mode
  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("ESP32 AP IP address: ");
  Serial.println(IP);

  // Setup endpoint
  server.on("/button", handleButton);
  server.begin();
}

void loop() {
  server.handleClient();
}
