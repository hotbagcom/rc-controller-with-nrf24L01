#include <SPI.h>
#include <nRF24L01.h>  
#include <RF24.h>
#include <Servo.h>

#define CE_pin 7
#define CSN_pin 8
#define pwmotor 5
#define yesil 1
#define mavi 0


RF24 radio(CE_pin , CSN_pin);
//address through which two modules communicate.
const byte address[6] = "00371";
const byte boyut = 3;

int datas[boyut] ;


Servo sg90;


void setup()
{
  while (!Serial);
    Serial.begin(9600);
  
  radio.begin();
  
  //set the address
  radio.openReadingPipe(0, address);
  
  //Set module as receiver
  radio.startListening();

  pinMode(pwmotor , OUTPUT);
  pinMode(yesil , OUTPUT);
  pinMode(mavi , OUTPUT);

digitalWrite(mavi, LOW);
digitalWrite(yesil, LOW);

  sg90.attach(3);    //Set servo pin at digital 5
  sg90.write(90);

  
}

void loop()
{
  //Read the data if available in buffer

  
 if(radio.available()){
   radio.read( &datas , sizeof(datas));
    Serial.println(datas[1]);
    sg90.write(datas[1]);

    analogWrite(pwmotor,abs(datas[2]));
    if(datas[2]>0){
      digitalWrite(yesil, HIGH);
      digitalWrite(mavi, LOW);
      Serial.println("yeşil");
    }
        else if(datas[2]<0){
      digitalWrite(yesil, LOW);
      digitalWrite(mavi, HIGH);
      Serial.println("mavi");
    }
    else{
    Serial.println(datas[2]);
    }
    
    if(datas[1]==90){
    Serial.println("orta");
    }
    else if(datas[1]>90 && datas[1]<=180){
    Serial.println("sağ");
    }
    else if(datas[1]<90 && datas[1]>=0){
    Serial.println("sol");
    }
    else{
    Serial.println("tehlike servo");
    }
    delay(150);
 
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
