#ifndef _EEPROM_ACCESS_PARTICLE
#define _EEPROM_ACCESS_PARTICLE

#include "application.h"

#define NO_DATA_EEPROM 0 //indicates no data present in EEPROM
#define DATA_IN_EEPROM 1 //indicates data present in EEPROM

#define BACK_APPEND 0 // indicates that data should append behind text
#define FRONT_APPEND 1 // indicates that data should append in front of text

void store(float num);
void process(String& text_process, String& event, int position_of_data);

#endif
