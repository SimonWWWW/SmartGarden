#define czujnikWilgotnosciGleby A0 //przypisanie pinu A0 do czujnika wilgotnosci gleby
int wilgotnoscGleby = 0;
int sprawdzanieWilgotnosciGleby(){
  wilgotnoscGleby = map(analogRead(czujnikWilgotnosciGleby),0,620,0,100); //mapowanie wartości analogowej na wartosc  procentowa (wartosci 0 do 620 uzyskane doswiadczalnie)
  return wilgotnoscGleby;
}
void setup() {
  Serial.begin(9600);

}

void loop() {
  Serial.print("Wilgotnosc gleby wynosi: ");
  Serial.println(sprawdzanieWilgotnosciGleby());

}
