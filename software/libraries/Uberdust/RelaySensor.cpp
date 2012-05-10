#include "RelaySensor.h"

RelaySensor::RelaySensor()
{
	init("unknown");
}

void RelaySensor::init(char name[])
{
	this->name = (char*) malloc(sizeof(char) * (strlen(name)+1));
	strcpy(this->name, name);	
}

void RelaySensor::setup()
{
	pinMode(ledPin, OUTPUT);
	digitalWrite(ledPin, LOW);
}

void RelaySensor::blinkLED(int times, int milliseconds)
{
  for(int i = 0; i < times; i++)
  {
    digitalWrite(ledPin, HIGH);
    delay(milliseconds/times/2);
    digitalWrite(ledPin, LOW);
    delay(milliseconds/times/2);
  }
}