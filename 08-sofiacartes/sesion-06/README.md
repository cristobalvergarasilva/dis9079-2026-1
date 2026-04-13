# sesion-06

lunes 13 abril 2026

## Apuntes

- resistencia
- consensador: capacidad electrica
- capacitor
- lo que varia es la capacitancia
- capacitive touch: <https://docs.arduino.cc/tutorials/uno-r4-wifi/touch/>
- librería a utilizar: `Arduino_CapacitiveTouch` library documentation
- ~
- `CapacitiveTouch(uint8_t pin)`:
- `bool begin()`:
- `int read()`:
- `bool isTouched()`:
- `void setThreshold(int threshold)`:
- `int getThreshold()`:
- D0 -> digital 0
  
```cpp
#include "Arduino_CapacitiveTouch.h"

CapacitiveTouch touchButton = CapacitiveTouch(D0);

void setup() {
  Serial.begin(9600);

  if(touchButton.begin()){
    Serial.println("Capacitive touch sensor initialized.");
  } else {
    Serial.println("Failed to initialize capacitive touch sensor. Please use a supported pin.");
    while(true);
  }

  touchButton.setThreshold(2000);
}

void loop() {
  int sensorValue = touchButton.read();
  Serial.print("Raw value: ");
  Serial.println(sensorValue);

  if (touchButton.isTouched()) {
    Serial.println("Button touched!");
  }

  delay(100);
}
```
