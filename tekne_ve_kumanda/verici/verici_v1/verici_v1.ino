#include <SPI.h>
#include <nRF24L01.h>  
#include <RF24.h>

#define CE_pin 10
#define CSN_pin 9
//sck 13
//mi 12
//mo 11
#define portser A0 
#define port1x A2
#define port1y A3 
RF24 radio(CE_pin , CSN_pin);

//address through which two modules communicate.
const byte address[6] = "00001";
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
 datas[0] = analogRead(portser);
 datas[0] = map(datas[0] , 0 , 1023 , 30 , 150 );
 datas[1] = analogRead(port1x);
 datas[1] = map(datas[1] , 0 , 1023 , 30 , 150 );
 datas[2] = analogRead(port1y);
 datas[2] = map(datas[2] , 0 , 1023 , 30 , 150 );
 
radio.write(&datas , sizeof(datas) );




Serial.println(datas[0]);
  delay(50);
}
