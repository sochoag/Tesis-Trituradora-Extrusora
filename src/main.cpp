#include <Arduino.h>
#include "headers/Motor.h"
#include "headers/Termocupla.h"

Termocupla temp1(18,5,19);

void readValue(void *parameters)
{
  while(1)
  {
    float termo1 = temp1.readTempC();
    Serial.println(termo1);
  }
}


void setup() 
{
  xTaskCreatePinnedToCore(readValue,"Termocupla 1",1024,NULL,1,NULL,1);
  Serial.begin(115200);
  vTaskDelete(NULL);
}

void loop() 
{
}