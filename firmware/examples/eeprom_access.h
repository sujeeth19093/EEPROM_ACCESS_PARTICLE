#ifndef _EEPROM_ACCESS
#define _EEPROM_ACCESS

#include "application.h"

#define DATA_IN_EEP 1
#define NO_DATA_IN_EEP 0
#define STRING_LEN 30

//void addToQueue(String msg);
void storeData(String msg);
//void processQueue();
void processData();

#endif