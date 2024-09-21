#ifndef SENSOR_MANAGER_H
#define SENSOR_MANAGER_H

#include <vector>
#include <ArduinoJson.h>
#include "SoilMoistureSensor.h"

class SensorManager {
private:
    std::vector<SoilMoistureSensor> sensors;

public:
    void addSensor(int pin);
    void addSensors(const std::vector<int>& pins);
    void readAllSensors();
    void printResults();
    void getJsonData(char* buffer, size_t bufferSize);
};

#endif // SENSOR_MANAGER_H