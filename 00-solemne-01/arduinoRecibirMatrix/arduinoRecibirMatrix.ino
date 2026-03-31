#include <WiFiS3.h>
#include <WiFiUdp.h>
#include "Arduino_LED_Matrix.h"

ArduinoLEDMatrix matrix;

// --- WIFI ---
const char* ssid = "dis9079";
const char* password = "75288273";

// --- UDP ---
WiFiUDP udp;
int port = 1234;

// --- GRID ---
const int cols = 12;
const int rows = 8;
bool grid[cols][rows];

void setup() {
  Serial.begin(115200);
  delay(1000);

  // --- Connect WiFi ---
  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid, password);

  int attempts = 0;

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    attempts++;

    if (attempts > 40) {  // ~20 seconds timeout
      Serial.println("\n❌ Failed to connect!");
      Serial.println("Check SSID / password / 2.4GHz network");
      return;  // stop setup
    }
  }

  while (WiFi.localIP() == IPAddress(0, 0, 0, 0)) {
    delay(200);
    Serial.print("⏳");
  }

  Serial.println("\n✅ Connected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());


  // --- Start UDP ---
  udp.begin(port);
  Serial.print("Listening on port: ");
  Serial.println(port);

  // --- Init Matrix ---
  matrix.begin();

  // --- Clear grid ---
  for (int x = 0; x < cols; x++) {
    for (int y = 0; y < rows; y++) {
      grid[x][y] = false;
    }
  }

  drawMatrix();
}

void loop() {
  int packetSize = udp.parsePacket();

  if (packetSize) {
    char packet[50];

    int len = udp.read(packet, sizeof(packet) - 1);
    if (len > 0) {
      packet[len] = '\0';
    }

    Serial.print("Received: ");
    Serial.println(packet);

    handleMessage(String(packet));
    drawMatrix();
  }
}

// --- Parse "x,y" ---
void handleMessage(String msg) {
  int commaIndex = msg.indexOf(',');

  if (commaIndex == -1) {
    Serial.println("Invalid format");
    return;
  }

  int x = msg.substring(0, commaIndex).toInt();
  int y = msg.substring(commaIndex + 1).toInt();

  Serial.print("Parsed -> x: ");
  Serial.print(x);
  Serial.print(" y: ");
  Serial.println(y);

  if (x >= 0 && x < cols && y >= 0 && y < rows) {
    grid[x][y] = !grid[x][y];  // toggle
  } else {
    Serial.println("Out of bounds");
  }
}

void drawMatrix() {
  uint8_t frame[8][12];  // <-- THIS is key

  for (int y = 0; y < rows; y++) {
    for (int x = 0; x < cols; x++) {
      frame[y][x] = grid[x][y] ? 1 : 0;
    }
  }

  matrix.renderBitmap(frame, 8, 12);
}