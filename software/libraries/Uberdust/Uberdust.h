#ifndef Uberdust_h
#define Uberdust_h

#include <Arduino.h>
#include <XbeeRadio.h>
#include <String.h>
#include "RelaySensor.h"

#define PAYLOAD_SIZE 30

class Uberdust
{
public:
	//the period we use when broadcasting our status. currently 1 min.
	const static unsigned broadcastPeriod = 60000;
	//the default pins for our switch, and the relay
	const static long DEFAULT_BAUDRATE = 38400;
	//setting the default LED pin
	const static int ledPin = 13;
	uint8_t payload[PAYLOAD_SIZE];
	char* name;
	Uberdust();
	// HomeAuto(char name[]);
	void setup(XBeeRadio* xbee, Tx16Request* tx);
	// void setup(long baudrate);
	// void check(void);
	// void addSensor(Sensor* newSensor);
	void blinkLED(int times, int milliseconds);
	void sendValue(String capability, int value);
	void sendValue(String capability, float value);
	void sendValue(String capability, double value);
	void sendValue(String capability, String value);
	// void sendValue(String capability, char value[]);
private:
	XBeeRadio* xbee;
	Tx16Request* tx;
	void init(char name[]);
	void send_data();
	void send_data(int sensor_type, int sensor_val);
};

#endif
