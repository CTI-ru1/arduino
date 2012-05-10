#include <Uberdust.h>

#include <XbeeRadio.h>
#include <XBee.h>
#include <stdio.h>
#include <string.h>
#include <SoftwareSerial.h>


// Create the xbee object
XBeeRadio xbee = XBeeRadio(); 

// Create reusable response objects for responses we expect to handle 
XBeeRadioResponse response = XBeeRadioResponse();  

// Allocate two bytes for to hold a 32-bit analog reading
uint8_t payload[] = { 
  102, 0,  0, 0, 0, 0};

// 16-bit addressing: Enter address of remote XBee, typically the coordinator
Tx16Request tx = Tx16Request(0xffff, payload, sizeof(payload));

TxStatusResponse txStatus = TxStatusResponse();

uint8_t ledPin = 13;

Uberdust uber = Uberdust();

void setup()
{

  xbee.initialize_xbee_module();
  // setup xbee 
  xbee.begin(38400);
  xbee.init();
  uber.setup(&xbee, &tx);
  delay(1000);
  sendCapabilities();
}

void loop()
{
  static unsigned long ledTimestamp = 0;
  if(millis() - ledTimestamp > 5000)
  {
    uber.blinkLED(1,100);
    ledTimestamp = millis();
  }
  checkAC();
  periodicCapabilities();
}

void periodicCapabilities()
{
  static unsigned long capabTimestamp = 0;
  if(millis() - capabTimestamp > 60000)
  {
    digitalWrite(13, HIGH);
    sendCapabilities();
    digitalWrite(13, LOW);
    delay(100);
    capabTimestamp = millis();
  }
}

void sendCapabilities(void)
{
    uber.sendValue("report", "AC");
}

void checkAC(void)
{
  if(xbee.checkForData(112))
  {
    xbee.getResponse(response);
    if(response.getData(0) == 1 && response.getData(1) == 1)
    {
      int value = response.getData(2);
			if(value)
			{
				//open AC
			}
			else 
			{
				//close AC
			}
      uber.blinkLED(2,100);
    }
  }
}

