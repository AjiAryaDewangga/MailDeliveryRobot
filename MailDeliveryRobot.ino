/*
   contact: ajiaryad@gmail.com
*/
#include <SoftwareSerial.h>
SoftwareSerial SIM800L(2, 3); // RX | TX
#include <Ultrasonic.h>
Ultrasonic ultrasonic(13, 12); // (Trig PIN,Echo PIN)
#include <L298N.h>
#define ENA 6
#define IN1 8
#define IN2 7
#define ENB 11
#define IN3 9
#define IN4 10
#include <Wire.h>
#include <MechaQMC5883.h>
MechaQMC5883 qmc;
int rotary = 5;
int hitung;
int tanda = 0;
int azimuth;
int surat1;
int surat2;
int surat3;
int surat4;
int surat5;
int surat6;
int plan;
L298N motorkiri(ENA, IN1, IN2);
L298N motorkanan(ENB, IN3, IN4);


void SMS() {
  while (!Serial);
  SIM800L.begin(9600);
  SIM800L.write("AT+CMGF=1\r\n");
  delay(1000);
  SIM800L.write("AT+CMGS=\"081547476888\"\r\n");
  delay(1000);
  SIM800L.write("Surat Berhasil Diantarkan");
  delay(1000);
  SIM800L.write((char)26);
  delay(1000);
  Serial.println("SMS Selesai Dikirim!");
}

void kompas() {
  int x, y, z;
  qmc.read(&x, &y, &z, &azimuth);
  Serial.print("x: ");
  Serial.print(x);
  Serial.print(" y: ");
  Serial.print(y);
  Serial.print(" z: ");
  Serial.print(z);
  Serial.print(" a: ");
  Serial.print(azimuth);
  Serial.println();
}

void jarak() {
  if (digitalRead(rotary) == 1 && tanda == 0) {
    hitung = hitung + 1;
    tanda = 1;
  }
  else if (digitalRead(rotary) == 0 && tanda == 1) {
    tanda = 0;
  }
}

void berhenti() {
  motorkanan.stop();
  motorkiri.stop();
}

void selatan() {
  if (azimuth >= 178 && azimuth <= 182) {
    motorkanan.setSpeed(100);
    motorkiri.setSpeed(100);
    motorkanan.forward();
    motorkiri.forward();
  }
  else if (azimuth <= 177 && azimuth >= 160) {
    motorkanan.setSpeed(80);
    motorkiri.setSpeed(120);
    motorkanan.forward();
    motorkiri.forward();
  }
  else if (azimuth <= 160 && azimuth >= 145) {
    motorkanan.setSpeed(0);
    motorkiri.setSpeed(120);
    motorkanan.forward();
    motorkiri.forward();
  }
  else if (azimuth < 145) {
    motorkanan.setSpeed(0);
    motorkiri.setSpeed(150);
    motorkanan.forward();
    motorkiri.forward();
  }
  else if (azimuth >= 183 && azimuth <= 200) {
    motorkanan.setSpeed(120);
    motorkiri.setSpeed(80);
    motorkanan.forward();
    motorkiri.forward();
  }
  else if (azimuth >= 200 && azimuth <= 215) {
    motorkanan.setSpeed(120);
    motorkiri.setSpeed(0);
    motorkanan.forward();
    motorkiri.forward();
  }
  else if (azimuth > 215) {
    motorkanan.setSpeed(150);
    motorkiri.setSpeed(0);
    motorkanan.forward();
    motorkiri.forward();
  }
}

void barat()
{
  if (azimuth >= 265 && azimuth <= 275) {
    motorkanan.setSpeed(100);
    motorkiri.setSpeed(100);
    motorkanan.forward();
    motorkiri.forward();
  }
  else if (azimuth <= 265 && azimuth >= 260) {
    motorkanan.setSpeed(80);
    motorkiri.setSpeed(120);
    motorkanan.forward();
    motorkiri.forward();
  }
  else if (azimuth <= 260 && azimuth >= 250) {
    motorkanan.setSpeed(0);
    motorkiri.setSpeed(120);
    motorkanan.forward();
    motorkiri.forward();
  }
  else if (azimuth < 250) {
    motorkanan.setSpeed(0);
    motorkiri.setSpeed(150);
    motorkanan.forward();
    motorkiri.forward();
  }
  else if (azimuth >= 275 && azimuth <= 280) {
    motorkanan.setSpeed(120);
    motorkiri.setSpeed(80);
    motorkanan.forward();
    motorkiri.forward();
  }
  else if (azimuth >= 280 && azimuth <= 290) {
    motorkanan.setSpeed(120);
    motorkiri.setSpeed(0);
    motorkanan.forward();
    motorkiri.forward();
  }
  else if (azimuth > 290) {
    motorkanan.setSpeed(150);
    motorkiri.setSpeed(0);
    motorkanan.forward();
    motorkiri.forward();
  }
}

void timur()
{
  if (azimuth >= 85 && azimuth <= 95) {
    motorkanan.setSpeed(100);
    motorkiri.setSpeed(100);
    motorkanan.forward();
    motorkiri.forward();
  }
  else if (azimuth <= 85 && azimuth >= 80) {
    motorkanan.setSpeed(80);
    motorkiri.setSpeed(120);
    motorkanan.forward();
    motorkiri.forward();
  }
  else if (azimuth <= 80 && azimuth >= 70) {
    motorkanan.setSpeed(0);
    motorkiri.setSpeed(120);
    motorkanan.forward();
    motorkiri.forward();
  }
  else if (azimuth < 70) {
    motorkanan.setSpeed(0);
    motorkiri.setSpeed(150);
    motorkanan.forward();
    motorkiri.forward();
  }
  else if (azimuth >= 95 && azimuth <= 100) {
    motorkanan.setSpeed(120);
    motorkiri.setSpeed(80);
    motorkanan.forward();
    motorkiri.forward();
  }
  else if (azimuth >= 100 && azimuth <= 110) {
    motorkanan.setSpeed(120);
    motorkiri.setSpeed(0);
    motorkanan.forward();
    motorkiri.forward();
  }
  else if (azimuth > 110) {
    motorkanan.setSpeed(150);
    motorkiri.setSpeed(0);
    motorkanan.forward();
    motorkiri.forward();
  }
}

void setup() {
  Serial.begin(9600);
  Serial.println("SISTEM DIMULAI");
  Wire.begin();
  qmc.init();
  pinMode(rotary, INPUT);
  delay(2000);
}


void loop() {
  BacaSurat();
  kompas();
  jarak();

  //Running Awal
  if (hitung <= 5 && ultrasonic.Ranging(CM) >= 15 && surat1 == 1) {
    selatan();
    plan = 1;
  }
  //Menuju Ruang 1
  else if (ultrasonic.Ranging(CM) >= 15 && surat1 == 1 && plan == 1) {
    kompas();
    barat();
  }
  else if (ultrasonic.Ranging(CM) <= 15 && surat1 == 1 && plan == 1) {
    berhenti();
    kompas();
    hitung = 0;
  }
  //Menuju Ruang 2
  else if (hitung <= 10 && ultrasonic.Ranging(CM) <= 15 && surat1 == 0 && plan == 1) {
    kompas();
    timur();
    plan = 2;
  }
  else if (ultrasonic.Ranging(CM) >= 15 && surat1 == 0 && plan == 2) {
    kompas();
    timur();
  }
  else if (hitung >= 10 && ultrasonic.Ranging(CM) <= 15 && surat1 == 0 && surat2 == 1 && plan == 2) {
    berhenti();
    kompas();
    hitung = 0;
  }
  //Menuju Ruang 3
  else if (hitung <= 10 && ultrasonic.Ranging(CM) <= 15 && surat1 == 0 && surat2 == 0 && plan == 2) {
    kompas();
    barat();
    plan = 3;
  }
  else if (ultrasonic.Ranging(CM) >= 15 && surat2 == 0 && plan == 3) {
    kompas();
    barat();
  }
  else if (hitung >= 10 && ultrasonic.Ranging(CM) <= 15 && surat2 == 0 && plan == 3) {
    berhenti();
    kompas();
    SMS();
  }

}


void BacaSurat() {
  int kotak1 = analogRead(A0);
  int kotak2 = analogRead(A1);
  int kotak3 = analogRead(A2);
  int kotak4 = analogRead(A3);
  int kotak5 = analogRead(A4);
  int kotak6 = analogRead(A5);
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

  if (kotak5 <= 500) {
    surat5 = 1;
  }
  else {
    surat5 = 0;
  }

  if (kotak6 <= 500) {
    surat6 = 1;
  }
  else {
    surat6 = 0;
  }
  Serial.println(surat1);
  delay(10);
}

