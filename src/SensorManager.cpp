#include "SensorManager.h"
#include <Arduino.h>

void SensorManager::addSensor(int pin) {
    sensors.emplace_back(pin);
}
void SensorManager::addSensors(const std::vector<int>& pins) {
    for (int pin : pins) {
        addSensor(pin);
    }
}


void SensorManager::readAllSensors() {
    for (auto& sensor : sensors) {
        sensor.read();
    }
}

void SensorManager::printResults() {
    for (size_t i = 0; i < sensors.size(); ++i) {
        Serial.print(F("Sensor pin "));
        Serial.print(sensors[i].getPin());
        Serial.print(F(": "));
        Serial.print(sensors[i].getValue());
        Serial.print(F(" ("));
        Serial.print(sensors[i].getMoistPercentage());
        Serial.println(F("%)"));
    }
    Serial.println();
}

void SensorManager::getJsonData(char* buffer, size_t bufferSize) {
    // Create a JSON array to hold our sensor objects
    JsonDocument doc; // Adjust size as needed
    JsonArray sensorArray = doc.to<JsonArray>();

    // Sensor IDs and names (you might want to store these elsewhere)
    const char* sensorIds[] = {
        "09d71ad2a4e5d7ae", "18a7abfe508873e9", "2455fae40858f430",
        "4f79cfc02c4d27f5", "06bcf011b1701d98", "ea8cc975cfc9353c"
    };

    // Iterate through all sensors
    for (size_t i = 0; i < sensors.size(); ++i) {
        JsonObject sensorObj = sensorArray.createNestedObject();
        sensorObj["sensorId"] = i < 6 ? sensorIds[i] : String("sensor") + String(i);
        sensorObj["sensorName"] = String("S0") + String(i + 1);
        sensorObj["type"] = "Soil Moisture";
        sensorObj["sensorValue"] = sensors[i].getMoistPercentage();
        sensorObj["sensorPin"] = sensors[i].getPin();
    }

    // Serialize JSON to buffer
    serializeJson(doc, buffer, bufferSize);
}

// void SensorManager::getJsonData(char* buffer, size_t bufferSize) {
//     const char* dataFormat = "[{"
//         "\"sensorId\":\"09d71ad2a4e5d7ae\",\"sensorName\":\"S01\",\"type\":\"Soil Moisture\",\"sensorValue\":%.2f,\"sensorPin\":%d"
//     "},{" 
//         "\"sensorId\":\"18a7abfe508873e9\",\"sensorName\":\"S02\",\"type\":\"Soil Moisture\",\"sensorValue\":%.2f,\"sensorPin\":%d"
//     "},{" 
//         "\"sensorId\":\"2455fae40858f430\",\"sensorName\":\"S03\",\"type\":\"Soil Moisture\",\"sensorValue\":%.2f,\"sensorPin\":%d"
//     "},{" 
//         "\"sensorId\":\"4f79cfc02c4d27f5\",\"sensorName\":\"S04\",\"type\":\"Soil Moisture\",\"sensorValue\":%.2f,\"sensorPin\":%d"
//     "},{" 
//         "\"sensorId\":\"06bcf011b1701d98\",\"sensorName\":\"S05\",\"type\":\"Soil Moisture\",\"sensorValue\":%.2f,\"sensorPin\":%d"
//     "},{" 
//         "\"sensorId\":\"ea8cc975cfc9353c\",\"sensorName\":\"S06\",\"type\":\"Soil Moisture\",\"sensorValue\":%.2f,\"sensorPin\":%d"
//     "}]";

//     // Method to format sensor data as JSON
//     snprintf(buffer, bufferSize, dataFormat,
//         sensors[0].getMoistPercentage(), sensors[0].getPin(),
//         sensors[1].getMoistPercentage(), sensors[1].getPin(),
//         sensors[2].getMoistPercentage(), sensors[2].getPin(),
//         sensors[3].getMoistPercentage(), sensors[3].getPin(),
//         sensors[4].getMoistPercentage(), sensors[4].getPin(),
//         sensors[5].getMoistPercentage(), sensors[5].getPin()
//     );
// }