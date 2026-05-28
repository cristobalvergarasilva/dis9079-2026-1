# investigaciones individuales

Débora Soto/ DebSkar

## Sensor

### ¿Qué es un sensor?

Un sensor es un dispositivo diseñado para detectar estímulos, magnitudes físicas o variaciones químicas en su entorno inmediato, como luz, temperatura, presión, distancia o presencia y transformar esa información analógica en una señal eléctrica cuantificable, generalmente voltaje o corriente, que puede ser leída y procesada por un sistema electrónico o microcontrolador.

### Sensor Chip MPR121

#### Sensor de proximidad y tacto capacitivo por comunicación I2C de 12 canales.

¿Cómo funciona?

Este sensor funciona midiendo las variaciones en la capacitancia eléctrica,la capacidad de un cuerpo para almacenar una carga eléctrica. 

El chip aplica una pequeña corriente a un material conductor conectado a él,que actúa como un electrodo,creando un campo electrostático a su alrededor.Cuando un cuerpo con propiedades conductivas y dieléctricas,como la piel humana, que está compuesta mayoritariamente por agua,se aproxima o toca este electrodo, interfiere con el campo electrostático, absorbiendo parte de la carga y alterando la capacitancia del circuito. 
El chip MPR121 detecta este micro-cambio físico en tiempo real, lo filtra digitalmente y lo envía como un dato numérico preciso a un microcontrolador mediante el protocolo de comunicación I^2C. Lo interesante es que su alta sensibilidad permite registrar variaciones por proximidad (antes del contacto físico real) si el electrodo es lo suficientemente grande.



## Actuador

## Bibliografía
