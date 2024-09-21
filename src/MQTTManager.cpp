#include "MQTTManager.h"

MQTTManager::MQTTManager(const char *broker, const char *pub_topic, const char *sub_topic, const char *username, const char *password, int port)
    : client(espClient), mqtt_broker(broker), pub_topic(pub_topic), sub_topic(sub_topic), mqtt_username(username), mqtt_password(password), mqtt_port(port) {
    client.setServer(mqtt_broker, mqtt_port);
    client.setCallback(callback);
    client.setBufferSize(1024);
}

void MQTTManager::connect(const char *ssid, const char *password) {
    // Connect to WiFi
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.println("Connecting to WiFi..");
    }
    Serial.println("Connected to the WiFi network");

    // Connect to MQTT broker
    while (!client.connected()) {
        String client_id = "ESP32-" + String(millis());
        Serial.printf("The client %s connects to the public mqtt broker\n", client_id.c_str());
        if (client.connect(client_id.c_str(), mqtt_username, mqtt_password)) {
            Serial.println("Public emqx mqtt broker connected");
        } else {
            Serial.print("failed with state ");
            Serial.print(client.state());
            delay(2000);
        }
    }

    // Publish and subscribe
    client.publish(pub_topic, "Hi EMQX I'm ESP32 ^^");
    client.subscribe(sub_topic);
}

void MQTTManager::loop() {
    client.loop();
}

void MQTTManager::publish(const char *message) {
    if (!client.publish(pub_topic, message)) {
        Serial.println(F("Failed to publish."));
    } else {
        Serial.print(message);
        Serial.println(F(" :SEND:OK"));
    }
}

void MQTTManager::callback(char *topic, byte *payload, unsigned int length) {
    Serial.print("Message arrived in topic: ");
    Serial.println(topic);
    Serial.print("Message:");
    for (int i = 0; i < length; i++) {
        Serial.print((char) payload[i]);
    }
    Serial.println();
    Serial.println("-----------------------");
}