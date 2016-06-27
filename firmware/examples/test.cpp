#include "Particle.h"

#include "EEPROM_ACCESS_PARTICLE/EEPROM_ACCESS_PARTICLE.h"

SYSTEM_MODE(MANUAL);

char s[35];
int i;
void setup()
{
    i = 0;
    EEPROM.put(0,0);
    Particle.connect();
}

void loop()
{
  if(i % 4 == 0)
    Particle.connect();

   if(i % 5 == 0)
    Particle.disconnect();

    sprintf(s, "%d - repeat",i);
    i++;

    store_str = String(s);

    if(Particle.connected())
    {
      Particle.process();
    }
    //boolean sent = Particle.publish("main", s1);
    delay(1000);

    if(Particle.connected())
        processData();

    if(!Particle.connected())
        storeData();
}
