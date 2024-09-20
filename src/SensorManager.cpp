#include "SensorManager.h"
#include <Arduino.h>

void SensorManager::addSensor(int pin) {
    sensors.emplace_back(pin);
}

void SensorManager::readAllSensors() {
    for (auto& sensor : sensors) {
        sensor.read();
    }
}

void SensorManager::printResults() {
    for (size_t i = 0; i < sensors.size(); ++i) {
        Serial.print("Sensor on pin ");
        Serial.print(sensors[i].getPin());
        Serial.print(": ");
        Serial.print(sensors[i].getValue());
        Serial.print(" (");
        Serial.print(sensors[i].getPercentage());
        Serial.println("%)");
    }
    Serial.println();
}