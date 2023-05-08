#include "Compass.h"

Compass compass(2, 3, 4, 5, 6, 7, 8, 9); // criando uma instância da classe Compass com os pinos dos LEDs

void setup() {
  compass.begin();
}

void loop() {
  compass.update();
}