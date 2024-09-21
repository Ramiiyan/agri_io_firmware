#include <Arduino.h>
#include "SensorManager.h"
#include "MQTTManager.h"

SensorManager sensorManager;
// MQTTManager(const char *broker, const char *pub_topic, const char *sub_topic, const char *username, const char *password, int port); 
MQTTManager mqttManager("broker.emqx.io", "subTopic1","pubTopic1", "emqx", "public", 1883);

// WiFi Credentials
const char *ssid = "Ramiyan";
const char *password = "Alohomora";

void setup() {
  
  // Initialize ESP32 serial communication at 115200 baud rate
  Serial.begin(115200);
  
  // Add sensors to the manager
  // sensorManager.addSensor(32);
  // sensorManager.addSensor(33);
  // sensorManager.addSensor(34);  // ADC1_CH6, not affected by WiFi
  // sensorManager.addSensor(35);  // ADC1_CH7, not affected by WiFi
  // sensorManager.addSensor(36);  // ADC1_CH0, not affected by WiFi
  std::vector<int> sensorPins = {32, 33, 34, 35, 36, 39};
  sensorManager.addSensors(sensorPins);


  // Connect to WiFi and MQTT broker
  mqttManager.connect(ssid, password);
}

void loop() {
  // Read all sensors
  sensorManager.readAllSensors();
  
  // Print results
  sensorManager.printResults();

  char msg[800];
  sensorManager.getJsonData(msg, sizeof(msg));
  mqttManager.publish(msg);
  
  mqttManager.loop();
  
  delay(4000); // Wait for 4 seconds before next reading
}