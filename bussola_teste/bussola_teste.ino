#include "Compass.h"

Compass compass; // criando uma instância da classe Compass com os pinos dos LEDs

void setup() {
  compass.begin_compass();
}

void loop() {
  //compass.update_compass();

  Serial.println(compass.calculate_heading_degrees());
  Serial.println(compass.cardinal_point_calculation(compass.calculate_heading_degrees()));
}
