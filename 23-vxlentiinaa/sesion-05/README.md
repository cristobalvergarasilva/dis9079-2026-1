# sesion-05

lunes 06 abril 2026

solemne 1

---

## Investigación Adafruit IO

`¿Qué es Adafruit IO?`

- Adafruit IO es una plataforma en la nube para Internet de las Cosas (IoT) que permite conectar dispositivos (como Arduino, ESP8266, Raspberry Pi, etc.) a Internet para enviar, recibir y visualizar datos.
  - <https://learn.adafruit.com/welcome-to-adafruit-io>

`¿Qué hace la biblioteca Adafruit IO?`
 
 Permite:

- Enviar datos (sensores, valores, etc.) a la nube
- Recibir datos (por ejemplo, para controlar LEDs o motores)
- Conectar tu dispositivo a Internet fácilmente
- Mantener comunicación en tiempo real con feeds (canales de datos)

*Esta librería simplifica el uso, como MQTT*

`¿Cómo funciona?`

- Tu dispositivo se conecta a WiFi (arduino)
- Usa la librería Adafruit IO para conectarse al servidor
- Envía o recibe datos a través de feeds
- Puedes ver esos datos en gráficas, etc

<https://learn.adafruit.com/adafruit-io-basics-digital-input/getting-started-with-adafruit-io>

**Instalé la librería Adafruit IO en Arduino IDE y usé de ejemplo `adafruitio_00_publish**

<https://io.adafruit.com/welcome>

- el ejemplo Publish, es un ejemplo de código que sirve para enviar datos desde el microcontrolador hacia la plataforma Adafruit IO
  - es para publicar (mandar) información a internet.

`¿Para qué se usa exactamente?`

Sirve para:

- Enviar datos de sensores
  - Ej: temperatura, luz, humedad.
- Mandar estados o eventos
  - Ej: “botón presionado”, “LED encendido”.
- Visualizar datos en dashboards

En Adafruit IO puedes ver gráficos en tiempo real.

`¿Qué hace el código?`

El ejemplo “Publish” hace:

1. Se conecta a tu WiFi
2. Se conecta a Adafruit IO con tu usuario y contraseña
3. Envía datos a un “feed” (como una variable online)
4. Repite el envío cada cierto tiempo

Ya sabiendo esto, descargué la librería. 
 > fui a `File` luego a `Examples` --> abrí `Adafruit IO Arduino` --> abrí el primer ejemplo `adafrutio_00_publish`

Y cambié 

```cpp
#define IO_USERNAME "your_username"
#define IO_KEY "your_key"
```
por

```cpp
#define IO_USERNAME "arduino01"
#define IO_KEY "dis9079"
```

esto igual lo cambié

```cpp
#define WIFI_SSID "your_ssid"
#define WIFI_PASS "your_pass"
```

por mi wifi

```cpp
#define WIFI_SSID "Ruz Pizarro 5G"
#define WIFI_PASS "agosto2019"
```

Luego probé el ejemplo para ver si en el monitor serial salía el mensaje de **"Connecting to Adafruit IO"** , pero solo me aparecía signos de interrogación

Podría haber sido por el baud, que en el código estaba a 115200 y en el monitor seriañ estaba a 9600

Lo cambié y después solo salían puntitos, no el mensaje de que ya estaba conectado
