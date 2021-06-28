#include "headers/Encoder.h"

long t0=0;

Encoder::Encoder(byte chAPin, byte chBPin) 
{
  this->chAPin = chAPin;
  this->chBPin = chBPin;
  init();
}

void Encoder::init() 
{
  pinMode(chAPin,OUTPUT);
}

void Encoder::ISREnc()
{
  long t00 = t0;
  t0 = millis();
  if(t0-t00 != 0)
  {
    Serial.println(t0-t00); 
  }
}

byte getVelocidad()
{
  //Implementar codigo velocidad aqui
}
