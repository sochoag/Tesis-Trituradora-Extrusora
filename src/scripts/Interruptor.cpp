#include "headers/Interruptor.h"

Interruptor::Interruptor(byte pinInterruptor)
{
    this->pinInterruptor = pinInterruptor;
    init();
}

void Interruptor::init(void)
{
    pinMode(pinInterruptor, INPUT_PULLUP);
    lastValue = digitalRead(pinInterruptor);
}

bool Interruptor::status(void)
{
    if(lastValue != digitalRead(pinInterruptor))
    {
        lastValue = !lastValue;
    }
    return lastValue;
}
