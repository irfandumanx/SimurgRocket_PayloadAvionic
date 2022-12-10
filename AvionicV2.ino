#include "BME280.h"
#include "GPS.h"
#include "RF.h"
#include <SD.h>
#include <SPI.h>
BME280 *bme;
GPS *gps;
RF *rf;
File avionicFile;
const char* fileName = "PayloadData.txt";
uint32_t timer = 0;

unsigned char buzzerPin = 27;
unsigned char ledPin = 26;
unsigned char teensyLedPin = 13;

void setup() {
  Serial.begin(115200);
  pinMode(teensyLedPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  digitalWrite(ledPin, HIGH);
  digitalWrite(buzzerPin, LOW);
  digitalWrite(teensyLedPin, HIGH);
  bme = new BME280();
  rf = new RF(&Serial5);
  gps = new GPS(&Serial1);
  if (!SD.begin(BUILTIN_SDCARD)) {
    Serial.println("SD initialization failed!");
    return;
  }
  Serial.println("SD initialization done.");
  tone(27, 10);
  delay(200);
  noTone(27);
}

bool phase = false;

void loop() {
  gps->setSensorData();
  if (millis() - timer > 50) {
    BME280Data bmeData = bme->getSensorData();
    GPSData gpsData = gps->getSensorData();
    if(bmeData.estimated_alti > 2000) phase = true;
    if(phase && bmeData.estimated_alti < 200) tone(buzzerPin, 1000);
    rf->sendData(bmeData, gpsData);
    avionicFile = SD.open(fileName, FILE_WRITE);
    if (avionicFile) {
      avionicFile.print(millis() / 1000.0f);
      avionicFile.print("*");
      avionicFile.print(bmeData.estimated_temp);
      avionicFile.print("*");
      avionicFile.print(bmeData.estimated_press);
      avionicFile.print("*");
      avionicFile.print(bmeData.estimated_alti);
      avionicFile.print("*");
      avionicFile.print(bmeData.estimated_humidity);
      avionicFile.print("*");
      //================================================================
      avionicFile.print("*");
      avionicFile.print(gpsData.latitude, 6);
      avionicFile.print("*");
      avionicFile.print(gpsData.longitude, 6);
      avionicFile.print("*");
      avionicFile.print(gpsData.altitude);
      avionicFile.print("*");
      avionicFile.print(gpsData.satellites);
      //================================================================
      avionicFile.println();
      avionicFile.close();
    }
    
    timer = millis();
  }
}
