#include "Uberdust.h"

Uberdust::Uberdust()
{
	init("unknown");
}

void Uberdust::init(char name[])
{
	this->name = (char*) malloc(sizeof(char) * (strlen(name)+1));
	strcpy(this->name, name); 
}

void Uberdust::setup(XBeeRadio* xbee, Tx16Request* tx)
{
	pinMode(ledPin, OUTPUT);
	digitalWrite(ledPin, LOW);
	this->xbee = xbee;
	this->tx = tx;
}

void Uberdust::blinkLED(int times, int milliseconds)
{
	for(int i = 0; i < times; i++)
	{
	digitalWrite(ledPin, HIGH);
	delay(milliseconds/times/2);
	digitalWrite(ledPin, LOW);
	delay(milliseconds/times/2);
	}
}

#define CAPAB_LENGTH 10
#define VALUE_LENGTH 10

void Uberdust::sendValue(String capability, int value)
{
	char val[VALUE_LENGTH];
	memset(val, '\0', VALUE_LENGTH);
	itoa(value, val, 10);
	sendValue(capability, String(val));
}

void Uberdust::sendValue(String capability, float value)
{
	sendValue(capability, (double) value);
}

void Uberdust::sendValue(String capability, double value)
{
	char val[VALUE_LENGTH];
	memset(val, '\0', VALUE_LENGTH);
	dtostrf(value, 6, 3, val);
	sendValue(capability, String(val));
}

// void Uberdust::sendValue(String capability, String value)
// {
	// char val[VALUE_LENGTH];
	// memset(val, '\0', VALUE_LENGTH);
	// value.toCharArray(val, VALUE_LENGTH);
	// sendValue("wtf", val);
// }


void Uberdust::sendValue(String capability, String value)
{
	char capab[CAPAB_LENGTH];
	memset(capab, '\0', CAPAB_LENGTH);
	capability.toCharArray(capab, CAPAB_LENGTH);

	char val[VALUE_LENGTH];
	memset(val, '\0', VALUE_LENGTH);
	value.toCharArray(val, VALUE_LENGTH);
	
	uint16_t myAddr = xbee->getMyAddress();
	
	payload[0] = 103;
	payload[1] = strlen(capab)+1;
	payload[2] = strlen(val)+1;
	memcpy(payload+3, &myAddr, 2);
	payload[5] = 0xff;
	payload[6] = 0xff;
	memcpy(payload+7, capab, strlen(capab)+1);
	memcpy(payload+7+strlen(capab)+1, val, strlen(val)+1);
	send_data();
}

//Subroutine, which sends sensor's data
void Uberdust::send_data(int sensor_type, int sensor_val)
{
	// initialize bla_pointer pointer for reading 32 bit sensors values
	uint8_t * bla_pointer;

	payload[0] = 103;
	payload[1] = sensor_type;
	bla_pointer = (uint8_t*) &sensor_val; //ldr_val
	payload[2] = *bla_pointer;
	bla_pointer++;
	payload[3] = *bla_pointer;
	bla_pointer++;
	payload[4] = 0; //*bla_pointer;
	bla_pointer++;
	payload[5] = 0; //*bla_pointer;


	send_data();

}

void Uberdust::send_data(void)
{
	uint8_t* oldPayload = tx->getPayload();
	uint8_t oldPayloadLength = tx->getPayloadLength();
	
	tx->setPayload(payload);
	tx->setPayloadLength(PAYLOAD_SIZE);
	xbee->sendAndCheck(*tx,112);	
	delay(100);	 
	
	tx->setPayload(oldPayload);
	tx->setPayloadLength(oldPayloadLength);
	
}
