#ifndef SOIL_MOISTURE_SENSOR_H
#define SOIL_MOISTURE_SENSOR_H

#include <Arduino.h>

class SoilMoistureSensor {
private:
    int pin;
    int value;
    int percentage;

public:
    SoilMoistureSensor(int sensorPin);
    void read();
    int getValue() const;
    int getPercentage() const;
    int getPin() const;
};

#endif // SOIL_MOISTURE_SENSOR_H