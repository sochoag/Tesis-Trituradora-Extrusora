#include <Arduino.h>
#include "headers/Motor.h"
#include "headers/Termocupla.h"

Termocupla temp1(18,5,19);
Termocupla temp2(18,6,19);
Termocupla temp3(18,7,19);

static TimerHandle_t temperaturas = NULL;

void readTemperatures(TimerHandle_t xTimer)
{
  float termo1 = temp1.readTempC();
  float termo2 = temp2.readTempC();
  float termo3 = temp3.readTempC();
}

void setup() 
{
  Serial.begin(115200);
  temperaturas = xTimerCreate( "Temperaturas",              //Nombre Tarea
                                10000/portTICK_PERIOD_MS,   //Periodo
                                pdTRUE,                     //Recurrente?
                                (void *)0,                  //Indetificador
                                readTemperatures);          //Función a ser llamada
  
  if(temperaturas == NULL)
  {
    Serial.println("Could not create Timer");
  }
  else
  {
    vTaskDelay(1000/portTICK_PERIOD_MS);
    Serial.println("Starting timers");
    xTimerStart(temperaturas, portMAX_DELAY);
  }
  vTaskDelete(NULL);
}

void loop() 
{
}

/*
#include <WiFiManager.h>

void configModeCalback (WiFiManager *myWiFiManager)
{
  Serial.println("Entered config mode");
  Serial.println(WiFi.softAPIP());
  Serial.println(myWiFiManager->getConfigPortalSSID());
}

void setup()
{
  WiFi.mode(WIFI_STA);
  Serial.begin(115200);
  Serial.println("\n Starting");
  pinMode(TRIGGER_PIN, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
  ticker.attach_ms(1000, tick);
}

void loop()
{
  if(digitalRead(TRIGGER_PIN) == LOW)
  {
    ticker.attach_ms(500, tick);
    WiFiManager wm;
    //wm.resetSettings();
    //wm.setDebugOutput(false);
    wm.setAPCallback(configModeCalback);
    wm.setConfigPortalTimeout(timeout);
    if (!wm.autoConnect("Prueba Tesis"))
    {
      Serial.println("failed to connect and hit timeout"); 
    }
    Serial.println("Connected... yeey :)");
    ticker.detach();
    digitalWrite(LED, LOW);
  }
}
*/