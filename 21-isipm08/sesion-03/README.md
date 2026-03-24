# sesion-03

# lunes 23 marzo 2026


## **Raspberry Pi**
+ Placa microcontroladora de alto rendimiento
+ Seguridad y versatilidad 
+ Computadora (no con mouse ni teclado)
+ Desarrollo de Arduino
+ C/C++ (el que usaremos)
+ int main()
+ Microcontroladores (RP2040, RP2050)
+ MODELOS
  - Raspberry Pi 5
  - Raspberry Pi 500+
  - Raspberry Pi Compute Module 5
  - Raspberry Pi Zero 2 W

{
    stdio_init_all();

    // Initialise the Wi-Fi chip
    if (cyw43_arch_init()) {
        printf("Wi-Fi init failed\n");
        return -1;
    }

    // Example to turn on the Pico W LED
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);

    while (true) {
        printf("Hello, world!\n");
        sleep_ms(1000);
    }

---

## **Microcontroladores y microcomputadoes**
+ BeagleBoard
+ Bela Platform
+ Electro-Smith
---

## **Mainframe**
+ Computadora alto rendimiento
+ Gran capacidad memoria y rendimiento
+ Gestiona transacciones en tiempo real
---

## **Atari**
---

## **Commodore**
+ Empresa de electrónica y hardware
+ Revolución ordenadores personales
  
---

## **Spectrum Zx**
+ Microordenador doméstico
+ Clave para la introducción masiva de la informática
+ Diseño compacto, teclado goma
---

**Monty Pyton**
+ Spam
+ Lenguaje Pyton

Stdio (Standar) 
Sdk: clip de desarrollo de software 
Crash course
Mermaid (diagrama de flujo)
S1: ARDUINO ENVÍA - RASPBERRY PI RECIBE 
