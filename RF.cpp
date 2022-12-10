#include "RF.h"

RF::RF(HardwareSerial *serial) {
  this->serial = serial;
  this->serial->begin(57600);
}

uint8_t RF::calculateParityByte(BME280Data bmeData, GPSData gpsData) {
  float sum = 0.0f;
  
  sum += bmeData.temperature;
  sum += bmeData.humidity;
  sum += bmeData.altitude;
  sum += gpsData.latitude;
  sum += gpsData.longitude;
  sum += gpsData.altitude;

  return (uint8_t) sum % 256;
}

void RF::sendData(BME280Data bmeData, GPSData gpsData){
  serial->print("!");
  serial->print(bmeData.estimated_temp);
  serial->print("*");
  serial->print(bmeData.estimated_alti);
  serial->print("*");
  serial->print(bmeData.estimated_humidity);
  //================================================================
  serial->print("*");
  serial->print(gpsData.latitude, 6);
  serial->print("*");
  serial->print(gpsData.longitude, 6);
  serial->print("*");
  serial->print(gpsData.altitude);
  serial->print("*");
  serial->print(calculateParityByte(bmeData, gpsData));
  serial->print("|");
}
