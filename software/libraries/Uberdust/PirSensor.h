#ifndef PirSensor_h
#define PirSensor_h

#include<Arduino.h>
class PirSensor
{
public:
	//the period we use when broadcasting our status. currently 1 min.
	const static unsigned broadcastPeriod = 60000;
	//the default pins for our switch, and the Pir
	const static long DEFAULT_BAUDRATE = 38400;
	const static int ledPin = 13;
	char* name;
	PirSensor();
	// HomeAuto(char name[]);
	void setup(void);
	// void setup(long baudrate);
	// void check(void);
	// void addSensor(Sensor* newSensor);
	void blinkLED(int times, int milliseconds);
private:
	void init(char name[]);
};

#endif
