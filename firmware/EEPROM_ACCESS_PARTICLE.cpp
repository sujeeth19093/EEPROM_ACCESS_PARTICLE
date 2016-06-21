#include "EEPROM_ACCESS_PARTICLE.h"

void storeData(String msg, int len)
{
	int position;
	int offset;
	String temp;
	int status;

	EEPROM.get(0, status);
	if(status != DATA_IN_EEP)
	{
		EEPROM.put(0, DATA_IN_EEP);		//Indicates that data is present in EEPROM
		EEPROM.put(5, 0);
	}

	EEPROM.get(5, position);		//The starting position of most recently stored data

	if(position == 0)				//Sets the start point of the new data to be stored
	{
		offset = position + 10;
	}else
	{
		EEPROM.get(position, temp);
		offset = position + temp.length() + 1;
	}

	EEPROM.put(offset, msg);
	Serial.printf("%s\n", msg);//////////////////////////////////////////////////////////////
	EEPROM.put(offset + len, '\0');

	EEPROM.put(5, offset);			//Updates the start position
}

void processData()
{
	int status;
	EEPROM.get(0, status);

	if(status == DATA_IN_EEP)
	{
		int position = 10;
		int limit;
		String msg;
		boolean success;

		EEPROM.get(5, limit);			//Gets position of latest data stored

		while(limit >= position)
		{
			EEPROM.get(position, msg);	//copies data
			Serial.printf("%s\n", msg);//////////////////////////////////////////////////////////
			success = Particle.publish("eeprom data", msg);	//publishes data onto the cloud
			position = position + msg.length() + 1;	//position is shifted to next data stored
		}

			position = 0;

			EEPROM.clear();					//clears all data in  EEPROM
			EEPROM.put(5, position);		//sets initial position
			EEPROM.put(0, NO_DATA_IN_EEP);		//indicates no data in EEPROM
	}
}
