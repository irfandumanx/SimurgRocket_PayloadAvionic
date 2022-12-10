#include "BME280.h"

SimpleKalmanFilter temperatureKalmanFilter(1.5, 1.5, 0.01);
SimpleKalmanFilter pressureKalmanFilter(1.5, 1.5, 0.01);
SimpleKalmanFilter altitudeKalmanFilter(1.5, 1.5, 0.01);
SimpleKalmanFilter humidityKalmanFilter(1.5, 1.5, 0.01);

BME280::BME280() {
  this->bme = new Adafruit_BME280();
  
  unsigned eStatus = bme->begin();
  Serial.println("BME try read data");
  checkError(eStatus);
  Serial.println("BME begin success");
  tone(27, 10);
  delay(200);
  noTone(27);
  delay(500);
  firstAltitude = bme->readAltitude(SEA_LEVEL_PRESSURE);
}

BME280Data BME280::getSensorData() {
  bmeData->temperature = bme->readTemperature();
  bmeData->pressure = bme->readPressure();
  bmeData->altitude = bme->readAltitude(SEA_LEVEL_PRESSURE) - firstAltitude;
  bmeData->humidity = bme->readHumidity();
  bmeData->estimated_temp = temperatureKalmanFilter.updateEstimate(bmeData->temperature);
  bmeData->estimated_press = pressureKalmanFilter.updateEstimate(bmeData->pressure);
  bmeData->estimated_alti = altitudeKalmanFilter.updateEstimate(bmeData->altitude);
  bmeData->estimated_humidity = humidityKalmanFilter.updateEstimate(bmeData->humidity);
  return *bmeData;
}

void BME280::checkError(unsigned eStatus)
{
  if (!eStatus) {
      Serial.println("Could not find a valid BME280 sensor, check wiring, address, sensor ID!");
      Serial.print("SensorID was: 0x"); Serial.println(bme->sensorID(),16);
      Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
      Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
      Serial.print("        ID of 0x60 represents a BME 280.\n");
      Serial.print("        ID of 0x61 represents a BME 680.\n");
      while (1) delay(10);
  }
}
