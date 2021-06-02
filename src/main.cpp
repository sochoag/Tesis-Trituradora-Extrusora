#include <Arduino.h>
#include "headers/Motor.h"
#include "headers/Termocupla.h"
#include "headers/Conexion.h"

Termocupla temp1(18,5,19);
//Termocupla temp2(18,6,19);
//Termocupla temp3(18,7,19);

Conexion conexion;

static TimerHandle_t temperaturas = NULL;

void readTemperatures(TimerHandle_t xTimer)
{
  float termo1 = temp1.readTempC();
  Serial.println(termo1);
  //float termo2 = temp2.readTempC();
  //float termo3 = temp3.readTempC();
}

void reportar(void *pvParameters)
{
  while(1)
  {
    conexion.report();
    vTaskDelay(1000/portTICK_PERIOD_MS);
  }
}

void setup() 
{
  Serial.begin(115200);
  bool respuesta = conexion.autoConnect();
  Serial.println("Respuesta: "+String(respuesta));
  conexion.report();
  temperaturas = xTimerCreate( "Temperaturas",              //Nombre Tarea
                                5000/portTICK_PERIOD_MS,    //Periodo
                                pdTRUE,                     //Recurrente?
                                (void *)0,                  //Indetificador
                                readTemperatures);          //Función a ser llamada

  xTaskCreatePinnedToCore(reportar,"Reportar",2500,NULL,1, NULL,1);
  
  if(temperaturas == NULL)
  {
    Serial.println("Could not create Timer");
  }
  else
  {
    vTaskDelay(1000/portTICK_PERIOD_MS);
    Serial.println("Starting timers");
    xTimerStart(temperaturas, portMAX_DELAY);
    //xTimerStart(reportar, portMAX_DELAY);
  }
  vTaskDelete(NULL);
}

void loop() 
{
}