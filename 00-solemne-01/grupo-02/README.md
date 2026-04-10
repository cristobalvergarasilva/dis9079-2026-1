# friendshipisfriend-02

## integrantes

* Magdalena Balart
* Jesus Miranda
* Carla Nuñez

## descripción del proyecto

friendshipisfriend nace desde una idea muy especial, usar la tecnologia no solo para conectar maquinas, sino para conectar personas. queriamos demostrar que el internet de las cosas puede tener sentimientos, y para lograrlo nuestro objetivo fue que con un clic se pudiera mandar un "abrazo digital". todo esto cobra vida al combinar el Arduino UNO R4 Wifi y Adafruit IO que nos sirvio como puente de comunicacion!!.

configuramos un rinconcito en la web adafruit llamado dashboard lo que vendria siendo la cara visible de esto. usamos un feed, que funciona como una cajita de mensajes donde guardamos la señal de activacion. para que nuestro arduino supiera exactamente donde conectarse sin exponer todo, utilizamos el archivo config.h que nos entregaron en clases. en este archivo guardamos nuestro wifi y key de adafruit, permitiendo que el proyecto esté seguro y organizado.

lo más bonito es lo que pasa cuando el arduino recibe la señal desde esta nube, el proceso de utilizar los codigos que fuimos recolectando mediante tutoriales, los que fueron entregados por aaron, por busqueda propia e importando librerias necesarias de adafruit fueron parte fundamental para que la comunicaion resultara. fue emocionante ver como todo cobraba sentido a medida que la programacion era detectada desde adafruit al arduino. en este proceso su LED se enciende y en la pantalla aparece el mensaje "amistad es amigo", momento de felicidad que dura 5 segundos, despues de este tiempo el led se apaga y el sistema regala un ultimo mensaje "te extraño amigo". es nuestra forma de decir que aunque la luz se apague, el cariño permanece.:)

en conclusion friendshipisfriend nos enseñó que todo esto tambien es una forma de expresion. logramos que herramientas muy desconocidas para nosotros como el protocolo mqtt y el procesador de arduino trabajen juntos para enviar un mensaje de afecto a traves de codigos. este proyecto es la prueba de que con un poco de programación, de imaginación podemos acortar cualquier distancia y recordarles a nuestros amigos que siempre estamos ahí para ellos.
## materiales usados en solemne-01

## código usado con Adafruit IO

### código para enviar

```cpp
#include "config.h"

const int LED_PIN = LED_BUILTIN;   // si usas un LED externo, cambia este pin
const unsigned long INTERVALO = 5000;  // 5 segundos

AdafruitIO_Feed *mensajeFeed = io.feed("mensaje");

bool estadoLed = false;  // empieza apagado
unsigned long ultimoCambio = 0;

void setup() {
  Serial.begin(115200);
  while (!Serial);

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  Serial.println("Conectando a Adafruit IO...");
  io.connect();

  while (io.status() < AIO_CONNECTED) {
    Serial.println(io.statusText());
    delay(1000);
  }

  Serial.println("Adafruit IO connected.");

  // mandar estado inicial
  if (mensajeFeed->save("te extraño amigo")) {
    Serial.println("Mensaje inicial enviado: te extraño amigo");
  } else {
    Serial.println("Error al enviar mensaje inicial");
  }

  ultimoCambio = millis();
}

void loop() {
  io.run();

  unsigned long ahora = millis();

  if (ahora - ultimoCambio >= INTERVALO) {
    ultimoCambio = ahora;

    // cambiar estado del LED
    estadoLed = !estadoLed;
    digitalWrite(LED_PIN, estadoLed ? HIGH : LOW);

    // enviar mensaje segun estado
    if (estadoLed) {
      if (mensajeFeed->save("amistad es amigo")) {
        Serial.println("LED encendido -> amistad es amigo");
      } else {
        Serial.println("Error al enviar: amistad es amigo");
      }
    } else {
      if (mensajeFeed->save("te extraño amigo")) {
        Serial.println("LED apagado -> te extraño amigo");
      } else {
        Serial.println("Error al enviar: te extraño amigo");
      }
    }
  }
}
```

### código para recibir

```cpp
#include "config.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C   // este depende de la pantalla parece

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//feed
AdafruitIO_Feed *mensajeFeed = io.feed("mensaje");

// funcion que escribe texto en la pantalla
void mostrarMensaje(String texto) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Mensaje:");
  display.println();
  display.println(texto);
  display.display();
}

// callback: se ejecuta cuando llega un mensaje nuevo
void handleMessage(AdafruitIO_Data *data) {
  String texto = data->toString();

  Serial.print("recibido <- ");
  Serial.println(texto);

  mostrarMensaje(texto);
}

void setup() {
  Serial.begin(115200);
  while (!Serial);

  Wire.begin();

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println("No se pudo iniciar la OLED");
    while (true);
  }

  display.clearDisplay();
  display.display();

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Conectando a");
  display.println("Adafruit IO...");
  display.display();

  // este para conectar a adafruit se enoja
  io.connect();

  // suscribirse al feed
  mensajeFeed->onMessage(handleMessage);

  while (io.status() < AIO_CONNECTED) {
    Serial.println(io.statusText());
    delay(1000);
  }

  Serial.println("Adafruit IO connected.");

  // pedir el valor actual del feed al conectarse
  mensajeFeed->get();
}

void loop() {
  io.run();
}
```

## investigaciones individuales

rellenar en el mismo orden que los integrantes del grupo

[persona-01.md](./persona-01.md) 
[persona-02.md](./persona-02.md)
[persona-03.md](./persona-03.md)

## bibliografía

**Arduino. UNO R4 WiFi Cheat Sheet / User Manual.** https://docs.arduino.cc/tutorials/uno-r4-wifi/cheat-sheet/?utm_source=chatgpt.com   
**Adafruit. Adafruit IO Basics: Feeds.** https://learn.adafruit.com/adafruit-io-basics-feeds?view=all&utm_source=chatgpt.com   
**Adafruit GitHub. Adafruit_SSD1306.** https://github.com/adafruit/adafruit_ssd1306?utm_source=chatgpt.com   
**Adafruit. Animated Flying Toaster OLED Jewelry – Code.** https://learn.adafruit.com/animated-flying-toaster-oled-jewelry/code?utm_source=chatgpt.com     
**Arduino: Pantalla Oled de 0.96"** Mostrar Datos Analógicos https://www.youtube.com/watch?v=GjI0_4ed4JE   
**Arduino oled mostrar datos.txt**  https://drive.google.com/file/d/1JUANNHpeVcxEBgpdv9FMDBNIgAdSIzLL/view   
**Sensor pulso cardiaco y arduino** https://m.youtube.com/watch?v=Pu6Ks_O12S8    
**Arduino Documentation. Using Variables in Sketches.** https://docs.arduino.cc/learn/programming/variables/?utm_source=chatgpt.com   
**Microsoft Learn. Declarations and definitions (C++).** https://learn.microsoft.com/en-us/cpp/cpp/declarations-and-definitions-cpp?view=msvc-170&utm_source=chatgpt.com   
**Variables en Arduino: Qué Son y Cómo Usarlas Correctamente.** youtube.com/watch?v=GajOQXb1lYw&utm_source=chatgpt.com    
**Arduino Tutorial 4: Understanding Arduino Variables.** https://www.youtube.com/watch?v=nPOKOi1jIK0   
