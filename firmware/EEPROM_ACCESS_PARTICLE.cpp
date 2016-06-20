#include "EEPROM_ACCESS_PARTICLE.h"

//typedef struct reading {
//    String data;					//Assuming a maximum of 30 characters
//    struct reading * next;
//} reading_t;

//reading_t * reading_queue_head = NULL;

void storeData(String msg)
{
	int position;
	int offset;
	
	EEPROM.put(0, DATA_IN_EEP);		//Indicates that data is present in EEPROM
	EEPROM.get(5, position);		//The starting position of most recently stored data
	
	if(position == 0)				//Sets the start point of the new data to be stored
	{
		offset = position + 10;
	}else
	{
		offset = position + STRING_LEN;
	}
	
	EEPROM.put(offset, msg);
	
	EEPROM.put(5, offset);			//Updates the start position
}

/*void addToQueue(String msg)
{
  reading_t * new_reading = new reading_t;
  new_reading->next = reading_queue_head;
  reading_queue_head = new_reading;//store the value
  new_reading->data = msg;
}

void processQueue()
{
	reading_t * current = reading_queue_head;
  
  while(reading_queue_head != NULL){
    current = reading_queue_head;
    boolean success = Particle.publish("colorinfo", reading_queue_head->data);	//I assume that colorinfo is used everywhere

    if(success){					//message was sent
      reading_queue_head = reading_queue_head->next;
      free(current);
      if(reading_queue_head != NULL){
        delay(1000); 				//wait a second before trying the next message Particle does not let us go faster than this
      }else{						//we are done here
        break;
      }
    }else{							//we failed to send try again later
		break;
    }
  }
}*/

void processData()
{
	int status;
	EEPROM.get(0,status);
	
	if(status == DATA_IN_EEP)
	{
		int position;
		String msg;
		boolean fail;
		
		EEPROM.get(5,position);			//Gets position of latestest data stored	
		
		while(position > 10)
		{
			EEPROM.get(position, msg);	//copies data
			boolean success = Particle.publish("colorinfo", msg);	//publishes data onto the cloud
			if(!success)				//data to cloud transfer is unsuccesful
			{
				EEPROM.put(5, position);	//the position of latest data changes 
				fail = TRUE;
				break;				
			}
			//addToQueue(msg);			//adds data onto Q.
			position = position - STRING_LEN;	//position is shifted to next data stored
		}
		
		if(success)
		{
			position = 0;
			
			EEPROM.clear();					//clears all data in  EEPROM
			EEPROM.put(5, position);		//sets initial position
			EEPROM.put(0, NO_DATA_IN_EEP);		//indicates no data in EEPROM
		}
		//processQueue();					//processes data in correct order of stroage
	}
}
