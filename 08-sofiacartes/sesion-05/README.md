# sesion-05

lunes 06 abril 2026

solemne 1

## Apuntes 

En Adafruit IO, te da la llave para colocar en el código en arduino

```cpp
#define IO_USERNAME  "sofiacartess"
#define IO_KEY       "sdfgh"
```

siempre hay que colocar esa línea, para que el arduino no olvide el adafruit IO

```cpp
io.run();
```

Es para ver lo que manda el otro arduino en adafruit 

```
io.feed();
```

Código que si funciona + el `config.h` es donde se guarda la clave de Adafruit IO y la clave de wifi

```cpp
// Adafruit IO Publish Example
//
// Adafruit invests time and resources providing this open source code.
// Please support Adafruit and open source hardware by purchasing
// products from Adafruit!
//
// Written by Todd Treece for Adafruit Industries
// Copyright (c) 2016 Adafruit Industries
// Licensed under the MIT license.
//
// All text above must be included in any redistribution.

// ejemplo para enviar / publish
// por montoyamoraga
// para disenoUDP
// basado en
// Adafruit IO Publish Example

// incluir archivo config.h
// hacer las modificaciones de este archivo
// NO subir a github
#include "config.h"

// esta variable entera
// sera un contador que aumenta
// durante el funcionamiento del software
int contador = 0;

// definir una variable que se llame nombreFeed
// que tenga un cierto valor
// mantener las doble comillas, cambiar grupoXX segun tu nombre de grupo
AdafruitIO_Feed *nombreFeed = io.feed("grupo01");

void setup()
{

  // prender la conexion serial
  // ojo con la velocidad de 115200 baud
  // cuando abras el monitor serial debes configurarlo
  // a este numero, porque el standard de fabrica es 9600 baud
  Serial.begin(115200);

  // estas lineas pausan el codigo
  // hasta que prendas el monitor serial
  // la lupita arriba a la derecha en Arduino IDE
  while (!Serial)
    ;

  // imprimir en consola
  Serial.print("conectando a Adafruit IO");

  // conectarse a io.adafruit.com
  io.connect();

  // esperar la conexion
  while (io.status() < AIO_CONNECTED)
  {
    // imprimir un punto cada medio segundo
    // mientras se conecta
    Serial.print(".");
    delay(500);
  }

  // demostrar que logramos conexion
  Serial.println();
  Serial.println(io.statusText());
}

void loop()
{

  // esta linea es necesaria
  // al principio de loop()
  // para mantener la conexion
  // y procesar datos que lleguen
  io.run();

  // enviar el contador a Adafruit IO
  // primero mostrar en monitor serial
  Serial.println("enviando -> " + String(contador));
  // despues enviar a la nube
  nombreFeed->save(contador);

  // incrementar el contador en 1
  contador = contador + 1;

  // Adafruit IO tiene una velocidad limitada
  // de escritura / publishing
  // usamos delay para pausar el codigo 3 segundos
  delay(3000);
}
```

este fue parte del trabajo en clases en grupo 

### Investigación Adafruit IO

Conceptos básicos de Adafruit IO: Fuentes de datos:

1. Adafruit IO: Feeds

Los feeds son el componente central del ecosistema Adafruit IO. Funcionan como el repositorio donde se almacenan y organizan tanto los datos enviados por los dispositivos como sus metadatos asociados.

Conceptos Fundamentales: Datos

Es la información técnica que se desea almacenar. Puede representar objetos físicos o variables lógicas

- Valores de sensores (temperatura, humedad, presión).
- Estados de actuadores (encendido/apagado).
- Variables de control (velocidad de motores).

2. Metadatos

Configuraciones que definen el comportamiento y contexto del feed

- **Privacidad:** Determina si los datos son públicos o privados.
- **Licencia:** Especifica los derechos de uso de los datos almacenados.
- **Descripción:** Información legible por personas para documentar el propósito del feed.

3. Modos de Implementación

La gestión de los feeds depende del método de interacción con la plataforma

´Interacción mediante API (MQTT / REST)´

Para usuarios que desarrollan su propio código, la gestión es manual y granular.

- **Regla:** Se debe crear un feed por cada origen de datos único.
- **Ejemplo:** Un proyecto con un sensor de temperatura y dos de humedad requiere la creación de **tres feeds** distintos.

´Uso con WipperSnapper (No-Code)´

Para usuarios que utilizan la plataforma de configuración sin código, la gestión es automatizada.

- **Funcionamiento:** Los feeds se crean automáticamente al momento de añadir un nuevo componente a la placa desde el panel de control de Adafruit IO.

*información sacada de: <https://learn.adafruit.com/adafruit-io-basics-dashboards>*

![instalaciónAdaIO](./imagenes/instalaciónAdaIO.jpg)
![proceso1](./imagenes/proceso1.gif)
