#include <SPI.h>
#include <nRF24L01.h>  
#include <RF24.h>
#include <Servo.h>

#define CE_pin 10
#define CSN_pin 9

RF24 radio(CE_pin , CSN_pin);
//address through which two modules communicate.

const byte address[6] = "00001";
const byte boyut = 3;

int datas[boyut] ;


Servo sg90;


void setup()
{
  while (!Serial);
    Serial.begin(9600);
  
  radio.begin();
  //radio.setDataRate( RF24_250KBPS );
  //set the address
  radio.openReadingPipe(0, address);
  
  //Set module as receiver
  radio.startListening();
datas[0]=45;
  sg90.attach(6);    //Set servo pin at digital 5
  sg90.write(150);
  delay (1500);
  
}

void loop()
{
  //Read the data if available in buffer
radio.read( &datas , sizeof(datas));
/*
 Serial.println(datas[0]);
  Serial.println(datas[1]);
   Serial.println(datas[2]);
   */
   delay(500);
  if (radio.available()){
   radio.read( &datas , sizeof(datas));
    Serial.println("---------------------------");
    Serial.println(datas[0]);
    sg90.write(datas[0]);
    delay(121);
    }
   else{
  Serial.println("no connect");
  delay(500);
  }

    
                        //iyileştirme yap   düzelt
/*
    for (byte i = 0;  i < boyut; i++)
    {
  
        if(datap[i] != datas[i]){break;}
      datap[boyut] = radio.read( &datas , sizeof(datas));
        if(i==boyut){ i = 0 ;}
    }
*/





    
  

}
