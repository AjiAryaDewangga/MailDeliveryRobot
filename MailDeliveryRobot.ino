/*
   contact: ajiaryad@gmail.com
*/
#include "TimerOne.h"
#include <Wire.h>
#include <MechaQMC5883.h>
int x, y, z;
int azimuth;
MechaQMC5883 qmc;
int IN1 = 10; //motor kanan
int IN2 = 11;
int IN3 = 6; //motor kiri
int IN4 = 5;
int kecKn;
int kecKr;
int rotary = 2; //sensor rotary
int hitung;
int tanda = 0;
int surat1, surat2, surat3, surat4, surat5, surat6, plan;

#include <SoftwareSerial.h>
SoftwareSerial SIM800L(3, 4); // RX | TX
char string[160];
char* status1;
char* status2;
char* status3;
char* status4;
char* status5;
char* status6;

void setup() {
  Wire.begin();
  Serial.begin(9600);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(rotary, INPUT);
  qmc.init();
  qmc.setMode(Mode_Continuous, ODR_200Hz, RNG_2G, OSR_256);
  delay(2000);
  plan = 1;
  hitung = 0;
}

void loop() {
  BacaSurat();
  ////////////////////////1
  if (plan == 1) { //menuju ruang 1
    delay(500);
    while (hitung < 40 && plan == 1) {
      utara();
    }
    berhenti();
    hitung = 40;
    delay(500);
    while (hitung < 70 && plan == 1) {
      barat();
    }
    berhenti();
    delay(5000);
    hitung = 0;
    plan = 2;
  }
  ////////////////////////2
  if (plan == 2) {
    delay(500);
    while (hitung < 30 && plan == 2) {
      timur();
    }
    berhenti();
    hitung = 30;
    delay(500);

    //kirim sms
    BacaSurat();
    if (surat1 == 0) status1 = "Berhasil";
    if (surat1 == 1) status1 = "Tidak";
    sprintf(string, "Surat Ruangan 1 %s Terkirim", status1);
    SMS();

    while (hitung < 60 && plan == 2) {
      utara();
    }
    berhenti();
    hitung = 60;
    delay(500);
    while (hitung < 90 && plan == 2) {
      barat();
    }
    berhenti();
    delay(5000);
    hitung = 0;
    plan = 3;
  }
  ////////////////////////3
  if (plan == 3) {
    delay(500);
    while (hitung < 30 && plan == 3) {
      timur();
    }
    berhenti();
    hitung = 30;
    delay(500);

    //kirim sms
    BacaSurat();
    if (surat2 == 0) status2 = "Berhasil";
    if (surat2 == 1) status2 = "Tidak";
    sprintf(string, "Surat Ruangan 2 %s Terkirim", status2);
    SMS();

    while (hitung < 60 && plan == 3) {
      utara();
    }
    berhenti();
    hitung = 60;
    delay(500);
    while (hitung < 90 && plan == 3) {
      barat();
    }
    berhenti();
    delay(5000);
    hitung = 0;
    plan = 4;
  }
  ////////////////////////4
  if (plan == 4) {
    delay(500);
    while (hitung < 30 && plan == 4) {
      timur();
    }
    berhenti();
    delay(500);

    //kirim sms
    BacaSurat();
    if (surat3 == 0) status3 = "Berhasil";
    if (surat3 == 1) status3 = "Tidak";
    sprintf(string, "Surat Ruangan 3 %s Terkirim", status3);
    SMS();

    hitung = 30;
    while (hitung < 60 && plan == 4) {
      timur();
    }
    berhenti();
    delay(5000);
    hitung = 0;
    plan = 5;
  }
  ////////////////////////5
  if (plan == 5) {
    delay(500);
    while (hitung < 30 && plan == 5) {
      barat();
    }
    berhenti();
    hitung = 30;
    delay(500);

    //kirim sms
    BacaSurat();
    if (surat4 == 0) status4 = "Berhasil";
    if (surat4 == 1) status4 = "Tidak";
    sprintf(string, "Surat Ruangan 4 %s Terkirim", status4);
    SMS();

    while (hitung < 60 && plan == 5) {
      selatan();
    }
    berhenti();
    hitung = 65;
    delay(500);
    while (hitung < 90 && plan == 5) {
      timur();
    }
    berhenti();
    delay(5000);
    hitung = 0;
    plan = 6;
  }
  ////////////////////////6
  if (plan == 6) {
    delay(500);
    while (hitung < 30 && plan == 6) {
      barat();
    }
    berhenti();
    hitung = 30;
    delay(500);

    //kirim sms
    BacaSurat();
    if (surat5 == 0) status5 = "Berhasil";
    if (surat5 == 1) status5 = "Tidak";
    sprintf(string, "Surat Ruangan 5 %s Terkirim", status5);
    SMS();

    while (hitung < 60 && plan == 6) {
      selatan();
    }
    berhenti();
    hitung = 60;
    delay(500);
    while (hitung < 90 && plan == 6) {
      timur();
    }
    berhenti();
    delay(5000);
    hitung = 0;
    plan = 7;
  }
  ////////////////////////back
  if (plan == 7) {
    delay(500);
    while (hitung < 30 && plan == 7) {
      barat();
    }
    berhenti();
    hitung = 30;
    delay(500);

    //kirim sms
    BacaSurat();
    if (surat6 == 0) status6 = "Berhasil";
    if (surat6 == 1) status6 = "Tidak";
    sprintf(string, "Surat Ruangan 6 %s Terkirim", status6);
    SMS();

    while (hitung < 70 && plan == 7) {
      selatan();
    }
    berhenti();
    hitung = 70;
    delay(500);
    while (hitung < 75 && plan == 7) {
      utara();
    }
    berhenti();
    delay(5000);
    hitung = 0;
    hasilAkhir();
    plan = 8;

  }
}
void hasilAkhir() {
  BacaSurat();
  if (surat1 == 0 && surat2 == 0 && surat3 == 0 && surat4 == 0 && surat5 == 0 && surat6 == 0) sprintf(string, "Semua Surat Berhasil Terkirim");
  if (surat1 == 1 && surat2 == 1 && surat3 == 1 && surat4 == 1 && surat5 == 1 && surat6 == 1) sprintf(string, "Semua Surat Tidak Terkirim");
  else sprintf(string, "Surat 1 %s, Surat 2 %s, Surat 3 %s, Surat4 %s, Surat 5 %s, Surat 6 %s Diantarkan", status1, status2, status3, status4, status5, status6);
  SMS();
}
void SMS() {
  while (!Serial);
  SIM800L.begin(9600);
  SIM800L.write("AT+CMGF=1\r\n");
  delay(1000);
  SIM800L.write("AT+CMGS=\"08978058010\"\r\n");
  delay(1000);
  SIM800L.write(string);
  delay(1000);
  SIM800L.write((char)26);
  delay(1000);
  Serial.println(string);
}

void jarak() {
  if (digitalRead(rotary) == 1 && tanda == 0) {
    hitung = hitung + 1;
    tanda = 1;
  }
  else if (digitalRead(rotary) == 0 && tanda == 1) {
    tanda = 0;
  }
  //Serial.println(hitung);
}
void barat() {
  compass();
  if (azimuth < 260 && azimuth > 180) kanan();
  if (azimuth > 280 || azimuth < 180) kiri();
  if (azimuth > 260 && azimuth < 280) {
    kecKn = azimuth - 270;
    kecKr = 270 - azimuth;
    maju();
  }
}
void timur() {
  compass();
  if (azimuth < 80 || azimuth > 270) kanan();
  if (azimuth > 100 && azimuth < 270) kiri();
  if (azimuth > 80 && azimuth < 100) {
    kecKn = azimuth - 90;
    kecKr = 90 - azimuth;
    maju();
  }
}
void selatan() {
  compass();
  if (azimuth < 170) kanan();
  if (azimuth > 190) kiri();
  if (azimuth > 170 && azimuth < 190) {
    kecKn = azimuth - 180;
    kecKr = 180 - azimuth;
    maju();
  }
}
void utara() {
  compass();
  if (azimuth > 180 && azimuth < 350) kanan(); // belok kanan
  if (azimuth > 10 && azimuth < 180) kiri(); // belok kiri
  if (azimuth > 350 && azimuth < 361 || azimuth > -1 && azimuth < 10) {
    if (azimuth > -1 && azimuth < 10) {
      azimuth = azimuth + 350;
    }
    kecKn = azimuth - 360;
    kecKr = 360 - azimuth;
    maju();
  }
}
void maju() {
  analogWrite(IN1, 100 + kecKn);
  analogWrite(IN2, 0);
  analogWrite(IN3, 100 + kecKr);
  analogWrite(IN4, 0);
  jarak();
}
void berhenti() {
  analogWrite(IN1, 0);
  analogWrite(IN2, 0);
  analogWrite(IN3, 0);
  analogWrite(IN4, 0);
}
void kanan() {
  analogWrite(IN1, 0);
  analogWrite(IN2, 100);
  analogWrite(IN3, 100);
  analogWrite(IN4, 0);
}
void kiri() {
  analogWrite(IN1, 100);
  analogWrite(IN2, 0);
  analogWrite(IN3, 0);
  analogWrite(IN4, 100);
}
void compass() {
  qmc.read(&x, &y, &z, &azimuth);
  //Serial.print(azimuth);
  //Serial.println();
}
void BacaSurat() {
  int kotak1 = analogRead(A0);
  int kotak2 = analogRead(A1);
  int kotak3 = analogRead(A2);
  int kotak4 = analogRead(A3);
  int kotak5 = digitalRead(12);
  int kotak6 = digitalRead(13);
  delay(10);
  if (kotak1 <= 500) {
    surat1 = 1;
  }
  else {
    surat1 = 0;
  }

  if (kotak2 <= 500) {
    surat2 = 1;
  }
  else {
    surat2 = 0;
  }

  if (kotak3 <= 500) {
    surat3 = 1;
  }
  else {
    surat3 = 0;
  }

  if (kotak4 <= 500) {
    surat4 = 1;
  }
  else {
    surat4 = 0;
  }
  if (kotak5 == 0) {
    surat5 = 1;
  }
  else {
    surat5 = 0;
  }
  if (kotak6 == 0) {
    surat6 = 1;
  }
  else {
    surat6 = 0;
  }
  /*Serial.print("surat1 = ");
    Serial.print(surat1);
      Serial.print(" surat2 = ");
    Serial.print(surat2);
      Serial.print(" surat3= ");
    Serial.print(surat3);
      Serial.print(" surat4 = ");
    Serial.print(surat4);
      Serial.print(" surat5 = ");
    Serial.print(surat5);
      Serial.print(" surat6 = ");
    Serial.println(surat6);*/
}
