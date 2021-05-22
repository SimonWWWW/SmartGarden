#define czujnikWilgotnosciGleby A0 //przypisanie pinu A0 do czujnika wilgotnosci gleby
//Jako sensor wykorzystana jest miniaturowa turbina wiatrowa. Napięcie generowane przez turbinę jest monitorowane na porcie szeregowym.
//Kiedy wartość przekracza próg markiza jest zamykana (lub nie otwiera się). Co do wartości potrzeba wygrzebać przelicznik lub kalibrację.
#define WIND A1 //przypisanie pinu A1 do czujnika prędkości wiatru

int windValue1; //definicja wartości pomiarów wiatru
int windValue2;
int windValue3;

int wilgotnoscGleby = 0;
int sprawdzanieWilgotnosciGleby(){
  wilgotnoscGleby = map(analogRead(czujnikWilgotnosciGleby),0,620,0,100); //mapowanie wartości analogowej na wartosc  procentowa (wartosci 0 do 620 uzyskane doswiadczalnie)
  return wilgotnoscGleby;
}
void setup() {
  Serial.begin(9600);
  
  //startowy reset wartosci wiatru
  windValue3 = 0;
}

void loop() {
  Serial.print("Wilgotnosc gleby wynosi: "); //testowe wyświetlanie 
  Serial.println(sprawdzanieWilgotnosciGleby());//testowe wyświetlanie 
  
  //siła wiatru************start
  //podanie aktualej na serial
  Serial.print("Siła wiatru: ");
  Serial.println(WIND);

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

   delay(6000); //opóźnienie między pomiarami
  //siła wiatru***************end

}
