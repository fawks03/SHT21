Edited Markbeee's Library for temperature and humidity sensor SHT21 (Sensirion) works with Arduino, ESP8266

This library works with temperature and humidity sensor SHT21 (Sensirion) both tested with Arduino and ESP8266. The demo sketch puts out the current temperature (Celsius) and humidity (%RH) values via the serial port.


Added async sensor reading

__new functions:__<br />
  _SHT21.update();_           call once per loop if setHold(false)<br />
      - async sensor reading<br />
  _SHT21.setTempWait(int);_   increase this value if "Wire not available for: 243"<br />
      - delay between write and request for temp reading<br />
  _SHT21.setHumdWait(int);_   increase this value if "Wire not available for: 245"<br />
      - delay between write and request for humd reading<br />
  _SHT21.setHold(bool);_      if set to true, use markbeee's version<br />
  _SHT21.setInterval(int);_   used to limit request frequency - minimum = tempWait + humdWait<br />
      - (default: 200ms)<br />
