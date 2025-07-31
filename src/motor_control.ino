#include <Arduino.h>
#include <AFMotor.h>

// Motor tanımları
AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

// Gelen komut
char command;
int speedValue;

void setup() {
  Serial.begin(9600);
  Serial.println("Komut bekleniyor (ornegin: f 200)");
}

void loop() {
  if (Serial.available()) {
    command = Serial.read();               // İlk karakteri oku (komut)
    speedValue = Serial.parseInt();        // Sayı değerini oku (hız)

    ApplyCommand(command, speedValue);     // Komutu uygula
  }
}

void ApplyCommand(char cmd, int spd) {
  spd = constrain(spd, 0, 255);            // Hızı sınırla
  SetSpeed(spd);

  switch (cmd) {
    case 'f':
      Serial.print("Ileri gidiliyor. Hiz: ");
      Serial.println(spd);
      Move_Forward();
      break;
    case 'b':
      Serial.print("Geri gidiliyor. Hiz: ");
      Serial.println(spd);
      Move_Backward();
      break;
    case 'l':
      Serial.print("Sola donuluyor. Hiz: ");
      Serial.println(spd);
      Move_Left();
      break;
    case 'r':
      Serial.print("Saga donuluyor. Hiz: ");
      Serial.println(spd);
      Move_Right();
      break;
    case 's':
      Serial.println("Duruldu.");
      Move_Release();
      break;
    default:
      Serial.println("Gecersiz komut.");
      break;
  }
}

void SetSpeed(int spd) {
  motor1.setSpeed(spd);
  motor2.setSpeed(spd);
  motor3.setSpeed(spd);
  motor4.setSpeed(spd);
}

void Move_Forward() {
  motor1.run(FORWARD); motor2.run(FORWARD);
  motor3.run(FORWARD); motor4.run(FORWARD);
}

void Move_Backward() {
  motor1.run(BACKWARD); motor2.run(BACKWARD);
  motor3.run(BACKWARD); motor4.run(BACKWARD);
}

void Move_Left() {
  motor1.run(FORWARD); motor2.run(FORWARD);
  motor3.run(BACKWARD); motor4.run(BACKWARD);
}

void Move_Right() {
  motor1.run(BACKWARD); motor2.run(BACKWARD);
  motor3.run(FORWARD); motor4.run(FORWARD);
}

void Move_Release() {
  motor1.run(RELEASE); motor2.run(RELEASE);
  motor3.run(RELEASE); motor4.run(RELEASE);
}