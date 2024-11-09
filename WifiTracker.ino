#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// Wi-Fi Configuration
const char* primarySSID = "Your_WiFi_SSID";        // Replace with your Wi-Fi network SSID
const char* primaryPassword = "Your_WiFi_Password"; // Replace with your Wi-Fi network password

// Web Server Setup
ESP8266WebServer server(80);

// Intruder Detection and Signal Strength
const String authorizedDevices[] = {"AA:BB:CC:DD:EE:FF", "11:22:33:44:55:66"}; // Replace with known MAC addresses
volatile int intruderDetectedCount = 0;
int rssiThreshold = -70; // RSSI threshold for intruder proximity estimation

void setup() {
  Serial.begin(115200);
  
  // Connect to Wi-Fi
  WiFi.begin(primarySSID, primaryPassword);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to primary network!");

  // Set up Web Server
  server.on("/", handleRoot);
  server.begin();
  Serial.println("Web server started!");

  // Enable Promiscuous Mode for Signal Strength Analysis
  wifi_set_opmode(STATION_MODE);
  wifi_promiscuous_enable(1);
  wifi_set_promiscuous_rx_cb(promiscuousCallback);
}

void promiscuousCallback(uint8_t* buf, uint16_t len) {
  // Read MAC Address of Detected Device
  String mac = String(buf[10], HEX) + ":" + String(buf[11], HEX) + ":" + String(buf[12], HEX) +
               ":" + String(buf[13], HEX) + ":" + String(buf[14], HEX) + ":" + String(buf[15], HEX);

  bool isAuthorized = false;
  for (String device : authorizedDevices) {
    if (mac.equalsIgnoreCase(device)) {
      isAuthorized = true;
      break;
    }
  }

  if (!isAuthorized) {
    intruderDetectedCount++;
    int rssi = WiFi.RSSI(); // Get RSSI value to estimate proximity
    Serial.print("Unauthorized device detected: " + mac + " RSSI: ");
    Serial.println(rssi);

    if (rssi >= rssiThreshold) {
      Serial.println("Intruder device is close to the network.");
    }
  }
}

void handleRoot() {
  String html = "<html><head><title>Wi-Fi Signal Strength & Intruder Locator</title></head><body>";
  html += "<h1>Wi-Fi Signal Analyzer & Intruder Locator</h1>";
  html += "<p>Intruder Count: " + String(intruderDetectedCount) + "</p>";
  html += "<p>RSSI Threshold: " + String(rssiThreshold) + "</p>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}

void loop() {
  server.handleClient();
  delay(1000); // Check every second for web interface refresh
}
