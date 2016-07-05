#include "EEPROM_ACCESS_PARTICLE.h"

void store(float num) //function do store data in eeprom
{
  int status_store; //used to check if data present in eeprom
  int position_store;//used to store position point of data

  EEPROM.get(0, status_store); //obtains status of eeprom

  if(status_store == NO_DATA_EEPROM){ //updates eeprom to data present and sets starting data point
    EEPROM.put(0, DATA_IN_EEPROM);
    EEPROM.put(5, 0);
  }

  EEPROM.get(5, position_store);
  Serial.printf("position_store = %d\r\n", position_store);
  if(position_store == 0){ //if position_store = 0, it indicates no data is present yet
    position_store = 10;
  }else{
    position_store = position_store + 10; //last address is incremented by 10 for address of next data
  }

    EEPROM.put(position_store, num); //places data in eeprom at position_store
    delay(1000);

    Serial.printf("store - %f\r\n", num);

    EEPROM.put(5, position_store); //updates last address of eeprom to be filled
}

void process(String& text_process, String& event, int position_of_data) //processes data in eeprom
{
  float num;
  int status_process;
  int limit_process = 0; //the last data point address
  int position_process = 10;
  char toPublish[10];
  String toPub;

  EEPROM.get(0, status_process); //gets eeprom status
  Serial.printf("status_process = %d\r\n", status_process);
  if(status_process == DATA_IN_EEPROM) //only processes data if it is present
  {
    EEPROM.get(5, limit_process);
    Serial.printf("limit_process = %d\r\n", limit_process);

    while(limit_process >= position_process)
    {
      Particle.process();
      Serial.printf("position_process = %d\r\n", position_process);
      EEPROM.get(position_process, num);
      delay(1000);
      sprintf(toPublish, " %f ", num);
      toPub = String(toPublish);

      if(position_of_data == FRONT_APPEND)
      {
        Serial.printf("%f %s", num, text_process.c_str());
        toPub.concat(text_process); //appends data to text
        Particle.publish(event, toPub); //publishes data
      }else if(position_of_data == BACK_APPEND)
      {
        Serial.printf("%s %f", text_process.c_str(), num);
        text_process.concat(toPub); //appends data to text
        Particle.publish(event, text_process); //publishes data
      }
      delay(1000);
      Serial.printf("Published\r\n");
      position_process = position_process + 10;
    }
    EEPROM.clear(); //clears all data in EEPROM
    EEPROM.put(0, NO_DATA_EEPROM); //sets status and inital position of eeprom
    EEPROM.put(5, 0);
  }
}
