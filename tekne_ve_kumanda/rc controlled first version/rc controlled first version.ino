#include <SPI.h>
#include <nRF24L01.h>  
#include <RF24.h>

const byte CE_pin = 7 ;
const byte CSN_pin = 8 ;

RF24 radio(CE_pin , CSN_pin);
const byte address[6] = "00371"; //address through which two modules communicate.
const byte boyut = 5;
int datas[boyut] ;

void serialprint();

void setup() {
radio.begin();
  radio.openReadingPipe(0, address); //set the address
  radio.startListening(); //Set module as receiver
Serial.begin(9600);
}

void loop() {
  Serial.println("//*\\*//*\\");
  if(radio.available()){
    radio.read( &datas , sizeof(int)*5);
    serialprint();
  }
  else{
    Serial.println("no connection");
    delay(200);
  }
  

}

void serialprint(){
  Serial.print("joystick 1 : ");
  Serial.println(datas[0]);
  Serial.print("potansiyometre : ");
  Serial.println(datas[1]);
  Serial.print("joystick x : ");
  Serial.println(datas[2]);
  Serial.print("joystick y : ");
  Serial.println(datas[3]);
  Serial.print("boolean : ");
  Serial.println(datas[4]&&0b1111);

  delay(1000);

}