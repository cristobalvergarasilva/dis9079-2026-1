// prototipo processing

import oscP5.*;
import netP5.*;

color apagado;
color prendido;

int columnas = 12;
int filas = 8;

int[][] grilla = new int[12][8];

// OSC
OscP5 oscP5;
NetAddress destino;


void setup() {
  size(1200, 800);

  apagado = color(0, 0, 0);
  prendido = color(255, 0, 0);

  // partir todo apagado
  for (int x = 0; x < columnas; x++) {
    for (int y = 0; y < filas; y++) {
      grilla[x][y] = 0;
    }
  }
  //noStroke();
  textAlign(CENTER, CENTER);

  // OSC setup
  // puerto local (puede ser cualquiera)
  oscP5 = new OscP5(this, 12000);
  // IP del otro computador
  destino = new NetAddress("172.28.15.29", 8000);
}

void draw() {
  // fondo negro

  // recorrer cada columna
  // recorrer cada fila
  // vamos a revisar la grilla
  // vamos a pintar segun eso

  for (int x = 0; x < columnas; x++) {
    for (int y = 0; y < filas; y++) {
      if (grilla[x][y] == 0) {
        fill(apagado);
      } else {
        fill(prendido);
      }
      rect(
        x*100,
        y*100,
        100,
        100
        );
    }
  }
}

void mousePressed() {
  int x = mouseX / 100;
  int y = mouseY / 100;

  // evitar errores fuera de la grilla
  if (x >= 0 && x < columnas && y >= 0 && y < filas) {
    // toggle: 1 -> 0, 0 -> 1
    grilla[x][y] = 1 - grilla[x][y];

    enviarOSC(x, y, grilla[x][y]);
  }
}

void enviarOSC(int x, int y, int estado) {
  OscMessage msg = new OscMessage("/grid");

  msg.add(x);
  msg.add(y);
  msg.add(estado);

  oscP5.send(msg, destino);

  println("Enviado OSC:", x, y, estado);
}
