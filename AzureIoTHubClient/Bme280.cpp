#include "Bme280.h"
#define delay(s) _mqttClient->mqttDelay(s)

void Bme280::initialise(){
  if (initialised) { return; }  
  bme280.begin(0x76);  
  delay(100);  
  initialised = true;
}

void Bme280::measure(){
  const int numberOfSamples = 4;

  initialise();
  temperature = pressure = humidity = 0;
   
  for (int c = 0; c < numberOfSamples; c++) {  
    temperature += bme280.readTemperature(); 
    pressure += (int)((int)( bme280.readPressure() + 0.5) / 100);
    humidity += bme280.readHumidity();
    delay(500);
  }
  
  temperature /= numberOfSamples;
  pressure /= numberOfSamples;  
  humidity /= numberOfSamples;
}

