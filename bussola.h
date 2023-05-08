#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>

class Compass {
  public:
    Compass(uint8_t northLedPin, uint8_t northeastLedPin, uint8_t eastLedPin, uint8_t southeastLedPin,
            uint8_t southLedPin, uint8_t southwestLedPin, uint8_t westLedPin, uint8_t northwestLedPin)
            : northLedPin_(northLedPin), northeastLedPin_(northeastLedPin), eastLedPin_(eastLedPin),
              southeastLedPin_(southeastLedPin), southLedPin_(southLedPin), southwestLedPin_(southwestLedPin),
              westLedPin_(westLedPin), northwestLedPin_(northwestLedPin), mag_(Adafruit_HMC5883_Unified(199851)) {}

    void begin() {
      Serial.begin(9600);

      Serial.println("Inicializando o módulo HMC5883L");

      if (!mag_.begin()) {
        // Checando se não houve nenhum problema de conexão com o...
        //sensor HMC5883
        Serial.println("Ooops, sensor nao detectado ... Verifique as conexoes!");
        while (1);
      }

      // Mostra algumas informações básicas do sensor quando o código começa
      displaySensorDetails();
      pinMode(northLedPin_, OUTPUT);
      pinMode(northeastLedPin_, OUTPUT);
      pinMode(eastLedPin_, OUTPUT);
      pinMode(southeastLedPin_, OUTPUT);
      pinMode(southLedPin_, OUTPUT);
      pinMode(southwestLedPin_, OUTPUT);
      pinMode(westLedPin_, OUTPUT);
      pinMode(northwestLedPin_, OUTPUT);
    }

    void update() {
      sensors_event_t event;
      mag_.getEvent(&event);
      float headingDegrees = calculate_heading_degrees(event);
      Serial.print("Posicao em graus: "); Serial.println(headingDegrees);
      Serial.println(cardinal_point_calculation(headingDegrees));
      delay(500);
    }

  private:
    void displaySensorDetails() {
      sensor_t sensor;
      mag_.getSensor(&sensor);
      Serial.println("------------------------------------");
      Serial.print("Sensor: "); Serial.println(sensor.name);
      Serial.print("Versao do driver: "); Serial.println(sensor.version);
      Serial.print("ID do sensor: "); Serial.println(sensor.sensor_id);
      Serial.print("Valor maximo: "); Serial.print(sensor.max_value);
      Serial.print("Valor Minimo: "); Serial.print(sensor.min_value);
      Serial.print("Resolucao: "); Serial.print(sensor.resolution);
      Serial.println("------------------------------------");
      Serial.println("");
      delay(500);
    }
      heading += declinationAngle;

  // Converte radianos para graus
  float headingDegrees = heading * 180 / PI;

  // Ajuste para que o grau esteja entre 0 e 360
  if (headingDegrees < 0) {
    headingDegrees += 360;
  }

  return headingDegrees;
}

String cardinal_point_calculation(float headingDegrees) {
  String cardinalPoints[] = {"N", "NE", "E", "SE", "S", "SW", "W", "NW", "N"};

  // O número de elementos no array
  int numElements = sizeof(cardinalPoints) / sizeof(cardinalPoints[0]);

  // A largura de cada setor em graus
  float sectorWidth = 360.0 / numElements;

  // Encontre a posição do setor que contém o ângulo de referência
  int sectorPos = floor((headingDegrees + (sectorWidth / 2)) / sectorWidth);

  return cardinalPoints[sectorPos];
}

uint8_t northLedPin_;
uint8_t northeastLedPin_;
uint8_t eastLedPin_;
uint8_t southeastLedPin_;
uint8_t southLedPin_;
uint8_t southwestLedPin_;
uint8_t westLedPin_;
uint8_t northwestLedPin_;

Adafruit_HMC5883_Unified mag_;
};
