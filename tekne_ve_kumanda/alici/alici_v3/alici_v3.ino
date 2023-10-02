#include <SPI.h>
#include <nRF24L01.h>  
#include <RF24.h>
//#include <Servo.h>

#define CE_pin 0
#define CSN_pin 1
#define pwmotor1 9
#define pwmotor2 3
#define ka1 8
#define ki1 7
#define ka2 4
#define ki2 2
 


RF24 radio(CE_pin , CSN_pin);
//address through which two modules communicate.
const byte address[6] = "00371";
const byte boyut = 4;

int datas[boyut] ;

//Servo sg90;

void setup()
{
 // while (!Serial);
    //Serial.begin(9600);
  
  radio.begin();
  
  //set the address
  radio.openReadingPipe(0, address);
  
  //Set module as receiver
  radio.startListening();

  pinMode(pwmotor1 , OUTPUT);
  pinMode(ka1 , OUTPUT);
  pinMode(ki1 , OUTPUT);
  pinMode(pwmotor2 , OUTPUT);
  pinMode(ka2 , OUTPUT);
  pinMode(ki2 , OUTPUT);
  
digitalWrite(ka1, LOW);
digitalWrite(ki1, LOW);  
digitalWrite(ka2, LOW);
digitalWrite(ki2, LOW);
 // my90.attach(6);    //Set servo pin at digital 6
 // my90.write(45);
 
delay (3000);

}

void loop()
{
  //Read the data if available in buffer

  
 if(radio.available()){
radio.read( &datas , sizeof(datas));
     Serial.println(datas[0]);
     //Serial.println(datas[1]);
     Serial.println(datas[2]); 
      Serial.println("***************************************");
  //  my90.write(datas[0]);

    analogWrite(pwmotor1,datas[2]);
    analogWrite(pwmotor2,datas[2]);
    
    if(datas[2]>5){
      digitalWrite(ki1, HIGH);
      digitalWrite(ka1, LOW);
      digitalWrite(ki2, HIGH);
      digitalWrite(ka2, LOW);
     
    }
        else if(datas[2]<-5){
      digitalWrite(ki1, LOW); 
      digitalWrite(ka1, HIGH);
      digitalWrite(ki2, LOW);
      digitalWrite(ka2, HIGH);
    }
    else{
      digitalWrite(ki1, LOW);
      digitalWrite(ki2, LOW);
      digitalWrite(ka1, LOW);
      digitalWrite(ka2, LOW);
    }
    
    delay(100);
}
  /* }
   else{
  Serial.println("no connect");
  delay(500);
  }
 /*
    
  else{
  Serial.println("no connect");
  delay(500);
  }
    */
                        //iyileştirme yap   düzelt
/*
    for (byte i = 0;  i < boyut; i++)
    {
  
        if(datap[i] != datas[i]){break;}
      datap[boyut] = radio.read( &datas , sizeof(datas));
        if(i==boyut){ i = 0 ;}
    }
*/





    /*
  digitalWrite(ki1, HIGH);
      digitalWrite(ka1, LOW);
      digitalWrite(ki2, HIGH);
      digitalWrite(ka2, LOW);
 for(int a =20 ;a<=250; a=a+10){
   delay(500);
   analogWrite(pwmotor2,a);
   analogWrite(pwmotor1,a);
   }*/
}
 

