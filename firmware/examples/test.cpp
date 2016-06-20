#include "Particle.h"

#include "EEPROM_ACCESS_PARTICLE/EEPROM_ACCESS_PARTICLE.h"

String msg;
int i;

void setup()
{
	i=0;
}

void loop()
{
	sprintf(msg, "%d - This should keep repeating.", i);
	i++;
	boolean sent = Particle.publish("access_test", msg, PRIVATE);
	
	delay(1000);
	
	processData();
	
	if(!sent)
	{
		storeData(msg);
	}
}
