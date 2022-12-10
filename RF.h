#ifndef RF_H
#define RF_H
#include "Arduino.h"
#include "BME280.h"
#include "GPS.h"

class RF {
  
public:
  HardwareSerial *serial;
  RF(HardwareSerial *serial);
  void sendData(BME280Data bmeData, GPSData gpsData);
private:
  uint8_t calculateParityByte(BME280Data bmeData, GPSData gpsData);
};

#endif
