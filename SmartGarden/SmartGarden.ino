#include "TinyDHT.h"
#include <buildTime.h>
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
int lightSensor;
int lightSensorValue(){
  lightSensor = map(analogRead(LightSensor), 0, 1023, 100, 0); //mapowanie wartości analogowej na wartość  procentową
  return lightSensor;
}

void setup() {
  Serial.begin(9600);
  dht.begin();
  
  //startowy reset wartosci 
  temperature = 0;
  airHumidity = 0;
  groundHumidity = 0;
  windValue3 = 0;
}

void loop() {

  temperature = dht.readTemperature();
  airHumidity = dht.readHumidity();

  //przeniesienie wartości do buforów
  windValue1 = windValue2;
  windValue2 = windValue3;

  //przypisanie aktulanej wartości
  windValue3 = WIND;
  
  Serial.print("Godzina: ");
  Serial.println(BUILD_HOUR);

  Serial.print("Miesiąc: ");
  Serial.println(BUILD_MONTH);

  Serial.print("Nasłonecznienie: "); //testowe wyświetlanie
  Serial.println(lightSensorValue());
 
  Serial.print("Wilgotnosc gleby wynosi: "); //testowe wyświetlanie
  Serial.println(groundHumidityFunction());//testowe wyświetlanie
 
  Serial.print("Siła wiatru: ");
  Serial.println(WIND);

  Serial.print("Temperatura: ");
  Serial.println(temperature);
  
  Serial.print("Wilgotnosc powietrza: ");
  Serial.println(airHumidity);

  //logika dla markizy
  if(BUILD_HOUR > 6 && BUILD_HOUR < 20){
    if(windValue1 < 350 && windValue2 < 350 && windValue3 < 350){//test 3 ostatnich wartości
        //tu wpisac otwieranie markizy
        Serial.println("Markiza otwarta");//markiza otwarta
       }
    else{
        //tu wpisac zamykanie markizy
        Serial.println("Wieje silny wiatr, markiza zamknięta");//markiza zamknięta
       }

  }
  else{
    Serial.println("O tej godzinie markiza zamknięta");//markiza zamknięta
  }

  //logika dla podlewu
  if(BUILD_MONTH > 3 && BUILD_MONTH < 10){//data od 1 kwietnia do 30 września
    if(BUILD_HOUR > 18 && BUILD_HOUR < 24 || BUILD_HOUR >= 0 && BUILD_HOUR < 9){//czas od 19:00 do 8:59
      if(windValue1 < 350 && windValue2 < 350 && windValue3 < 350){//test 3 ostatnich wartości
        if(groundHumidityFunction() < 30){//zmienić wartość wilgotności głeby
          if(lightSensorValue() < 20){//nasłonecznienie do 19%
            if(temperature > 2){//temperatura powyżej 2 stopni
              //tu wpisać włączenie podlewania
              Serial.println("Podlew włączony");//Podlew włączony
            }
            else{
              Serial.println("Jest zimno, podlew wyłączony");//Podlew wyłączony
            }
          }
          else{
            Serial.println("Słońce jasno świeci, podlew wyłączony");//Podlew wyłączony
          }
        }
        else{
          Serial.println("Wilgotność dostateczna, podlew wyłączony");//Podlew wyłączony
        }
      }
      else{
        Serial.println("Wieje silny wiatr, podlew wyłączony");//Podlew wyłączony
      }
    }
    else{
      Serial.println("O tej godzinie podlew wyłączony");//Podlew wyłączony
    }
  }
  else{
    Serial.println("W tym miesiącu podlew wyłączony");//Podlew wyłączony
  }

  Serial.println("");//odstęp
  delay(4000); //opóźnienie między pomiarami

}
