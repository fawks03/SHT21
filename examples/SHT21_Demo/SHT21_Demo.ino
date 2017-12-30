/****************************************************************
*  SHT21_Demo
*
*  An example sketch that reads the sensor and prints the
*  temperature and relative humidity to the serial port
* 
***************************************************************/

#include <Wire.h>
#include "SHT21.h"

SHT21 SHT21;

void setup()
{
  SHT21.setHold(true);    //markbeee's version
  SHT21.setTempWait(48);  //default value
  SHT21.setHumdWait(16);  //default value
  SHT21.begin();          //don't use SHT21.update() if setHold(true)
  Serial.begin(9600);
}

void loop()
{
  Serial.print("Humidity(%RH): ");
  Serial.print(SHT21.getHumidity());      //waits until sensors read finished and returns value
  Serial.print("     Temperature(C): ");
  Serial.println(SHT21.getTemperature()); //waits until sensors read finished and returns value
  
  delay(1000);
}
