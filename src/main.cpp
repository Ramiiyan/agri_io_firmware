#include <Arduino.h>
#include "SensorManager.h"

SensorManager sensorManager;

void setup() {
  Serial.begin(115200);
  
  // Add sensors to the manager
  sensorManager.addSensor(32);
  sensorManager.addSensor(33);
  sensorManager.addSensor(34);  // ADC1_CH6, not affected by WiFi
  sensorManager.addSensor(35);  // ADC1_CH7, not affected by WiFi
  sensorManager.addSensor(36);  // ADC1_CH0, not affected by WiFi
  
  // Add more sensors as needed
}

void loop() {
  // Read all sensors
  sensorManager.readAllSensors();
  
  // Print results
  sensorManager.printResults();
  
  delay(5000); // Wait for 5 seconds before next reading
}