// ============================================================
// RECEPTOR - Adafruit IO → Altavoz 8Ω (via transistor) + LED Matrix
// Arduino R4 WiFi
//
// CONEXIÓN FÍSICA DEL ALTAVOZ:
//   Pin 9  → Resistencia 1kΩ → Base del transistor (2N2222 o BC547)
//   Colector del transistor  → Pin (-) del altavoz
//   Pin (+) del altavoz      → 5V
//   Emisor del transistor    → GND
//   GND Arduino              → GND (común con emisor)
//
// IMPORTANTE: Pin 9 es PWM en el R4 WiFi, necesario para
// controlar la amplitud real del tono con analogWrite()
// ============================================================

#include "config.h"              // Credenciales WiFi y Adafruit IO
#include "Arduino_LED_Matrix.h"  // Librería de la matriz LED integrada del R4

// --- MATRIZ LED ---
ArduinoLEDMatrix matrix;

// --- PIN DEL ALTAVOZ ---
// Debe ser un pin PWM para poder controlar el volumen real
// En el R4 WiFi los pines PWM son: 3, 5, 6, 9, 10, 11
const int PIN_ALTAVOZ = 9;

// Frecuencia del tono en Hz
// 440 Hz = nota La (referencia musical estándar)
// Puedes cambiar esto: 261=Do, 329=Mi, 392=Sol
const int FRECUENCIA_TONO = 440;

// --- FEED DE ADAFRUIT IO ---
AdafruitIO_Feed *feedVolumen = io.feed("paredesvania-volumen");

// --- BUFFER DE LA MATRIZ LED (8 filas × 12 columnas) ---
uint8_t frameMatrix[8][12];

// ============================================================
// FUNCIÓN: reproducirConVolumen
// Controla el volumen REAL del altavoz usando PWM
// En lugar de solo cambiar la duración, cambia la amplitud
// de la señal enviada al transistor
// ============================================================
void reproducirConVolumen(int volumen) {

  if (volumen == 0) {
    // Volumen 0 → apagar completamente el altavoz
    // analogWrite(pin, 0) pone el pin en LOW constante
    analogWrite(PIN_ALTAVOZ, 0);
    return;
  }

  // Convertir volumen (1-100) a ciclo de trabajo PWM (1-128)
  // analogWrite acepta valores 0-255
  // Limitamos a 128 (50%) para proteger el altavoz de 0.5W
  // con 5V y 8Ω la corriente máxima es V/R = 5/8 = 0.625A → riesgoso
  // al 50% PWM reducimos la potencia efectiva a niveles seguros
  int pwmAmplitud = map(volumen, 1, 100, 5, 128);

  // Duración del tono proporcional al volumen
  // tono más fuerte → suena más tiempo
  int duracion = map(volumen, 1, 100, 80, 400);

  // --- GENERAR EL TONO MANUALMENTE CON PWM ---
  // tone() no es compatible con analogWrite() al mismo tiempo
  // así que generamos el tono a mano con un bucle:
  // alternamos entre la amplitud PWM y 0 a la frecuencia deseada

  unsigned long tiempoInicio = millis();
  // Periodo de medio ciclo en microsegundos
  // Para 440 Hz: periodo completo = 1/440 = 2272 µs → medio ciclo = 1136 µs
  unsigned long semiPeriodo = 1000000UL / (FRECUENCIA_TONO * 2);

  // Repetir el ciclo durante toda la duración del tono
  while (millis() - tiempoInicio < (unsigned long)duracion) {
    analogWrite(PIN_ALTAVOZ, pwmAmplitud); // fase positiva
    delayMicroseconds(semiPeriodo);
    analogWrite(PIN_ALTAVOZ, 0);           // fase negativa (silencio)
    delayMicroseconds(semiPeriodo);
  }

  // Silencio breve entre tonos para que se escuche como pulso
  analogWrite(PIN_ALTAVOZ, 0);
  delay(60);
}

// ============================================================
// FUNCIÓN: dibujarBarraVolumen
// Enciende filas de la matriz LED de abajo hacia arriba
// proporcional al volumen recibido (0-100)
// ============================================================
void dibujarBarraVolumen(int volumen) {

  // Limpiar toda la matriz (apagar todos los LEDs)
  memset(frameMatrix, 0, sizeof(frameMatrix));

  if (volumen == 0) {
    // Volumen 0 → todo apagado
    matrix.renderBitmap(frameMatrix, 8, 12);
    return;
  }

  // Calcular cuántas filas encender (de 1 a 8)
  // Fila 7 = abajo, Fila 0 = arriba
  int filasEncendidas = map(volumen, 1, 100, 1, 8);

  // Encender filas desde abajo (fila 7) hacia arriba
  for (int fila = 7; fila >= (8 - filasEncendidas); fila--) {
    for (int col = 0; col < 12; col++) {
      frameMatrix[fila][col] = 1;
    }
  }

  // Actualizar la pantalla LED
  matrix.renderBitmap(frameMatrix, 8, 12);
}

// ============================================================
void setup() {

  Serial.begin(115200);
  while (!Serial);

  // Inicializar la matriz LED integrada
  matrix.begin();

  // Animación de inicio: encender todo brevemente
  // para verificar que la pantalla funciona
  memset(frameMatrix, 1, sizeof(frameMatrix));
  matrix.renderBitmap(frameMatrix, 8, 12);
  delay(500);
  memset(frameMatrix, 0, sizeof(frameMatrix));
  matrix.renderBitmap(frameMatrix, 8, 12);

  // Configurar pin del altavoz como salida
  pinMode(PIN_ALTAVOZ, OUTPUT);
  analogWrite(PIN_ALTAVOZ, 0); // Asegurar silencio al arrancar

  // Conectar a Adafruit IO
  Serial.print("Conectando a Adafruit IO...");
  io.connect();

  while (io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println();
  Serial.println(io.statusText());

  // Suscribirse al feed: cuando llegue un dato nuevo
  // se llamará automáticamente manejarVolumen()
  feedVolumen->onMessage(manejarVolumen);

  // Pedir el último valor del feed para no arrancar en blanco
  feedVolumen->get();

  Serial.println("Listo. Escuchando feed de volumen...");
}

// ============================================================
void loop() {
  // Mantener conexión activa y procesar mensajes entrantes
  // El callback manejarVolumen() se dispara automáticamente aquí
  io.run();
}

// ============================================================
// CALLBACK - Se ejecuta al recibir un dato nuevo del feed
// ============================================================
void manejarVolumen(AdafruitIO_Data *dato) {

  // Leer el valor enviado por el emisor (0 a 100)
  int volumen = dato->toInt();

  // Asegurar que esté dentro del rango válido
  volumen = constrain(volumen, 0, 100);

  Serial.print("Volumen recibido: ");
  Serial.print(volumen);
  Serial.println("%");

  // Actualizar la barra visual en la matriz LED
  dibujarBarraVolumen(volumen);

  // Reproducir el tono con el volumen real controlado por PWM
  reproducirConVolumen(volumen);
}