#ifndef MY_LED_H
#define MY_LED_H

#include <Arduino.h>

class Motor 
{  
  private:
    byte in1Pin, in2Pin, stbyPin, pwmPin, pwmChannel, resolution = 8;
    int freq=5000;
    
  public:
    Motor(byte in1Pin, byte in2Pin, byte stbyPin, byte pwmPin, byte pwmChannel);
    void init();
    void off();
    void setValue(byte pwmVal);
    void cw();
    void ccw();
};
#endif