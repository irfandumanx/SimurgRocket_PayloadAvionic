#ifndef BME280_H
#define BME280_H
#define SEA_LEVEL_PRESSURE    1015.0f

#include "Arduino.h"
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <SimpleKalmanFilter.h>


typedef struct BME280Data {
  float temperature;
  uint32_t pressure;
  float altitude;
  float humidity;
  float estimated_temp;
  uint32_t estimated_press;
  float estimated_alti;
  float estimated_humidity;
} BME280Data;


class BME280 {
  
  BME280Data *bmeData = (BME280Data*) malloc(sizeof(BME280Data));
  
public:
  BME280();
  Adafruit_BME280 *bme;
  BME280Data getSensorData();
private:
  float firstAltitude;
  void checkError(unsigned eStatus);
};


#endif
