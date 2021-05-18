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
    vTaskDelay(250/portTICK_PERIOD_MS);
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