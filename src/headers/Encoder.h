#ifndef EncoderClass
#define EncoderClass

#include <Arduino.h>

class Encoder 
{  
  private:
    bool value = 0;
    
  public:
    unsigned long t0=0;
    byte chAPin, chBPin;
    Encoder(byte chAPin, byte chBPin);
    void init();
    void ISREnc();
};

#endif