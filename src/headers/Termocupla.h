#ifndef TermocuplaClass
#define TermocuplaClass

#include <Arduino.h>

class Termocupla
{
  private:
    byte SCLK, CS, MISO;
    void init(void);
    byte spiread(void);
  public:
    Termocupla(byte SCLK, byte CS, byte MISO);
    float readTempC(void);
};

#endif