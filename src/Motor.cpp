#include "Motor.h"

Motor::Motor(byte in1Pin, byte in2Pin, byte stbyPin, byte pwmPin, byte pwmChannel) 
{
  this->in1Pin = in1Pin;
  this->in2Pin = in2Pin;
  this->stbyPin = stbyPin;
  this->pwmPin = pwmPin;
  this->pwmChannel = pwmChannel;
  init();
}

void Motor::init() 
{
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  pinMode(stbyPin, OUTPUT);
  ledcSetup(pwmChannel,freq, resolution);
  ledcAttachPin(pwmPin, pwmChannel);
  off();
}

void Motor::off() 
{
  digitalWrite(in1Pin, LOW);
  digitalWrite(in2Pin, LOW);
  digitalWrite(stbyPin, LOW);
  ledcWrite(pwmChannel, 0);
}

void Motor::setValue(byte pwmVal)
{
  ledcWrite(pwmChannel, pwmVal);
}

void Motor::cw()
{
  digitalWrite(in1Pin, HIGH);
  digitalWrite(in2Pin, LOW);
  digitalWrite(stbyPin, HIGH);
}

void Motor::ccw()
{
  digitalWrite(in1Pin, LOW);
  digitalWrite(in2Pin, HIGH);
  digitalWrite(stbyPin, HIGH);
}