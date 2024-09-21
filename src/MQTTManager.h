#ifndef MQTT_MANAGER_H
#define MQTT_MANAGER_H

#define TINY_GSM_MODEM_SIM7000

#include <PubSubClient.h>
#include <TinyGsmClient.h>

#define BAUD_RATE           115200     // Initialize ESP32 serial communication at 115200 baud rate

// Define SIM module communication parameters
#define SIM_BAUD_RATE       9600       // Baud rate for SIM module communication
#define TXD                 16         // GPIO pin number for UART TX (transmit)
#define RXD                 17         // GPIO pin number for UART RX (receive)


#define GSM_APN             "dialogbb"  // APN for GSM network (e.g., for Dialog Broadband)
#define NB_APN              "nbiot"     // APN for NB-IoT network
#define NETWORK_MODE        13          // Network mode (13 typically represents LTE only mode)


// HardwareSerial SerialSIM(2);
// TinyGsm modem(SerialSIM);
// TinyGsmClient gsmClient(modem);

class MQTTManager {
private:
    HardwareSerial SerialSIM;   // Initialize hardware serial communication
    TinyGsm modem;              // Create a TinyGsm instance
    TinyGsmClient gsmClient;    // Create a TinyGsmClient instance
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
    void initializeModem();
    void connect();
    void loop();
    void publish(const char *message);
    String getCPSI();
};

#endif // MQTT_MANAGER_H