#include "headers/Termocupla.h"

Termocupla::Termocupla(byte SCLK, byte CS, byte MISO)
{
  this->SCLK = SCLK;
  this->MISO = MISO;
  this->CS = CS;
  init();
}

void Termocupla::init(void)
{
  pinMode(CS, OUTPUT);
  pinMode(SCLK, OUTPUT);
  pinMode(MISO, INPUT);

  digitalWrite(CS, HIGH);
}

byte Termocupla::spiread(void)
{
  int i;
  byte d = 0;

  for (i = 7; i >= 0; i--)
  {
    digitalWrite(SCLK, LOW);
    delayMicroseconds(10);
    if(digitalRead(MISO))
    {
      d |= (1 << i);
    }
    digitalWrite(SCLK, HIGH);
    delayMicroseconds(10);
  }
  return d;
}

float Termocupla::readTempC(void)
{
  uint16_t v;

  digitalWrite(CS,LOW);
  delayMicroseconds(10);
  
  v = spiread();
  v <<= 8;
  v |= spiread();

  digitalWrite(CS,HIGH);

  if (v & 0x4)
  {
    return NAN;
  }

  v >>= 3;
  
  return v * 0.25;
}