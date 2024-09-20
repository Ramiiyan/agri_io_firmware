#ifndef SENSOR_MANAGER_H
#define SENSOR_MANAGER_H

#include <vector>
#include "SoilMoistureSensor.h"

class SensorManager {
private:
    std::vector<SoilMoistureSensor> sensors;

public:
    void addSensor(int pin);
    void readAllSensors();
    void printResults();
};

#endif // SENSOR_MANAGER_H