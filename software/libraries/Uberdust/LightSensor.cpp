#include "LightSensor.h"

LightSensor::LightSensor()
{
	init("unknown");
}

void LightSensor::init(char name[])
{
	this->name = (char*) malloc(sizeof(char) * (strlen(name)+1));
	strcpy(this->name, name);	
}

void LightSensor::setup()
{
	pinMode(ledPin, OUTPUT);
	digitalWrite(ledPin, LOW);
}

void LightSensor::blinkLED(int times, int milliseconds)
{
  for(int i = 0; i < times; i++)
  {
    digitalWrite(ledPin, HIGH);
    delay(milliseconds/times/2);
    digitalWrite(ledPin, LOW);
    delay(milliseconds/times/2);
  }
}