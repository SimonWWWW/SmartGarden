#include "DHT.h"
#define groundHumiditySensor A0 //przypisanie pinu A0 do czujnika wilgotnosci gleby
//Jako sensor wykorzystana jest miniaturowa turbina wiatrowa. Napięcie generowane przez turbinę jest monitorowane na porcie szeregowym.
//Kiedy wartość przekracza próg markiza jest zamykana (lub nie otwiera się). Co do wartości potrzeba wygrzebać przelicznik lub kalibrację.
#define WIND A1 //przypisanie pinu A1 do czujnika prędkości wiatru
#define LightSensor A2 //przypisanie pinu A2 do czujnika nasłonecznienia
#define DHTTYPE DHT11 //TYP DHT11
#define DHTPIN 3  // PIN 3 - czujnik DHT11


int windValue1; //definicja wartości pomiarów wiatru
int windValue2;
int windValue3;
DHT dht(DHTPIN, DHTTYPE);

int lightSensorValue;
  
int temperature;
int airHumidity;

int pressure;

int groundHumidity;

String Podlewanie;
String Markiza;

void setup() {
  Serial.begin(9600);
  dht.begin();
  
  //startowy reset wartosci 
  temperature = 0;
  airHumidity = 0;
  groundHumidity = 0;
  windValue3 = 0;
  groundHumidity = 0;
  pressure = 0;
  lightSensorValue = 0;
  

}

void loop() {  
  lightSensorValue = analogRead(LightSensor);
  //Serial.println(lightSensorValue);

  
  groundHumidity = map(analogRead(groundHumiditySensor),0,620,0,100); //mapowanie wartości analogowej na wartosc  procentowa (wartosci 0 do 620 uzyskane doswiadczalnie)
  //Serial.println(groundHumidity);//testowe wyświetlanie 
  
  
  temperature = dht.readTemperature();
  airHumidity = dht.readHumidity();

  /*Serial.println(String(temperature));
  Serial.println(String(0000));
  Serial.println(String(airHumidity));
  Serial.println(String(WIND));
  Serial.println(String(lightSensorValue));
  Serial.println(String(groundHumidity));*/
  //siła wiatru***************end
  delay(5000); //opóźnienie między pomiarami
  Serial.println("__________________________");
  Serial.print("Temperatura: "); 
  Serial.println((String)temperature);
  Serial.print("Cisnienie: ");
  Serial.println((String)pressure);
  Serial.print("Wilgotnosc powietrza: ");
  Serial.println((String)airHumidity);
  Serial.print("Sila wiatru: ");
  Serial.println((String)windValue3); 
  Serial.print("Naslonecznienie: ");
  Serial.println((String)lightSensorValue);
  Serial.print("Wilgotnosc gleby: ");
  Serial.println((String)groundHumidity);
  Serial.print("Stan markizy: ");
  Serial.println(Markiza);
  Serial.print("Stan podlewania: ");
  Serial.println(Podlewanie);
  //przeniesienie wartości do buforów
 /* windValue1 = windValue2;
  windValue2 = windValue3;

  //przypisanie aktulanej wartości
  windValue3 = WIND;

  //test 3 ostatnich wartości
  if(windValue1 > 350 && windValue2 > 350 && windValue3 > 350)
       {
        //markiza zamknięta
        //zraszacze wyłączone
       }
  */
  //siła wiatru***************end

}
