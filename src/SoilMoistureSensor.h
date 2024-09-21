#ifndef SOIL_MOISTURE_SENSOR_H
#define SOIL_MOISTURE_SENSOR_H

#include <Arduino.h>

/* 
* Define calibration values for the soil moisture sensor
* These values represent the analog readings for dry and wet soil conditions
*/
#define DRY_ANALOG_VALUE 2574  // Analog reading when soil is completely dry
#define WET_ANALOG_VALUE 1127  // Analog reading when soil is saturated

class SoilMoistureSensor {
private:
    int pin;
    int value;
    double moistPercentage;

public:
    SoilMoistureSensor(int sensorPin);
    void read();
    int getValue() const;
    int getMoistPercentage() const;
    int getPin() const;
};

#endif // SOIL_MOISTURE_SENSOR_H