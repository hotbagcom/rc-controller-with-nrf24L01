#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN

int joystickX1, joystickY1, joystickX2, joystickY2, joystickX3, joystickY3;
int pot1, pot2;
int toggle1, toggle2, toggle3, toggle4;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0,0xF0F0F0F0E1LL);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();

  pinMode(2, OUTPUT); // Örnek bir çıkış pini tanımlama
  pinMode(3, OUTPUT); // Örnek bir çıkış pini tanımlama
}

void loop() {
  if (radio.available()) {
    radio.read(&joystickX1, sizeof(joystickX1));
    radio.read(&joystickY1, sizeof(joystickY1));
    radio.read(&joystickX2, sizeof(joystickX2));
    radio.read(&joystickY2, sizeof(joystickY2));
    radio.read(&joystickX3, sizeof(joystickX3));
    radio.read(&joystickY3, sizeof(joystickY3));
    radio.read(&pot1, sizeof(pot1));
    radio.read(&pot2, sizeof(pot2));
    radio.read(&toggle1, sizeof(toggle1));
    radio.read(&toggle2, sizeof(toggle2));
    radio.read(&toggle3, sizeof(toggle3));
    radio.read(&toggle4, sizeof(toggle4));

    // Burada, gelen verilere göre teknenin hareketlerini kontrol edebilirsiniz.
    // Joystick'ler ve potansiyometrelerin okunan verilerini kullanarak
    // teknenin hareketini ayarlayabilirsiniz.

    // Toggle switch'lerin durumunu kontrol edebilir ve diğer aksesuarları kontrol edebilirsiniz.

    // Örnek hareket kontrol kodu:
    int hiz = map(pot1, 0, 1023, 0, 255); // Potansiyometre değerini hıza dönüştürme
    analogWrite(motorPin, hiz); // Hızı motor pinine yazma
    int x = map(joystickX1, 0, 1023, -255, 255); // Joystick değerini hareket yönüne dönüştürme
    digitalWrite(2, toggle1); // Toggle switch'in durumuna göre çıkış pini durumunu ayarlama
    digitalWrite(3, toggle2); // Toggle switch'in durumuna göre çıkış pini durumunu ayarlama

    // Diğer hareket kontrol kodları ve aksesuar kontrol kodları buraya eklenebilir
  }
}
