#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>

class Compass
{
public:
  Compass() : mag_(Adafruit_HMC5883_Unified(199851)) {}

  void begin_compass()
  {
    Serial.begin(9600);

    Serial.println("Inicializando o módulo HMC5883L");

    if (!mag_.begin())
    {
      // Checando se não houve nenhum problema de conexão com o...
      // sensor HMC5883
      Serial.println("Ooops, sensor nao detectado ... Verifique as conexoes!");
      while (1)
        ;
    }

    // Mostra algumas informações básicas do sensor quando o código começa
    displaySensorDetails();
  }

  void update_compass()
  {
    sensors_event_t event;
    mag_.getEvent(&event);
    float headingDegrees = calculate_heading_degrees_from_event(event);
    Serial.print("Posicao em graus: ");
    Serial.print(headingDegrees);
    Serial.print(" ---->  ");
    Serial.println(cardinal_point_calculation(headingDegrees));
    delay(100);
  }
  float calculate_heading_degrees()
  {
    sensors_event_t event;
    mag_.getEvent(&event);
    float heading = atan2(event.magnetic.y, event.magnetic.x);
    float declinationAngle = 0.22; // Ângulo de declinação magnética para São Paulo
    heading += declinationAngle;

    // Converte radianos para graus
    float headingDegrees = heading * 180 / PI;

    // Ajuste para que o grau esteja entre 0 e 360
    if (headingDegrees < 0)
    {
      headingDegrees += 360;
    }

    return headingDegrees;
  }

  String cardinal_point_calculation(float headingDegrees)
  {
    // array de posições cardeais

    String cardinalPoints[] = {"N", "NE", "E", "SE", "S", "SW", "W", "NW"};

    // verifica a posição em graus do ponto cardeal

    if (headingDegrees >= 0 && headingDegrees < 22.5)
    {
      return cardinalPoints[0];
    }
    else if (headingDegrees >= 22.5 && headingDegrees < 67.5)
    {
      return cardinalPoints[1];
    }
    else if (headingDegrees >= 67.5 && headingDegrees < 112.5)
    {
      return cardinalPoints[2];
    }
    else if (headingDegrees >= 112.5 && headingDegrees < 157.5)
    {
      return cardinalPoints[3];
    }
    else if (headingDegrees >= 157.5 && headingDegrees < 202.5)
    {
      return cardinalPoints[4];
    }
    else if (headingDegrees >= 202.5 && headingDegrees < 247.5)
    {
      return cardinalPoints[5];
    }
    else if (headingDegrees >= 247.5 && headingDegrees < 292.5)
    {
      return cardinalPoints[6];
    }
    else if (headingDegrees >= 292.5 && headingDegrees < 337.5)
    {
      return cardinalPoints[7];
    }
    else if (headingDegrees >= 337.5 && headingDegrees < 360.0)
    {
      return cardinalPoints[0];
    }
  }

private:
  void displaySensorDetails()
  {
    sensor_t sensor;
    mag_.getSensor(&sensor);
    Serial.println("------------------------------------");
    Serial.print("Sensor: ");
    Serial.println(sensor.name);
    Serial.print("Versao do driver: ");
    Serial.println(sensor.version);
    Serial.print("ID do sensor: ");
    Serial.println(sensor.sensor_id);
    Serial.print("Valor maximo: ");
    Serial.print(sensor.max_value);
    Serial.print("Valor Minimo: ");
    Serial.print(sensor.min_value);
    Serial.print("Resolucao: ");
    Serial.print(sensor.resolution);
    Serial.println("------------------------------------");
    Serial.println("");
    delay(500);
  }
  float calculate_heading_degrees_from_event(sensors_event_t event)
  {
    float heading = atan2(event.magnetic.y, event.magnetic.x);
    float declinationAngle = 0.22; // Ângulo de declinação magnética para São Paulo
    heading += declinationAngle;

    // Converte radianos para graus
    float headingDegrees = heading * 180 / PI;

    // Ajuste para que o grau esteja entre 0 e 360
    if (headingDegrees < 0)
    {
      headingDegrees += 360;
    }

    return headingDegrees;
  }
  Adafruit_HMC5883_Unified mag_;
};
