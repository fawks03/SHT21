/****************************************************************
*  SHT21_Demo_Async
*
*  An example sketch that reads the sensor async and prints the
*  temperature and relative humidity to the serial port
* 
***************************************************************/

#include <Wire.h>
#include "SHT21.h"

SHT21 SHT21;

void setup()
{
  SHT21.setHold(false);   //default value
  SHT21.setTempWait(48);  //default value
  SHT21.setHumdWait(16);  //default value
  SHT21.setInterval(200); //default value
  
  SHT21.begin();          //also calls update()
  
  Serial.begin(9600);
}

void loop()
{
  SHT21.update(); //updates sensor value non-blocking
  
  Serial.print("Humidity(%RH): ");
  Serial.print(SHT21.getHumidity());      //gets latest sensor value
  Serial.print("     Temperature(C): ");
  Serial.println(SHT21.getTemperature()); //gets latest sensor value
  
  delay(1000);
}
