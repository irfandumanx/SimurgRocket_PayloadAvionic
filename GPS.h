#ifndef GPS_H
#define GPS_H
#include "Arduino.h"
#include <Adafruit_GPS.h>
#include <SimpleKalmanFilter.h>

typedef struct GPSData {
  nmea_float_t latitude;
  nmea_float_t longitude;
  nmea_float_t altitude;
  uint8_t satellites;
} GPSData;


class GPS {
  
  GPSData *gpsData = (GPSData*) malloc(sizeof(GPSData));
  
public:
  GPS(HardwareSerial *serial);
  Adafruit_GPS *gps;
  GPSData getSensorData();
  void setSensorData();
private:

};

#endif
