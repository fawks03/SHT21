/*
  SHT21 - Library for ESP8266 and Arduino for the Sensirion Temperature and Humidity sensor

  Created by Markus Ulsass, Hamburg, Germany
  github@tradewire.de
  23-5-2016
  https://github.com/markbeee/SHT21

  With credits to:

  HTU21D Humidity Sensor Library
  By: Nathan Seidle
  SparkFun Electronics
  Date: September 22nd, 2013
  License: This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).

  29/12/2017 edited by fawks03 - async reading
*/

#include <Wire.h>
#include "SHT21.h"

SHT21::SHT21 () {}

void SHT21::begin(void) {
  Wire.begin();
  if (!hold)
    update();
}

float SHT21::getHumidity(void) {
  if (!hold) return humd;
  else return (-6.0 + 125.0 / 65536.0 * (float)(readSHT21(TRIGGER_HUMD_MEASURE_NOHOLD)));
}

float SHT21::getTemperature(void) {
  if (!hold) return temp;
  else return (-46.85 + 175.72 / 65536.0 * (float)(readSHT21(TRIGGER_TEMP_MEASURE_NOHOLD)));
}

void SHT21::update(void) {
  switch (state) {
    case 0:		//setup
      {
		if (millis() >= nextRefresh) {
			nextRefresh = millis() + refreshInterval;
			state = 1;
			Wire.beginTransmission(SHT21_ADDRESS);
			Wire.write(currentRead ? TRIGGER_HUMD_MEASURE_NOHOLD : TRIGGER_TEMP_MEASURE_NOHOLD);
			Wire.endTransmission();
			waitUntil = millis() + (currentRead ? humdWait : tempWait);
		}
        break;
      }
    case 1:		//request
      {
        if (millis() >= waitUntil)
        {
          Wire.requestFrom(SHT21_ADDRESS, 3);
          if (Wire.available() > 2) {
            state = 3;
            SHT21::update();
          } else { //usually ignored
            state = 2;
            waitUntil = millis() + timeout;
          }
        }
        break;
      }
    case 2:	//wait for request
      {
        if (Wire.available() == 3) {
          state = 3;
          SHT21::update();
        } else if (millis() >= waitUntil) {
          while (Wire.available())
            Wire.read();
          state = 0;
          Serial.println("request timed out.");
        }
        break;
      }
    case 3:		//return result
      {
        uint16_t result = ((Wire.read()) << 8);
        result += Wire.read();
        result &= ~0x0003;   // clear two low bits (status bits)
        if (currentRead)   //calculate humd
          humd = (-6.0 + 125.0 / 65536.0 * result);
        else  //calculate temp
          temp = (-46.85 + 175.72 / 65536.0 * result);
        currentRead = !currentRead;
        state = 0;
        break;
      }
  }
}

void SHT21::setTempWait(int val) {
  tempWait = val;
}
void SHT21::setHumdWait(int val) {
  humdWait = val;
}
void SHT21::setHold(bool val) {
  hold = val;
}
void SHT21::setInterval(int val) {
	refreshInterval = val;
}

uint16_t SHT21::readSHT21(uint8_t command)
{
  uint16_t result;

  Wire.beginTransmission(SHT21_ADDRESS);
  Wire.write(command);
  Wire.endTransmission();

  if (command == TRIGGER_HUMD_MEASURE_NOHOLD)
    delay(humdWait);
  else
    delay(tempWait);

  Wire.requestFrom(SHT21_ADDRESS, 3);

  if (Wire.available() < 3) {	//wait 20ms for data, else return0		<< edit
    Serial.print("Wire not available for: "); Serial.println(command);
    for (int i = 0; i < 20; i++) {
      delay(1);
      if (Wire.available() > 2) break;
    }
    return 0;
  }

  // return result
  result = ((Wire.read()) << 8);
  result += Wire.read();
  result &= ~0x0003;   // clear two low bits (status bits)
  return result;
}
