#include <SPI.h>
#include <nRF24L01.h>  
#include <RF24.h>

#define CE_pin 8
#define CSN_pin 7

#define portpot A2
#define port1x A1
#define port1y A0
RF24 radio(CE_pin , CSN_pin);

//address through which two modules communicate.
//const byte address[6] = "00371";
const byte address[6] = "00371";
const byte boyut = 4;
int datas[boyut];

void setup()
{
   Serial.begin(9600);

  radio.begin();
  //radio.setDataRate( RF24_250KBPS );
  //set the address
  radio.openWritingPipe(address);
  
  //Set module as transmitter
  radio.stopListening();
  datas[0]=100;
  datas[1]=100;
  datas[2]=100;
  datas[3]=100;
}
void loop()
{
  //Send message to receiver

 datas[0] = analogRead(port1y);//sağ sol //riğht left
 datas[0] = map(datas[0] , 0 , 1023 , 30 , 150 );
 //datas[1] = analogRead(portpot);//ince ayar motor için //fine tuning knob for motors
 datas[1] = 120;//map(datas[1] , 0 , 1023 , 0 ,250 );
 datas[2] = analogRead(port1y);//ileri geri //front and back
 datas[2] = map(datas[2] , 0 , 1023 , 0, datas[1] );
 datas[3] = analogRead(port1x);
 datas[3] = map(datas[3] , 0 , 1023 , -datas[2]/3 , datas[2]/3 );
radio.write(&datas , sizeof(datas) );





Serial.println(datas[0]);
Serial.println(datas[1]);
Serial.println(datas[2]);
Serial.println(datas[3]);
Serial.println("---------------");
  delay(1500);
}
