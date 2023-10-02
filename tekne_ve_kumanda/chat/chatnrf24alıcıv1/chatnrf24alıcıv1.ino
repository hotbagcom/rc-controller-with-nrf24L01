#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

RF24 radio(7, 8); // CE, CSN

int joystickX1, joystickY1, joystickX2, joystickY2, joystickX3, joystickY3;
int pot1, pot2;
int toggle1, toggle2, toggle3, toggle4;

int motor1Pin1 = 2;
int motor1Pin2 = 3;
int motor2Pin1 = 4;
int motor2Pin2 = 5;
int motorDriverPWM = 6;
int servoPin = 9;
int ledPin1 = 10;
int ledPin2 = 11;

Servo servo;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0,0xF0F0F0F0E1LL);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();

  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(motorDriverPWM, OUTPUT);
  pinMode(servoPin, OUTPUT);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);

  servo.attach(servoPin);
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

    int motorSpeed = map(pot1, 0, 1023, 0, 255); // Potansiyometre değerini hıza dönüştürme
    int motorTurn = map(joystickX1, 0, 1023, -255, 255); // Joystick değerini hareket yönüne dönüştürme
    int motorDirection1 = 0, motorDirection2 = 0;

    if (motorTurn > 0) {
      motorDirection1 = 1;
      motorDirection2 = 0;
    } else if (motorTurn < 0) {
      motorDirection1 = 0;
      motorDirection2 = 1;
    }

    analogWrite(motorDriverPWM, motorSpeed); // Hızı motor sürüc
  digitalWrite(motor1Pin1, motorDirection1);
  digitalWrite(motor1Pin2, motorDirection2);
  digitalWrite(motor2Pin1, motorDirection2);
  digitalWrite(motor2Pin2, motorDirection1);

  if (toggle1 == 1) {
    digitalWrite(ledPin1, HIGH);
  } else {
    digitalWrite(ledPin1, LOW);
  }

  if (toggle2 == 1) {
    digitalWrite(ledPin2, HIGH);
  } else {
    digitalWrite(ledPin2, LOW);
  }

  int servoAngle = map(joystickX2, 0, 1023, 0, 180); // Joystick değerini servo açısına dönüştürme
  servo.write(servoAngle);

  if (toggle3 == 1) {
    digitalWrite(motor1Pin1, HIGH);
    digitalWrite(motor1Pin2, LOW);
    digitalWrite(motor2Pin1, HIGH);
    digitalWrite(motor2Pin2, LOW);
  } else if (toggle4 == 1) {
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, HIGH);
    digitalWrite(motor2Pin1, LOW);
    digitalWrite(motor2Pin2, HIGH);
  } else {
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, LOW);
    digitalWrite(motor2Pin1, LOW);
    digitalWrite(motor2Pin2, LOW);
  }
  }
}
//Bu kod, nRF24L01 kablosuz modülü aracılığıyla gelen verileri okur ve ardından motorları, LED'leri ve servo motoru kontrol eder. Potansiyometreler, joystick'ler ve toggle switch'lerden gelen veriler, önceden tanımlanmış fonksiyonlara dönüştürülür ve bu fonksiyonlar kullanılarak motorların hızı ve yönü, LED'lerin açık/kapalı durumu ve servo motorun açısı kontrol edilir. 

//Motor sürücüsü, motorları hız ve yön bilgileriyle kontrol edebilecek şekilde bağlıdır. Servo motor, joystick'lerden gelen verilere göre belirtilen açıya döndürülür. LED'ler, toggle switch'lerden gelen verilere göre açık veya kapalı durumda yanar veya söner.

//Bu kod, projeniz için bir başlangıç noktası olarak kullanılabilir ve ihtiyaçlarınıza göre özelleştirilebilir.
