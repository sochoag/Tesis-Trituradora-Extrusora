#include <Arduino.h>
#include "headers/Encoder.h"

Encoder enc1(2,4);
Encoder enc2(2,5);

long t00 = 0;
long t01 = 0;

void IRAM_ATTR ISREnc1()
{
  enc1.t0 = millis();
  if(enc1.t0-t00 != 0)
  {
    Serial.println(enc1.t0-t00);
    Serial.println("Interrupcion desde encoder 1");
    t00 = enc1.t0;
  }
}

void IRAM_ATTR ISREnc2()
{
  enc2.t0 = millis();
  if(enc2.t0-t01 != 0)
  {
    Serial.println(enc2.t0-t01); 
    Serial.println("Interrupcion desde encoder 2");
    t01 = enc2.t0;
  }
}

void setup() 
{
  Serial.begin(115200);
  attachInterrupt(digitalPinToInterrupt(enc1.chBPin),ISREnc1,RISING);
  attachInterrupt(digitalPinToInterrupt(enc2.chBPin),ISREnc2,RISING);
}

void loop() 
{
}