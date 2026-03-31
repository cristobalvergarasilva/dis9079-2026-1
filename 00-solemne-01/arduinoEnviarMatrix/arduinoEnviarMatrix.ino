#include <WiFiS3.h>
#include <WiFiUdp.h>

// --- WIFI ---
const char* ssid = "dis9079";
const char* password = "75288273";

// --- UDP ---
WiFiUDP udp;
IPAddress receiverIP(255, 255, 255, 255);  // 👈 PUT RECEIVER IP HERE
int port = 1234;

// --- SERIAL INPUT ---
String input = "";

void setup() {
  Serial.begin(115200);
  delay(1000);

  // Connect WiFi
  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Wait for IP (same fix as before)
  while (WiFi.localIP() == IPAddress(0, 0, 0, 0)) {
    delay(200);
    Serial.print("⏳");
  }

  Serial.println("\n✅ Connected!");
  Serial.print("My IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  Serial.print("Sending to: ");
  Serial.println(receiverIP);
  udp.beginPacket(receiverIP, port);
  udp.print("2,3");
  udp.endPacket();

  Serial.println("Sent test packet");
  delay(1000);
}

void sendMessage(String msg) {
  udp.beginPacket(receiverIP, port);
  udp.print(msg);
  udp.endPacket();

  Serial.print("📤 Sent: ");
  Serial.println(msg);
}