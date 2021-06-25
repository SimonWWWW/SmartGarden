#include <Wire.h>
#include <buildTime.h>
#include <TinyDHT.h>
#include <Adafruit_BMP085.h>
#define groundHumiditySensor A0 //przypisanie pinu A0 do czujnika wilgotnosci gleby
//Jako sensor wykorzystana jest miniaturowa turbina wiatrowa. Napięcie generowane przez turbinę jest monitorowane na porcie szeregowym.
//Kiedy wartość przekracza próg markiza jest zamykana (lub nie otwiera się). Co do wartości potrzeba wygrzebać przelicznik lub kalibrację.
#define WIND A1 //przypisanie pinu A1 do czujnika prędkości wiatru
#define LightSensor A2 //przypisanie pinu A2 do czujnika nasłonecznienia
#define DHTTYPE DHT11 // PIN 3 - czujnik DHT11
#define DHTPIN 2  
DHT dht(DHTPIN, DHTTYPE);

Adafruit_BMP085 bmp;

int windValue1; //definicja wartości pomiarów wiatru
int windValue2;
int windValue3;

int pressure;

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


String text;

void setup() {
  Serial.begin(9600);
  dht.begin();
  
  //startowy reset wartosci 
  lightSensor = 0;
  temperature = 0;
  pressure = 0;
  airHumidity = 0;
  groundHumidity = 0;
  windValue3 = 0;
}

void loop() {

  pressure = bmp.readSealevelPressure();

  temperature = dht.readTemperature();
  airHumidity = dht.readHumidity();

  //przeniesienie wartości do buforów
  windValue1 = windValue2;
  windValue2 = windValue3;

  //przypisanie aktulanej wartości
  windValue3 = WIND;
  

  //logika dla markizy
  if(BUILD_HOUR > 6 && BUILD_HOUR < 20){
    if(windValue1 < 350 && windValue2 < 350 && windValue3 < 350){//test 3 ostatnich wartości
        //tu wpisac otwieranie markizy
        text = ("Markiza otwarta");//markiza otwarta
       }
    else{
        //tu wpisac zamykanie markizy
        text = ("Wieje silny wiatr, markiza zamknieta");//markiza zamknięta
       }

  }
  else{
    text = ("O tej godzinie markiza zamknieta");//markiza zamknięta
  }

  //logika dla podlewu
  if(BUILD_MONTH > 3 && BUILD_MONTH < 10){//data od 1 kwietnia do 30 września
    if(BUILD_HOUR > 18 && BUILD_HOUR < 24 || BUILD_HOUR >= 0 && BUILD_HOUR < 9){//czas od 19:00 do 8:59
      if(windValue1 < 350 && windValue2 < 350 && windValue3 < 350){//test 3 ostatnich wartości
        if(groundHumidityFunction() < 30){//zmienić wartość wilgotności głeby
          if(lightSensorValue() < 20){//nasłonecznienie do 19%
            if(temperature > 2){//temperatura powyżej 2 stopni
              //tu wpisać włączenie podlewania
              text = ("Podlew wlaczony");//Podlew włączony
            }
            else{
              text = ("Jest zimno, podlew wylaczony");//Podlew wyłączony
            }
          }
          else{
            text = ("Slonce jasno swieci, podlew wylaczony");//Podlew wyłączony
          }
        }
        else{
          text = ("Wilgotnosc dostateczna, podlew wylaczony");//Podlew wyłączony
        }
      }
      else{
        text = ("Wieje silny wiatr, podlew wylaczony");//Podlew wyłączony
      }
    }
    else{
      text = ("O tej godzinie podlew wylaczony");//Podlew wyłączony
    }
  }
  else{
    text = ("W tym miesiącu podlew wylaczony");//Podlew wyłączony
  }
  Serial.println("__________________________________________");
  Serial.println("SMART GARDEN");
  Serial.print("Temperatura: "); 
  Serial.print((String)temperature);
  Serial.println(" *C");
  Serial.print("Cisnienie: ");
  Serial.print((String)pressure);
  Serial.println(" hPa");
  Serial.print("Wilgotnosc powietrza: ");
  Serial.print((String)airHumidity);
  Serial.println(" %");
  Serial.print("Sila wiatru: ");
  Serial.println((String)windValue3); 
  Serial.print("Naslonecznienie: ");
  Serial.print((String)lightSensorValue());
  Serial.println(" %");
  Serial.print("Wilgotnosc gleby: ");
  Serial.print((String)groundHumidity);
  Serial.println(" %");
  Serial.println("__________________________________________");
  Serial.println("KOMUNIKAT:");
  Serial.println(text);
  Serial.println("__________________________________________");
  delay(4000); //opóźnienie między pomiarami
  

}
