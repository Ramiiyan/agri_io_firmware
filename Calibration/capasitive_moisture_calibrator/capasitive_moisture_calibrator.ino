/*
  ESP32 Soil Moisture Sensor Calibrator
  Capacitive soil moisture sensor.
  By Ramiyan
*/



// Soil Moisture
const int AirValue = 2900;
const int WaterValue = 1015;
int ADC_1_Pins[] = {32,33,34,35,36,39};

const int sensorPin = 34;  /* Soil moisture sensor Analog O/P pin */
int soilMoistureValue = 0;
int soilMoisturePercent = 0;
int i =1;


void setup(void){
    Serial.begin(115200);     /* Set the baudrate to 115200*/
    
}

void loop(){
  
//  char strBuf[20];
//  for(int i=0; i < ADC_1_Pins.length(); i++){
//    
//    sprintf(strBuf, "Pin %d : %d", ADC_1_Pins[i], analogRead(ADC_1_Pins[i]) );
//    Serial.println(strBuf);
// 
//  }
  
  soilMoistureValue = analogRead(sensorPin);
  
  Serial.print(i);
  Serial.print(".");
  Serial.println(soilMoistureValue);
  i++;
  delay(500);
//  Serial.println(soilMoistureValue);
//  soilMoisturePercent=map(soilMoistureValue, AirValue, WaterValue, 0, 100);
//  Serial.print("Soil Moist % = ");
//  Serial.println(soilMoisturePercent);
  
//  _moisture = ( 100 - ( (sensor_analog/4095.00) * 100 ) );
//  Serial.print("Moisture = ");
//  Serial.print(_moisture);  /* Print Moisture on the serial window */
//  Serial.println("%");

  //Set the payload to publish.
  //sprintf(msg, "{\"moisture\":%d,\"unit\": \"%\"}");


}
