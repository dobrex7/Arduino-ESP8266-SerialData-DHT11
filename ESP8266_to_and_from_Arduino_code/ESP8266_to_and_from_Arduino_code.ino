#include<SoftwareSerial.h> // knjiznica za serijsko komunikacijo (z arduinom)
SoftwareSerial NodeMcu_SoftSerial(D1, D2);  //D1 povezano na 11, D2 povezano na 10

char c; // prazen znak z imenom c
String dataIn; // niz z imenom dataIn

void setup()
{
  Serial.begin(115200); // inicializiramo serijsko komunikacijo na vrednosti 115200
  NodeMcu_SoftSerial.begin(9600); // inicializiramo serijsko komunikacijo za posiljanje iz esp8266 na arduino, na vrednosti 9600
}

void loop()
{
  //izpis, ki se ga pošlje po digitalnih pinih na Arduino
  NodeMcu_SoftSerial.print("Sporocilo iz ESP8266 \n");

  // while zanka, ki sprejema podatke iz Arduina, v primeru, da so podatki poslani 
 while(NodeMcu_SoftSerial.available()>0)
  {
      c = NodeMcu_SoftSerial.read(); // c = kar prebere iz Arduina podatke
      if(c=='\n') // ce je c new line 
      {
        break; //prekini
      }
      else {
        dataIn+=c; // zdruzi podatke iz c z dataIn
        }
  }
  //v primeru da je nova vrsta izpiši podatke oziroma dataIn 
if (c=='\n')
{
  Serial.println(dataIn);

  //reset oziroma ponastavitev na 0
  c=0;
  dataIn="";
}
}

