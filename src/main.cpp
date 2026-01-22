#include <WiFi.h>
#include <WebServer.h>

// ====== ACCESS POINT SETTINGS ======
const char* ap_ssid = "ESP32_AP";
const char* ap_password = "test123test"; // min 8 chars

WebServer server(80);

// ====== WEB PAGE HANDLER ======
void handleRoot() {
  server.send(
    200,
    "text/html",
    "<!DOCTYPE html>"
    "<html>"
    "<head><title>ESP32 AP</title></head>"
    "<body>"
    "<h1>Hello from ESP32 (AP Mode)</h1>"
    "</body>"
    "</html>"
  );
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println();
  Serial.println("Starting ESP32 Access Point...");

  // ====== START ACCESS POINT ======
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ap_ssid, ap_password);

  IPAddress apIP = WiFi.softAPIP();

  Serial.println("Access Point started");
  Serial.print("SSID: ");
  Serial.println(ap_ssid);
  Serial.print("IP address: ");
  Serial.println(apIP);

  // ====== WEB SERVER ======
  server.on("/", handleRoot);
  server.begin();

  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
