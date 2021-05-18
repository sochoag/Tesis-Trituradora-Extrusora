#include <Arduino.h>
#include "headers/Motor.h"
#include "headers/Termocupla.h"

Termocupla temp1(18,5,19);

static TimerHandle_t termocupla1 = NULL;

void readValue(TimerHandle_t xTimer)
{
  float termo1 = temp1.readTempC();
  Serial.println(termo1);
  vTaskDelay(250/portTICK_PERIOD_MS);
}


void setup() 
{
  Serial.begin(115200);
  termocupla1 = xTimerCreate( "Termocupla 1",
                            10000/portTICK_PERIOD_MS,
                            pdTRUE,
                            (void *)0,
                            readValue);
  
  if(termocupla1 == NULL)
  {
    Serial.println("Could not create Timer");
  }
  else
  {
    vTaskDelay(1000/portTICK_PERIOD_MS);
    Serial.println("Starting timers");
    xTimerStart(termocupla1, portMAX_DELAY);
  }
  vTaskDelete(NULL);
}

void loop() 
{
}

/*

#include <WiFiManager.h>
#include <Ticker.h>

Ticker ticker;

#define TRIGGER_PIN 0

byte timeout = 60;
byte LED = LED_BUILTIN;

void tick()
{
  digitalWrite(LED, !digitalRead(LED));
}

void configModeCalback (WiFiManager *myWiFiManager)
{
  Serial.println("Entered config mode");
  Serial.println(WiFi.softAPIP());
  Serial.println(myWiFiManager->getConfigPortalSSID());
  ticker.attach_ms(250, tick);
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