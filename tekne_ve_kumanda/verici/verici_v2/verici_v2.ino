#include <SPI.h>
#include <nRF24L01.h>  
#include <RF24.h>

#define CE_pin 10
#define CSN_pin 9

#define portser A0 
#define port1x A2
#define port1y A3 
RF24 radio(CE_pin , CSN_pin);

//address through which two modules communicate.
const byte address[6] = "00371";
const byte boyut =3;
int datas[boyut];

void setup()
{
   Serial.begin(9600);

  radio.begin();
  //set the address
  radio.openWritingPipe(address);
  
  //Set module as transmitter
  radio.stopListening();
}
void loop()
{
  //Send message to receiver
radio.stopListening();
 datas[0] = analogRead(portser);//ince ayar servo için //fine tuning knob for servo
 datas[0] = map(datas[0] , 0 , 1023 , -30 , 30 );
 datas[1] = analogRead(port1x);//sağ sol //riğht left
 datas[1] = map(datas[1] , 0 , 1023 , 30 , 150 );
 datas[1]=datas[1]+datas[0];
 datas[2] = analogRead(port1y);//ileri geri //front and back
 datas[2] = map(datas[2] , 0 , 1023 , 165 , -165 );
 
radio.write(&datas , sizeof(datas) );




Serial.println(datas[0]);
Serial.println(datas[1]);
Serial.println(datas[2]);
Serial.println("---------------");
  delay(50);
}
