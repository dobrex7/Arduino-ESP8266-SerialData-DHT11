#include<SoftwareSerial.h> // knjiznica za serijsko komunikacijo (z esp8266)
#include <dht11.h> // knjiznica za temperaturo in vlago

#define DHT11PIN 8 // definiramo dht11 vhod na 8
dht11 DHT11;

SoftwareSerial Arduino_SoftSerial(10, 11);  //10 povezano na D2, 11 povezano na D1
char c; // prazen znak z imenom c
String dataIn; // niz z imenom dataIn

void setup()
{
  Serial.begin(115200); // inicializiramo serijsko komunikacijo na vrednosti 115200
  Arduino_SoftSerial.begin(9600); // inicializiramo serijsko komunikacijo za posiljanje iz arduina na esp8266, na vrednosti 9600
}

void loop()
{
  Serial.println(); //izpis prazne vrstice
  int chk = DHT11.read(DHT11PIN); // branje iz senzorja
  
  Serial.print("Vlaznost (%): ");
  Serial.println((float)DHT11.humidity); // izpis vlage na serijski zaslon

  Serial.print("Temperatura (C): ");
  Serial.println((float)DHT11.temperature); // izpis temperature na serijski zaslon

  Serial.println(); //izpis prazne vrstice

  delay(2000); // 2 sekundi premora

Arduino_SoftSerial.print("Vlaznost (%): ");
Arduino_SoftSerial.print((float)DHT11.humidity);
Arduino_SoftSerial.print(',');

Arduino_SoftSerial.print("Temperatura (C): ");
Arduino_SoftSerial.print((float)DHT11.temperature);
Arduino_SoftSerial.println();

// while zanka, ki sprejema podatke iz ESP8266, v primeru, da so podatki poslani 
 while(Arduino_SoftSerial.available()>0)
  {
      c = Arduino_SoftSerial.read(); // c = kar prebere iz ESP8266 podatke
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

