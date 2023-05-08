#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>

// Atribuindo um ID para o sensor
Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(199851);


int ledSul = 2;
int ledSudoeste = 3;
int ledOeste = 4;
int ledNoroeste = 5;
int ledNorte = 6;
int ledNordeste = 7;
int ledLeste = 8;
int ledSudeste = 9;


void displaySensorDetails(void)

{
  sensor_t sensor;
  mag.getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.print ("Sensor: "); Serial.println(sensor.name);
  Serial.print ("Versao do driver: "); Serial.println(sensor.version);
  Serial.print ("ID do sensor: "); Serial.println(sensor.sensor_id);
  Serial.print ("Valor maximo: "); Serial.print(sensor.max_value);
  Serial.print ("Valor Minimo: "); Serial.print(sensor.min_value);
  Serial.print ("Resolucao: "); Serial.print(sensor.resolution);
  Serial.println("------------------------------------");
  Serial.println("");
  delay(500);
}

void compass_calibration(){

  if(!mag.begin())
  {
    // Checando se não houve nenhum problema de conexão com o...
    //sensor HMC5883
    Serial.println("Ooops, sensor nao detectado ... Verifique as conexoes!");
    while(1);
  }

  // Mostra algumas informações básicas do sensor quando o código começa
  displaySensorDetails();
}
void setup_bussola()
{
  Serial.begin(9600);
 
  Serial.println("Inicializando o módulo HMC5883L");

  configura_bussola();
  pinMode(ledOeste,OUTPUT);
  pinMode(ledSul,OUTPUT);
  pinMode(ledLeste,OUTPUT);
  pinMode(ledNorte,OUTPUT);
  pinMode(ledNordeste,OUTPUT);
  pinMode(ledSudoeste,OUTPUT);
  pinMode(ledSudeste,OUTPUT);
  pinMode(ledNoroeste,OUTPUT);
}

float calculate_heading_degrees(sensors_event_t event){
  
  // Calculando a posição do eixo x e y
  float heading = atan2(event.magnetic.y, event.magnetic.x);

  // Depois de ter sua posição, você deve em seguida, adicionar o seu...
  //'angulo de declincação', que é o 'erro' do campo magnético em...
  //sua localização.
  // Localizar o seu aqui: http://www.magnetic-declination.com/
  // O meu é: -20, que é ~ 20 graus, ou (o que nós precisamos) 0,34 radianos
  // Se você não conseguiu encontrar a sua declinação, comente estas...
  //duas linhas, a bussola ficará um pouco defasada.


  // valor correto para jaraguá do Sul
  float declinationAngle = 0.34;
  heading += declinationAngle;

  // Faz a correção quandos os sinais estão invertidos
  if(heading < 0)
    heading += 2*PI;

  // Verifica a adição de declinação
  if(heading > 2*PI)
    heading -= 2*PI;

  // Converter radianos em graus para facilitar a leitura
  float headingDegrees = heading * 180/M_PI;
  return headingDegrees;
}

void loop()
{
 // Obtem um novo evento do sensor
  sensors_event_t event;
  mag.getEvent(&event);
  float headingDegrees = calculate_heading_degrees(event);
  Serial.print("Posicao em graus: "); Serial.println(headingDegrees);
  Serial.println(cardinal_point_calculation(headingDegrees));
  delay(500);
}

String cardinal_point_calculation(float headingDegrees){
 String cardinal_point = "norte";
  if (headingDegrees > 0 && headingDegrees <= 44.9)
  {
    cardinal_point = "Norte";
    digitalWrite(ledNorte,HIGH);
    delay(1000);
  }
  else if (headingDegrees > 45 && headingDegrees <= 89.9)
  {
    cardinal_point = "Nordeste";
    digitalWrite(ledNordeste,HIGH);
    delay(1000);
  }
  else if (headingDegrees > 90 && headingDegrees <= 134.9)
  {
    cardinal_point = "Leste";
    digitalWrite(ledLeste,HIGH);
    delay(500);
  }
  else if (headingDegrees > 135 && headingDegrees <= 179.9)
  {
    cardinal_point = "Sudeste";
    digitalWrite(ledSudeste,HIGH);
    delay(500);
  }
  else if (headingDegrees > 180 && headingDegrees <= 224.9)
  {
    cardinal_point = "Sul";
    digitalWrite(ledSul,HIGH);
    delay(500);
  }
  else if (headingDegrees > 225 && headingDegrees <= 269.9)
  {
    cardinal_point = "Suldoeste";
    digitalWrite(ledSudoeste,HIGH);
    delay(500);
  }
  else if (headingDegrees > 270 && headingDegrees <= 314.9)
  {
    cardinal_point = "Oeste";
    digitalWrite(ledOeste,HIGH);
    delay(500);
  }
  else if (headingDegrees > 315 && headingDegrees <= 359.9)
  {
    cardinal_point = "Noroeste";
    digitalWrite(ledNoroeste,HIGH);
    delay(500);
  }
 digitalWrite(ledSul,LOW);
 digitalWrite(ledSudoeste,LOW);
 digitalWrite(ledOeste,LOW);
 digitalWrite(ledNoroeste,LOW);
 digitalWrite(ledNorte,LOW);
 digitalWrite(ledNordeste,LOW);
 digitalWrite(ledLeste,LOW);
 digitalWrite(ledSudeste,LOW);
 return cardinal_point;
}

void four_directions_led_test(){
 digitalWrite(ledSul,HIGH);
 delay(1000);
 digitalWrite(ledOeste,HIGH);
 delay(1000);
 digitalWrite(ledNorte,HIGH);
 delay(1000);
 digitalWrite(ledLeste,HIGH);
 delay(1000);
 digitalWrite(ledSul,LOW);
 delay(1000);
 digitalWrite(ledOeste,LOW);
 delay(1000);
 digitalWrite(ledNorte,LOW);
 delay(1000);
 digitalWrite(ledLeste,LOW);
 delay(1000);
}

void eight_directions_led_test(){
 digitalWrite(ledSul,HIGH);
 delay(1000);
 digitalWrite(ledSudoeste,HIGH);
 delay(1000);
 digitalWrite(ledOeste,HIGH);
 delay(1000);
 digitalWrite(ledNoroeste,HIGH);
 delay(1000);
 digitalWrite(ledNorte,HIGH);
 delay(1000);
 digitalWrite(ledNordeste,HIGH);
 delay(1000);
 digitalWrite(ledLeste,HIGH);
 delay(1000);
 digitalWrite(ledSudeste,HIGH);
 delay(1000);
 digitalWrite(ledSul,LOW);
 delay(1000);
 digitalWrite(ledSudoeste,LOW);
 delay(1000);
 digitalWrite(ledOeste,LOW);
 delay(1000);
 digitalWrite(ledNoroeste,LOW);
 delay(1000);
 digitalWrite(ledNorte,LOW);
 delay(1000);
 digitalWrite(ledNordeste,LOW);
 delay(1000);
 digitalWrite(ledLeste,LOW);
 delay(1000);
 digitalWrite(ledSudeste,LOW);
 delay(1000);
}
