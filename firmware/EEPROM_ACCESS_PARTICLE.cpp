#include "EEPROM_ACCESS_PARTICLE.h"

int status_store;
int position_store;
void storeData()
{
  EEPROM.get(0, status_store);
  if(status_store == NO_DATA_IN_EEP)
  {
    EEPROM.put(0, DATA_IN_EEP);
    EEPROM.put(5, 0);
  }

  EEPROM.get(5, position_store);
  if(position_store == 0)
  {
    position_store = 10;
  }else
  {
    position_store = position_store + 35;
  }
    EEPROM.put(position_store,store_str);
    delay(1000);
  //  Particle.publish("e-test-store", s1);
    Serial.printf("position_store = %d\r\n", position_store);
    EEPROM.put(5, position_store);
}

String s2;
int status_process;
int limit_process, position_process;
void processData()
{
  EEPROM.get(0, status_process);
  Serial.printf("status_process = %d\r\n", status_process);
  if(status_process == DATA_IN_EEP)
  {
    limit_process = 0;
    position_process = 10;
    EEPROM.get(5, limit_process);
    Serial.printf("limit_process = %d\r\n", limit_process);
    while(limit_process >= position_process)
    {
      Particle.process();
      Serial.printf("position_process = %d\r\n", position_process);
      EEPROM.get(position_process, s2);
      delay(1000);
      Particle.publish("e-test", s2);
      Serial.printf("Published\r\n");
      position_process = position_process + 35;
    }
    EEPROM.clear();
    EEPROM.put(0, NO_DATA_IN_EEP);
    EEPROM.put(5, 0);
  }
}
