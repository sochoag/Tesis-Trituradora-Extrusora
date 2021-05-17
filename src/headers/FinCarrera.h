#ifndef FinCarreraClass
#define FinCarreraClass

#include <Arduino.h>

class FinCarrera
{
  private:
    byte pinFC;
    void init(void);
    bool lastValue = false;
  public:
    FinCarrera(byte pinFC);
    bool status(void); 
};

#endif