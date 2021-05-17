#include "headers/FinCarrera.h"

FinCarrera::FinCarrera(byte pinFC)
{
    this->pinFC = pinFC;
    init();
}

void FinCarrera::init(void)
{
    pinMode(pinFC, INPUT_PULLUP);
    lastValue = digitalRead(pinFC);
}

bool FinCarrera::status(void)
{
    if(lastValue != digitalRead(pinFC))
    {
        lastValue = !lastValue;
    }
    return lastValue;
}
