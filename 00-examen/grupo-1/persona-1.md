# persona-1

magdalenabalart

Una API, *Application Programming Interface*, es un conjunto de reglas o protocolos que permite que distintas aplicaciones de software se comuniquen entre sí. Funciona como un puente entre programas, ya que permite intercambiar datos, características y funcionalidades sin que una aplicación tenga que conocer cómo está construida la otra por dentro.

> Las API simplifican y aceleran el desarrollo de aplicaciones y software, ya que permiten a los desarrolladores integrar datos, servicios y funcionalidades de otras aplicaciones, en lugar de desarrollarlos desde cero. Las API ofrecen a los propietarios de aplicaciones una forma sencilla y segura de poner los datos y las funciones de la aplicación a disposición de los consumidores internos y externos.

Un ejemplo es la aplicación del clima, la app no necesariamente crea todos los datos meteorológicos por sí sola. Lo que hace es conectarse a otro sistema que tiene esa información y a través de una API, recibe los datos para mostrarlos de una forma más simple. 

El funcionamiento de una API se basa en una solicitud y una respuesta. Una aplicación, que sería el cliente, le pide algo a otro sistema, que sería el servidor. Luego, ese servidor procesa la solicitud y responde con la información necesaria. Para el usuario esto ocurre de manera invisible porque solo ve el resultado final en la pantalla, pero por detrás hay varios sistemas conectándose entre sí. 

Existen diversos tipos de APIs y no todas funcionan de la misma manera. Aunque todas tienen como objetivo permitir la comunicación entre sistemas, cada una utiliza distintos métodos, formatos o reglas para intercambiar información. 

API SOAP: funciona de una manera más ordenada y rígida. Se podría comparar con llenar un formulario muy específico: la información debe ir en cierto formato y siguiendo reglas claras. Por eso puede ser más segura y controlada, pero también menos flexible porque no permite tantas variaciones en la forma de enviar los datos. 

APIs RPC: funcionan como cuando una aplicación le pide a otra que haga una tarea concreta. Por ejemplo, sería como decirle a otro sistema: “calcula esto”, “guarda esta información” o “devuélveme este resultado”. El servidor realiza esa acción y luego entrega una respuesta. 

APIs WebSocket: sirven para mantener una comunicación constante entre dos sistemas. A diferencia de otras APIs, donde una aplicación pregunta y espera una respuesta, WebSocket permite que ambas partes se envíen información en tiempo real. Esto es útil, por ejemplo, en chats, videojuegos en línea, notificaciones o aplicaciones donde los datos deben actualizarse al instante. 

APIs REST: son de las más utilizadas actualmente en páginas web y aplicaciones. Funcionan de una manera más simple y flexible: una aplicación solicita información o pide realizar una acción, y el servidor responde. Por ejemplo, una app puede pedir mostrar productos, actualizar un perfil o cargar publicaciones. Por su facilidad de uso, REST es muy común en servicios digitales actuales. 


Desde el código, una API se utiliza realizando una solicitud a una dirección específica, llamada endpoint. Esta solicitud puede incluir datos o parámetros, como una ciudad, una fecha o un usuario. Luego, la API procesa esa solicitud y devuelve una respuesta, normalmente en un formato ordenado como JSON (JavaScript Object Notation, es un formato para ordenar datos). En las APIs, JSON es muy usado porque permite que el servidor devuelva información de forma ordenada y que el código pueda leerla fácilmente. Después, la aplicación puede tomar esos datos y mostrarlos de una forma más visual para el usuario. 

1. Escribes la dirección de la API.
2. Le agregas lo que quieres pedir, por ejemplo: ciudad=Santiago.
3. El código manda esa solicitud.
4. La API responde con datos.
5. Tu código lee esos datos.
6. Después decides qué hacer con ellos: mostrarlos, guardarlos, usarlos en una pantalla, etc.

En C++, JSON se entiende como un texto ordenado con datos, pero C++ no lo lee automáticamente como si fuera una variable normal. Primero llega como texto y después el código debe interpretarlo. 



