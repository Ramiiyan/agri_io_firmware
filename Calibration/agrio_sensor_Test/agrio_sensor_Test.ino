/*
  ESP32 Soil Moisture Sensor analysis
  Capacitive soil moisture sensor.
  By Ramiyan
*/



// Soil Moisture constant
#define DRY_ANALOG_VALUE  2900
#define WET_ANALOG_VALUE  1118

int ADC_1_Pins[] = {32,33,34,35,36,39};
const int sensorPin = 34;  /* Soil moisture sensor Analog O/P pin */

int soilMoistureAnalogVal = 0;
char msg[50];

double getMoistPercentage(int analogValue){
  // Linear Interpolation = (Analog_Value − Dry_Analog_Value) / (Wet_Analog_Value − Dry_Analog_Value)
  double moistPercent = ((double)(analogValue - DRY_ANALOG_VALUE) / (WET_ANALOG_VALUE - DRY_ANALOG_VALUE)) * 100 ;
//  if (moistPercent < 0.00){ 
//    return 0.00;
//  }else if(moistPercent > 101){
//    return 100.00;
//  }else{
    return moistPercent;
//  }

  
}

void setup(void){
    Serial.begin(115200);     /* Set the baudrate to 115200*/
}

void loop(){

  soilMoistureAnalogVal = analogRead(sensorPin);
  Serial.print("PinNo- ");
  Serial.print(sensorPin);
  Serial.print(" :: Analog Value: ");
  Serial.println(soilMoistureAnalogVal);

  sprintf(msg, "Moisture Percent: %.2f", getMoistPercentage(soilMoistureAnalogVal));
  Serial.println(msg);

  delay(500);
  
  
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
