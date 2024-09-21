#include "MQTTManager.h"

MQTTManager::MQTTManager(const char *broker, const char *pub_topic, const char *sub_topic, const char *username, const char *password, int port)
    : SerialSIM(2), modem(SerialSIM), gsmClient(modem), client(gsmClient), mqtt_broker(broker), pub_topic(pub_topic), sub_topic(sub_topic), mqtt_username(username), mqtt_password(password), mqtt_port(port) {
    client.setServer(mqtt_broker, mqtt_port);
    client.setCallback(callback);
    client.setBufferSize(1024);
}

void MQTTManager::initializeModem() {
    Serial.begin(BAUD_RATE);
    delay(10);
    Serial.println("setup begin...");
    
    SerialSIM.begin(SIM_BAUD_RATE, SERIAL_8N1, (int8_t) RXD, (int8_t) TXD);
    modem.setNetworkMode(NETWORK_MODE); // 38-nbiot 13-gsm
    //modem.setPreferredMode(2);  // only for nbiot
    modem.getModemName();
    Serial.println(modem.getModemInfo());
    Serial.println(modem.getIMEI());
    modem.restart();
    delay(2000);
    Serial.println(F("Finding Network..."));
    if (!modem.waitForNetwork()) {
        Serial.println(F("Network Fail"));
        while (true);
    } else {
        Serial.println(F("Network identified."));
        Serial.print(F("Signal Strength : "));
        Serial.println(modem.getSignalQuality());
        
        if (!modem.gprsConnect(GSM_APN, "", "")) {
            Serial.println(F("GPRS Fail"));
        } else {
            Serial.println(F("GPRS Connected."));
            Serial.println(getCPSI());
            // The client is already set up in the constructor, so we don't need to set it again here
        }
    }
}

void MQTTManager::connect() {

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

String MQTTManager::getCPSI(){
    String cpsi;
    SerialSIM.println("AT+CPSI?");
    delay(500);
    while (SerialSIM.available()){
        cpsi = SerialSIM.readString();
    }
    delay(500);
    return cpsi;
}
