/*
  ESP32 Soil Moisture Sensor analysis
  Capacitive soil moisture sensor.
  By Ramiyan
*/
#include <Wire.h>
#include <WiFi.h>
#include <PubSubClient.h>

WiFiClient espClient;
PubSubClient client(espClient);

// WiFi
const char *ssid = "Ramiyan"; // Enter your WiFi name
const char *password = "Alohomora";  // Enter WiFi password

// MQTT Broker
const char *mqtt_broker = "broker.emqx.io";
const char *topic = "Agri_IO/Dev/Test/D1";
const char *mqtt_username = "emqx";
const char *mqtt_password = "public";
const int mqtt_port = 1883;


// Soil Moisture
const int AirValue = 2900;
const int WaterValue = 1015;
int ADC_1_Pins[] = {32,33,34,35,36,39};

const int sensorPin = 34;  /* Soil moisture sensor Analog O/P pin */
int soilMoistureValue = 0;
int soilMoisturePercent = 0;
char msg[50];

void setup(void){
    Serial.begin(115200);     /* Set the baudrate to 115200*/
    
    // connecting to a WiFi network
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
  
  //connecting to a mqtt broker
  client.setServer(mqtt_broker, mqtt_port);
  client.setCallback(callback);
  while (!client.connected()) {
     
     String client_id = "TEST-" + String(millis()) + String(random(0, 100000000), HEX);
     Serial.printf("The client %s connects to the public mqtt broker\n", client_id.c_str());
     
     if (client.connect(client_id.c_str(), mqtt_username, mqtt_password)) {
         Serial.println("Public emqx mqtt broker connected");
     } else {
         Serial.print("failed with state ");
         Serial.print(client.state());
         delay(2000);
     }
  }
  Serial.println();
  // publish and subscribe
  client.publish(topic, "Hi EMQX I'm ESP32 ^^");
  client.subscribe(topic);
}

void loop(){
  client.loop();
//  char strBuf[20];
//  for(int i=0; i < ADC_1_Pins.length(); i++){
//    
//    sprintf(strBuf, "Pin %d : %d", ADC_1_Pins[i], analogRead(ADC_1_Pins[i]) );
//    Serial.println(strBuf);
// 
//  }

//  Serial.println(soilMoistureValue);
//  soilMoisturePercent=map(soilMoistureValue, AirValue, WaterValue, 0, 100);
//  Serial.print("Soil Moist % = ");
//  Serial.println(soilMoisturePercent);
  

  //Set the payload to publish.
  //sprintf(msg, "{\"moisture\":%d,\"unit\": \"%\"}");

  // publish Event
  //publishAgriEvent(_moisture);
//  delay(1000);              /* Wait for 3000mS */
}

void callback(char *topic, byte *payload, unsigned int length) {
 Serial.print("Message arrived in topic: ");
 Serial.println(topic);
 Serial.print("Message:");
 for (int i = 0; i < length; i++) {
     Serial.print((char) payload[i]);
 }
 Serial.println();
 Serial.println("-----------------------");
}

void publishAgriEvent(int mois){
  //Set the payload to publish.
  sprintf(msg, "{\"moisture\":%d,\"unit\": \"%%\"}", mois);

  // publish Event
  //client.publish(topic, msg);
  if (!client.publish(topic, msg)){
    Serial.println(F("Failed."));
  }else{
    Serial.print(msg);
    Serial.println(F(" :SEND:OK"));
  }
}
