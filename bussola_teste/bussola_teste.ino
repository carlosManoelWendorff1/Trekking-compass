#include "Compass.h"

Compass compass; // criando uma instância da classe Compass com os pinos dos LEDs

void setup() {
  compass.begin_compass();
}

void loop() {
  compass.update_compass();
}
