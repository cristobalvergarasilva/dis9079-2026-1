# grupo-07

## integrantes

* Josefa Araya 
* Débora Soto 
* Cristóbal Vergara

## descripción del proyecto

El Arduino se conecta a una red WiFi y luego establece comunicación con Adafruit IO usando el protocolo MQTT en Arduino Ide.
Desde cualquier otro computador o celular, entras al dashboard de Adafruit IO en el navegador y presionas un botón toggle. Ese click viaja por internet hasta los servidores de Adafruit, que se lo reenvían al Arduino. El Arduino recibe el mensaje y enciende o apaga el LED.

Partimos utilzando el codigo de ejemplo que subio Aaron a Github para aprender como funcionaban las conecciones base auna nube pero de primeras no funcionaba, y tras un rato investigando dimos con que estabamos dando mal las credenciales que habia que cambiar del codigo, puntualmente la clave que estabamos poniendo la personal para ingresar al sitio pero resulta que era la AIO Key, que es una clave alphanumerica que te da el Adafruit IO para poder conectarte a la nube.
Luego de solucionar eso el codigo estaba bien pero aun asi no se conectaba, solo aparecia una serie de puntos infinitos (...........) que no nos dimos cuenta hasta que en clases Aaron actualizó los Arduinos que tenian ese error y se soluciono, resulta que al final de los puntos habia un mensaje de "Please upgrade the WiFiS3 firmware!" pero no alcanzaba a verse.
Una vez actualizado el Arduino pudimos conectar bien con Adafruit IO y probamos con un ejercicio que nos dio Aaron que consistia en conectarse a un feed en Adafruit IO el cual estaba conectado a una Dashboard con un contador.




## conexiones 
![runway](./imagenes/conexiones.jpg)

![arduino conectado al led](./imagenes/arduino-conectado-a-led.jpeg)


## materiales usados en solemne-01
- 1 Arduino UNO R4 WIFI 
- 1 protoboard 400 puntos
- 1 pin LED 
- 1 OHM resistor de 220
- 1 cable Dupont M/M
  
## código usado con Adafruit IO

### código para enviar

```cpp
#include <WiFiS3.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

// ─── Configuración WiFi ───────────────────────────────
#define WIFI_SSID     "TU_SSID"
#define WIFI_PASS     "TU_PASSWORD"

// ─── Configuración Adafruit IO ───────────────────────
#define AIO_SERVER    "io.adafruit.com"
#define AIO_PORT      1883
#define AIO_USERNAME  "TU_USUARIO_AIO"
#define AIO_KEY       "TU_AIO_KEY"

// ─── Pin del LED ──────────────────────────────────────
#define LED_PIN 13  // Cambia al pin que uses

// ─── Objetos MQTT ─────────────────────────────────────
WiFiClient wifiClient;
Adafruit_MQTT_Client mqtt(&wifiClient, AIO_SERVER, AIO_PORT, AIO_USERNAME, AIO_KEY);

// Feed de suscripción (recibe comandos)
Adafruit_MQTT_Subscribe ledFeed = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/led-control");

// ─────────────────────────────────────────────────────
void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  // Conectar WiFi
  Serial.print("Conectando a WiFi...");
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n✅ WiFi conectado!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  // Registrar suscripción
  mqtt.subscribe(&ledFeed);
}

// ─────────────────────────────────────────────────────
void loop() {
  // Mantener conexión MQTT
  MQTT_connect();

  // Escuchar mensajes entrantes (timeout 200ms)
  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(200))) {

    if (subscription == &ledFeed) {
      String value = String((char *)ledFeed.lastread);
      Serial.print("Comando recibido: ");
      Serial.println(value);

      if (value == "ON" || value == "1") {
        digitalWrite(LED_PIN, HIGH);
        Serial.println("💡 LED encendido");
      } else if (value == "OFF" || value == "0") {
        digitalWrite(LED_PIN, LOW);
        Serial.println("🔴 LED apagado");
      }
    }
  }
}

// ─── Función de conexión/reconexión MQTT ─────────────
void MQTT_connect() {
  if (mqtt.connected()) return;

  Serial.print("Conectando a Adafruit IO...");
  int8_t ret;
  uint8_t retries = 5;

  while ((ret = mqtt.connect()) != 0) {
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("Reintentando en 5 segundos...");
    mqtt.disconnect();
    delay(5000);
    retries--;
    if (retries == 0) {
      Serial.println("❌ No se pudo conectar. Reiniciando...");
      while (1); // Fuerza watchdog reset
    }
  }
  Serial.println("\n✅ Conectado a Adafruit IO!");
}
```

### código para recibir

```cpp
// rellenar
```

## investigaciones individuales

rellenar en el mismo orden que los integrantes del grupo

[persona-01.md](./persona-01.md)
[persona-02.md](./persona-02.md)
[persona-03.md](./persona-03.md)

## bibliografía
