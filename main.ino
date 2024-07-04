/*
 *   Çift Kanallı DC Motor ile çizgi izleyen robot örneği,
 *   
 *  
 *   
 *
 *   Bu algılayıcı I2C haberleşme protokolü ile çalışmaktadır.
 *
 *  
 *      ------>  https://docs.deneyapkart.org/tr/content/contentDetail/deneyap-module-deneyap-dual-channel-motor-driver-m  <------
 *      ------>  https://github.com/deneyapkart/deneyap-cift-kanalli-motor-surucu-arduino-library  <------ 
*/

#include <Deneyap_CiftKanalliMotorSurucu.h>         // Deneyap Çift Kanallı Motor Sürücü kütüphanesi eklenmesi

DualMotorDriver MotorDriver;                        // DualMotorDriver için sınıf tanımlanması

// Çizgi izleyen robotun dijital pinlerin tanımlanması
const int digitalPin0 = D7; 
const int digitalPin1 = D6;
const int digitalPin2 = D5;

void setup() {
  Serial.begin(115200);                             // Seri haberleşmenin başlatılması

  // I2C bağlantısının başlatılması ve kontrol edilmesi
  if (!MotorDriver.begin(0x16)) {                   // begin(slaveAdress) fonksiyonu ile cihazların haberleşmesi başlatılması
     // delay(3000);
      Serial.println("I2C bağlantısı başarısız");   // I2C bağlantısı başarısız olursa seri port ekranına yazdırılması
      while (1);                                    // Bağlantı başarısızsa sonsuz döngü
  } 
}

void loop() {
  // Dijital pinlerin okunması
  int digitalValue0 = digitalRead(digitalPin0);
  int digitalValue1 = digitalRead(digitalPin1);
  int digitalValue2 = digitalRead(digitalPin2);



  // Motor hatasının kontrol edilmesi
  if (MotorDriver.CheckMotorError() == 1) {
    Serial.println("HATA !!! Lütfen motorları kontrol edin");
  }

  // Motor sürücü kontrolü
  motorControl(digitalValue0, digitalValue1, digitalValue2);
}

// Motor sürücü kontrol fonksiyonu
void motorControl(int value0, int value1, int value2) {
  if (value2 == 1) {
    MotorDriver.MotorDrive(MOTOR1, 0, 1);           

    MotorDriver.MotorDrive(MOTOR2, 45, 0);           // 2. motor %45 dutycycle ile ileri yönde çalıştırılması
  }
  else if (value1 == 1 && value0 == 0 && value2 == 0) {
    MotorDriver.MotorDrive(MOTOR1, 35, 1);           // 1. motor %35 dutycycle ile geri yönde çalıştırılması
    MotorDriver.MotorDrive(MOTOR2, 35, 0);           // 2. motor %35 dutycycle ile ileri yönde çalıştırılması
    
    delay(2);
  }
  else if (value1 == 0 && value0 == 0 && value2 == 0) {
    MotorDriver.MotorDrive(MOTOR1, 30, 1);           // 1. motor %30 dutycycle ile geri yönde çalıştırılması
    MotorDriver.MotorDrive(MOTOR2, 30, 0);           // 2. motor %30 dutycycle ile ileri yönde çalıştırılması
    delay(2);
  }
  else if (value0 == 1) {
    MotorDriver.MotorDrive(MOTOR1, 45, 1);           // 1. motor %45 dutycycle ile geri yönde çalıştırılması
    MotorDriver.MotorDrive(MOTOR2, 0, 0);           
  }
}
