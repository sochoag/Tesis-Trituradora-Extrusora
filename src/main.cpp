#include <Arduino.h>
#include "Motor.h"

Motor Mot_Ext(5,3,4,2,0);

void setup() 
{

}

void loop() 
{
  Mot_Ext.ccw();
  for(int i=0; i<=255; i++)
  {
    Mot_Ext.setValue(i);
    delay(10);
  }
  for(int i=255; i>=0; i--)
  {
    Mot_Ext.setValue(i);
    delay(20);
  }
}