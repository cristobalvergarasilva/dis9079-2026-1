# sesion-04

HiveMQ: Plataforma y broker MQTT diseñada para la mensajería IoT (Internet de las Cosas), facilita la conexión entre dispositivos y la nube en tiempo real.

Tiger VNC:  dar soporte de manera remota o administrar servidores a los que no tienes un acceso físico directo, puede servir para tener escritorio gráfico para ver la Raspberry Pi.

`sudo`: su (super user) `do` (hacer) + `rm` (remove) `rf` (recursivamente, force) = eliminar todo de manera recursiva a la fuerza.

## Mosquitto

Para enviar se debe hacer con un topic en específico y la persona que recibe tiene que tener ese mismo topic.

Puerto mas usado: 1883

ID ≠ Username

ID: Número o codigo único que te asigna el sist. automáticamente.

Username: Nombre público que uno mismo elige.

### Comandos Mosquitto

`-c` : correr

`-v` : Mosquitto piensa en voz alta

El resto de comandos se pueden encontrar en: <https://mosquitto.org/man/mosquitto_sub-1.html>

----

Cambiar línea 52 a arduino07

Se intento enviar y recibir mensajes por medio del arduino con el protocolo mqtt lo que fracasó por lo que hay que cambiar de protocolo al UDP (user datagram protocol)


Protocolo UDP: Útil para enviar mensajes, pero no le importa si éstos llegan o no, por lo que no es bueno para enviar audio ya que se necesita algo constante y preciso. 

Formalmente el protocolo UDP es: un protocolo de comunicación que se utiliza en Internet para transmisiones sujetas a limitaciones temporales, como la reproducción de vídeo o las búsquedas en DNS. Acelera las comunicaciones al no establecer formalmente una conexión antes de transferir los datos. Esto permite que los datos se transfieran muy rápido, pero también puede hacer que los paquetes se pierdan en tránsito.











lunes 30 marzo 2026
