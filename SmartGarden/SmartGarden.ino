#include "DHT.h"
#define groundHumiditySensor A0 //przypisanie pinu A0 do czujnika wilgotnosci gleby
//Jako sensor wykorzystana jest miniaturowa turbina wiatrowa. Napięcie generowane przez turbinę jest monitorowane na porcie szeregowym.
//Kiedy wartość przekracza próg markiza jest zamykana (lub nie otwiera się). Co do wartości potrzeba wygrzebać przelicznik lub kalibrację.
#define WIND A1 //przypisanie pinu A1 do czujnika prędkości wiatru
#define LightSensor A2 //przypisanie pinu A2 do czujnika nasłonecznienia
#define DHTTYPE DHT11 // PIN 3 - czujnik DHT11
#define DHTPIN 2  

int windValue1; //definicja wartości pomiarów wiatru
int windValue2;
int windValue3;
DHT dht(DHTPIN, DHTTYPE);

float temperature;
float airHumidity;

int groundHumidity;
int groundHumidityFunction(){
  groundHumidity = map(analogRead(groundHumiditySensor),0,620,0,100); //mapowanie wartości analogowej na wartosc  procentowa (wartosci 0 do 620 uzyskane doswiadczalnie)
  return groundHumidity;
}
void setup() {
  Serial.begin(9600);
  dht.begin();
  
  //startowy reset wartosci 
  temperature = 0;
  airHumidity = 0;
  groundHumidity = 0;
  windValue3 = 0;
  groundHumidity = 0;
}

void loop() {
  int lightSensorValue = analogRead(LightSensor);
  Serial.print("Nasłonecznienie: "); //testowe wyświetlanie
  Serial.println(lightSensorValue, DEC);
  
  Serial.print("Wilgotnosc gleby wynosi: "); //testowe wyświetlanie 
  Serial.println(groundHumidityFunction());//testowe wyświetlanie 
  
  //siła wiatru************start
  //podanie aktualej na serial
  Serial.print("Siła wiatru: ");
  Serial.println(WIND);
  
  temperature = dht.readTemperature();
  airHumidity = dht.readHumidity();
  
  Serial.print("Temperatura: ");
  Serial.println(temperature);
  Serial.print("Wilgotnosc powietrza: ");
  Serial.println(airHumidity);

  //przeniesienie wartości do buforów
  windValue1 = windValue2;
  windValue2 = windValue3;

  //przypisanie aktulanej wartości
  windValue3 = WIND;

  //test 3 ostatnich wartości
  if(windValue1 > 350 && windValue2 > 350 && windValue3 > 350)
       {
        //markiza zamknięta
        //zraszacze wyłączone
       }

   delay(4000); //opóźnienie między pomiarami
  //siła wiatru***************end

}
