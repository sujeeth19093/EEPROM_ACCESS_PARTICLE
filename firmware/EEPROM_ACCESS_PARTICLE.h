#ifndef _EEPROM_ACCESS_PARTICLE
#define _EEPROM_ACCESS_PARTICLE

#include "application.h"

#define DATA_IN_EEP 1
#define NO_DATA_IN_EEP 0

String store_str;

void storeData();
void processData();

#endif
