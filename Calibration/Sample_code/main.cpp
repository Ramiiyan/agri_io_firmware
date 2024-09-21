/*
  ESP32 Soil Moisture Sensor analysis
  Capacitive soil moisture sensor.
  By Ramiyan
*/
// #define MQTT_MAX_PACKET_SIZE 1536
#include <Wire.h>
#include <WiFi.h>
#include <Arduino.h>
#include <PubSubClient.h>


WiFiClient espClient;
PubSubClient client(espClient);


// WiFi
const char *ssid = "Ramiyan";       // Enter your WiFi name
const char *password = "Alohomora"; // Enter WiFi password

// MQTT Broker

const char *mqtt_broker = "broker.emqx.io";
const char *topic = "subTopic";
const char *subTopic = "agrio/Test";
const char *mqtt_username = "emqx";
const char *mqtt_password = "public";
const int mqtt_port = 1883;

// Soil Moisture
#define DRY_ANALOG_VALUE 2574
#define WET_ANALOG_VALUE 1127
const byte ADC_1_Pins[] = {32, 33, 34, 35, 36, 39};
const int sizeOfADC_1_Pins = sizeof(ADC_1_Pins)/sizeof(ADC_1_Pins[0]);
// const int sensorPin = 34; /* Soil moisture sensor Analog O/P pin */
int soilMoistureValue = 0;
int soilMoisturePercent = 0;
char msg[800];
double sensorValues[sizeOfADC_1_Pins];

void callback(char *topic, byte *payload, unsigned int length)
{
  Serial.print("Message arrived in topic: ");
  Serial.println(subTopic);
  Serial.print("Message:");
  for (int i = 0; i < length; i++)
  {
    Serial.print((char)payload[i]);
  }
  Serial.println();
  Serial.println("-----------------------");
}

double getMoistPercentage(int analogValue){
  // Linear Interpolation = (Analog_Value − Dry_Analog_Value) / (Wet_Analog_Value − Dry_Analog_Value)
  Serial.print("analogValue :");
  Serial.println(analogValue);
  double moistPercent = ((double)(analogValue - DRY_ANALOG_VALUE) / (WET_ANALOG_VALUE - DRY_ANALOG_VALUE)) * 100 ;
  if (moistPercent < 0.00 || moistPercent > 101){
    return 0.00;
  }else {
    return moistPercent;
  }

  
}

void publishAgriEvent(double sensorValues[])
{

  // Sample Format
  const char *dataFormat = "[{\"sensorId\":\"09d71ad2a4e5d7ae\",\"sensorName\":\"S01\",\"type\":\"Soil Moisture\",\"sensorValue\": %.2f,\"sensorPin\":32},{\"sensorId\":\"18a7abfe508873e9\",\"sensorName\":\"S02\",\"type\":\"Soil Moisture\",\"sensorValue\":%.2f,\"sensorPin\":33},{\"sensorId\":\"2455fae40858f430\",\"sensorName\":\"S03\",\"type\":\"Soil Moisture\",\"sensorValue\":%.2f,\"sensorPin\":34},{\"sensorId\":\"4f79cfc02c4d27f5\",\"sensorName\":\"S04\",\"type\":\"Soil Moisture\",\"sensorValue\":%.2f,\"sensorPin\":35},{\"sensorId\":\"06bcf011b1701d98\",\"sensorName\":\"S05\",\"type\":\"Soil Moisture\",\"sensorValue\":%.2f,\"sensorPin\":36},{\"sensorId\":\"ea8cc975cfc9353c\",\"sensorName\":\"S06\",\"type\":\"Soil Moisture\",\"sensorValue\":%.2f,\"sensorPin\":39}]";
  // Set the payload to publish.
  sprintf(msg, dataFormat, sensorValues[0], sensorValues[1], sensorValues[2], sensorValues[3], sensorValues[4], sensorValues[5]);

  // Serial.println(F(msg));
  // publish Event
  //client.publish(topic, msg);
  // char test[800] = "[{\"sensorId\":\"09d71ad2a4e5d7ae\",\"sensorName\":\"S01\",\"type\":\"Soil Moisture\",\"sensorValue\":75.03,\"sensorPin\":32},{\"sensorId\":\"18a7abfe508873e9\",\"sensorName\":\"S02\",\"type\":\"Soil Moisture\",\"sensorValue\":78.03,\"sensorPin\":33},,{\"sensorId\":\"2455fae40858f430\",\"sensorName\":\"S03\",\"type\":\"Soil Moisture\",\"sensorValue\":54.92,\"sensorPin\":34}]";
  // Serial.println(F(test));
  if (!client.publish(topic, msg))
  {
    Serial.println(F("Failed."));
  }
  else
  {
    Serial.print(msg);
    Serial.println(F(" :SEND:OK"));
  }
}

void setup(void)
{
  Serial.begin(115200); /* Set the baudrate to 115200*/

  // connecting to a WiFi network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");

  // connecting to a mqtt broker
  client.setServer(mqtt_broker, mqtt_port);
  client.setCallback(callback);
  client.setBufferSize(1024);
  while (!client.connected())
  {

    String client_id = "TEST-" + String(millis()) + String(random(0, 100000000), HEX);
    Serial.printf("The client %s connects to the public mqtt broker\n", client_id.c_str());

    if (client.connect(client_id.c_str(), mqtt_username, mqtt_password))
    {
      Serial.println("Public emqx mqtt broker connected");
    }
    else
    {
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
    }
  }
  Serial.println();
  // publish and subscribe
  // client.publish(topic, "Hi EMQX I'm ESP32 ^^");
  client.subscribe(subTopic);
}

void loop()
{
  client.loop();
   char strBuf[20];
   for(int i=0; i < sizeof(ADC_1_Pins)/sizeof(ADC_1_Pins[0]); i++){
  
    //  sprintf(strBuf, "Pin %d : %d", ADC_1_Pins[i], analogRead(ADC_1_Pins[i]) );
    //  Serial.println(strBuf);
    int analogSensorVal = analogRead(ADC_1_Pins[i]);
    sensorValues[i] = getMoistPercentage(analogSensorVal);
    Serial.print("Moist: ");
    Serial.println( sensorValues[i]);

   }
  //  Serial.println(soilMoistureValue);
  //  soilMoisturePercent=map(soilMoistureValue, AirValue, WaterValue, 0, 100);
  //  Serial.print("Soil Moist % = ");
  //  Serial.println(soilMoisturePercent);

  // Set the payload to publish.
  //  sprintf(msg, "{\"moisture\":%d,\"unit\": \"%\"}");

  // publish Event
   publishAgriEvent(sensorValues);
   delay(3000);              /* Wait for 3000mS */
}




