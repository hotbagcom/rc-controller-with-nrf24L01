#include "SPI.h"              // SPI kütüphanesini ekliyoruz
 #include "Wire.h"             // Wire kütüphanesini ekliyoruz
 #include "Adafruit_SSD1306.h" // Adafruit'in SSD1306 kütüphanesini ekliyoruz
 #include <nRF24L01.h>         //nRF24L01 kütüphanesini ekliyoruz 
 #include <RF24.h>             //RF24 kütüphanesini ekliyoruz

//pinleri const ile sabitliyoruz 
const byte pbd2 = 2;
const byte pbd3 = 3;
const byte slided7 = 7;
const byte toggled8 = 8;
const byte onejoyya0 = A0;
const byte pota1 = A1;
const byte twojoyya6 = A6;
const byte twojoyxa7 = A7;
const byte CE_pind10 = 10;
const byte CSN_pind9 = 9;

bool pushbuttond2_state = false; //sol alttaki bastırmalı buton için
bool pushbuttond3_state = false; //sol üstteki bastırmalı buton için
bool slideswitch_state = false; //kaydırmalı buton için 
bool toogleswitch_state = false; //çubulu buton için
int potansiyo_state = 0; //gerilim bölücü için 
int joystick1_state = 0; //tek eksenli eğlence çubuğu için 
int joystick2x_state = 0; //iki eksenli eğlence çubuğunun yatay ekseni için
int joystick2y_state = 0; //iki eksenli eğlence çubuğunun dikey ekseni için
int digital_nrf_ = 0;

int genislik = 128; // OLED ekran genişliği (piksel olarak)
int yukseklik = 64; // OLED ekran yüksekliği (piksel olarak)
int adres = 0x3C;   // 128x64 için 0x3C (bazı modüllerde 0x3D)
 
Adafruit_SSD1306 ekran(genislik, yukseklik, &Wire); // Kütüphaneyi tanımlıyoruz
RF24 radio(CE_pind10 , CSN_pind9);//nrf için pinleri belirle
//nrf için paket hazırlama
const byte address[6] = "00371";
const byte boyut = 5;
int datas[boyut];

void digitalpin();
void analog();
void digital();
void digital_nrf();
void manage_displayer();
void prepare_delivery();

void setup() {
  ekran.begin(SSD1306_SWITCHCAPVCC, adres);         // ekran için Kütüphaneyi başlatıyoruz
  digitalpin();
  radio.begin();
    radio.openWritingPipe(address);//set the address
    radio.stopListening();//Set module as transmitter

}

void loop() {
  ekran.clearDisplay();        // Ekranı temizleyelim
  ekran.display();             // Ekranı görüntüleyelim
  analog();                    // Analog input verilerini topla
  digital();                   // Dijital input verilerini topla

  manage_displayer();          // Ekrana verileri yazdır
  prepare_delivery();          // Nrf ile gönderilecek verileri hazırla
  
}

void digitalpin(){
  pinMode(pbd2,INPUT);
  pinMode(pbd3,INPUT);
  pinMode(slided7,INPUT); 
  pinMode(toggled8,INPUT); 
}

void analog(){
  joystick1_state = analogRead(onejoyya0);
  potansiyo_state = analogRead(pota1);
  joystick2x_state = analogRead(twojoyxa7);
  joystick2y_state = analogRead(twojoyya6);
}

void digital(){
  pushbuttond2_state = digitalRead(pbd2); //sol alttaki bastırmalı buton verisini almak için
  pushbuttond3_state = digitalRead(pbd3); //sol üstteki bastırmalı buton verisini almak için
  slideswitch_state = digitalRead(slided7); //kaydırmalı buton verisini almak için
  toogleswitch_state = digitalRead(toggled8); //çubuklu buton verisini almak için
  digital_nrf();
}

void digital_nrf(){
  digital_nrf_ = pushbuttond2_state; //digital_nrf_ = digital_nrf_ <<
  digital_nrf_ = digital_nrf_ << 1 ;
  digital_nrf_ = digital_nrf_ + pushbuttond3_state;
  digital_nrf_ = digital_nrf_ << 1 ;
  digital_nrf_ = digital_nrf_ + slideswitch_state;
  digital_nrf_ = digital_nrf_ << 1 ;
  digital_nrf_ = digital_nrf_ + toogleswitch_state;
}

void manage_displayer(){
  ekran.clearDisplay();
  ekran.setTextSize(1); // Yazı boyutu
  ekran.setTextColor(SSD1306_WHITE);
  ekran.clearDisplay();
  ekran.setCursor(0, 10); // Başlangıç konumu(yatay,dikey)
  ekran.print("joy1 : ");//tek yönlü eğlence çubuğu
  ekran.println(joystick1_state);//tek yönlü eğlence çubuğu

  ekran.setCursor(0, 20); // Başlangıç konumu(yatay,dikey)//////////buton hıgh olarak göstermiyor (arasıra gösteriyor)
  ekran.print("d3 pb ");
  ekran.println( pushbuttond3_state);

  ekran.setCursor(0, 30); // Başlangıç konumu(yatay,dikey)//////////buton hıgh olarak göstermiyor (arasıra gösteriyor)
  ekran.print("d2 pb ");
  ekran.println( pushbuttond2_state);

  ekran.setCursor(0, 40); // Başlangıç konumu(yatay,dikey)
  ekran.print("pot : ");
  ekran.println( potansiyo_state ); //ekran.println( potansiyo_state , HEX ); 16 bitlik yazdırabiliyoruz

  ekran.setCursor(10, 50); // Başlangıç konumu(yatay,dikey)
  ekran.print("slide : ");
  ekran.println( slideswitch_state);
  

  ekran.setCursor(70, 50); // Başlangıç konumu(yatay,dikey)
  ekran.print("toggle ");
  ekran.println( toogleswitch_state);
  /*
  ekran.setCursor(50, 30); // Başlangıç konumu(yatay,dikey)
  ekran.print("");
  ekran.println( potansiyo_state , BIN );
  */
  ekran.setCursor(50, 0); // Başlangıç konumu(yatay,dikey)
  ekran.print("x axis : ");
  ekran.println(joystick2x_state);

  ekran.setCursor(50, 20); // Başlangıç konumu(yatay,dikey)
  ekran.print("y axis : ");
  ekran.println(joystick2y_state);

  ekran.display();
  delay(400);
  
}


void prepare_delivery(){
  datas[0] =joystick1_state; //map( joystick1_state , 0 , 1023 , 0 , 1023 ); //kamera ileri geri servo
  datas[1] = potansiyo_state; //map( potansiyo_state , 0 , 1023 , 0 , 1023 ); //kamera sağsol 
  datas[2] = 1023-joystick2x_state; //map( joystick2x_state , 0 , 1023 , 1023 , 0 ); //sağsol
  datas[3] = 1023-joystick2y_state; //map( joystick2y_state , 0 , 1023 , 1023 , 0 ); //ileri geri
  datas[4] = digital_nrf_;
  
 
  radio.write(&datas , sizeof(datas) );
}


