#ifndef MQTT_MANAGER_H
#define MQTT_MANAGER_H

#include <WiFi.h>
#include <PubSubClient.h>

class MQTTManager {
private:
    WiFiClient espClient;
    PubSubClient client;
    const char *mqtt_broker;
    const char *pub_topic;
    const char *sub_topic;
    const char *mqtt_username;
    const char *mqtt_password;
    int mqtt_port;

    static void callback(char *topic, byte *payload, unsigned int length);

public:
    MQTTManager(const char *broker, const char *pub_topic, const char *sub_topic, const char *username, const char *password, int port);
    void connect(const char *ssid, const char *password);
    void loop();
    void publish(const char *message);
};

#endif // MQTT_MANAGER_H