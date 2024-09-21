#include "SoilMoistureSensor.h"

SoilMoistureSensor::SoilMoistureSensor(int sensorPin) : pin(sensorPin), value(0), moistPercentage(0) {}

void SoilMoistureSensor::read() {
    value = analogRead(pin);
    
    moistPercentage = ((double)(value - DRY_ANALOG_VALUE) / (WET_ANALOG_VALUE - DRY_ANALOG_VALUE)) * 100 ;
}

int SoilMoistureSensor::getValue() const {
    return value;
}

int SoilMoistureSensor::getMoistPercentage() const {

    if (moistPercentage < 0.00 || moistPercentage > 101){
        return 0.00;
    }else {
        return moistPercentage;
    }

}

int SoilMoistureSensor::getPin() const {
    return pin;
}