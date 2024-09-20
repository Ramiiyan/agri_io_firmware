#include "SoilMoistureSensor.h"

SoilMoistureSensor::SoilMoistureSensor(int sensorPin) : pin(sensorPin), value(0), percentage(0) {}

void SoilMoistureSensor::read() {
    value = analogRead(pin);
    // Assuming the sensor gives values between 0 (wet) and 1023 (dry)
    percentage = map(value, 1023, 0, 0, 100);
}

int SoilMoistureSensor::getValue() const {
    return value;
}

int SoilMoistureSensor::getPercentage() const {
    return percentage;
}

int SoilMoistureSensor::getPin() const {
    return pin;
}