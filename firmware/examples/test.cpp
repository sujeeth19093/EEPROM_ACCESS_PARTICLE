#include "Particle.h"

SYSTEM_MODE(MANUAL);
SYSTEM_THREAD(ENABLED);


char toPublish_m[10];
String text = "- Value"; //text to accompany data
String event = "e-test"; //name of event
float num_m;  //data variable

void setup()
{
    //startup delay and initialization
    delay(5000);
    EEPROM.put(0, NO_DATA_EEPROM);
    EEPROM.put(5,0);
    num_m = 0;
    WiFi.on(); //MANUAL requires code to turn WiFi module on
    Particle.connect(); //Establishes connection to cloud
}

void loop()
{
      Particle.process(); //maintains connection with cloud, must be executed, at most, every 20s
      if(waitFor(Particle.connected, 10000)) //checks if device is connected to cloud
      {
        Particle.process();
        sprintf(toPublish_m, "%f - Value", num_m);
        Serial.printf("%f - Main\r\n", num_m);
        Particle.publish("main", toPublish_m);
        delay(1000);

            process(text, event, FRONT_APPEND); //processes eeprom stored data. sends text that data is appended to and event name
      }

      if(!Particle.connected())
      {
        Serial.printf("Enter store condition\r\n");
        store(num_m); //stores data in eeprom
      }
        num_m++;
}
