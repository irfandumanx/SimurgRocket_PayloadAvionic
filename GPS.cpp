#include "GPS.h"

GPS::GPS(HardwareSerial *serial) {
  this->gps = new Adafruit_GPS(serial);
  gps->begin(9600);
  gps->sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  gps->sendCommand(PMTK_SET_NMEA_UPDATE_10HZ);
  gps->sendCommand(PGCMD_ANTENNA);
  gps->sendCommand(PMTK_Q_RELEASE);
  Serial.println("GPS started succesfully");
  gpsData->latitude = 0.0f;
  gpsData->longitude = 0.0f;
  gpsData->altitude = 0.0f;
  gpsData->satellites = 0;
  tone(27, 10);
  delay(200);
  noTone(27);
  delay(500);
}

void GPS::setSensorData() {
  gps->read();
  if (gps->newNMEAreceived()) {
    if (!gps->parse(gps->lastNMEA()))
    return;
  }
}

GPSData GPS::getSensorData() {
  if (gps->fix) {
    gpsData->altitude = gps->altitude;
    gpsData->longitude = gps->longitudeDegrees;
    gpsData->latitude = gps->latitudeDegrees;
    gpsData->satellites = gps->satellites;
  }else {
    gpsData->altitude = 0.0f;
    gpsData->longitude = 0.0f;
    gpsData->latitude = 0.0f;
    gpsData->satellites = gps->satellites;
  }
  return *gpsData;
}
