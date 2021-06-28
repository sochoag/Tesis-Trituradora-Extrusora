#ifndef InterruptorClass
#define InterruptorClass

#include <Arduino.h>

class Interruptor
{
  private:
    byte pinInterruptor;
    void init(void);
    bool lastValue = false;
  public:
    Interruptor(byte pinInteruptor);
    bool status(void); 
};

#endif