Edited Markbeee's Library for temperature and humidity sensor SHT21 (Sensirion) works with Arduino, ESP8266

This library works with temperature and humidity sensor SHT21 (Sensirion) both tested with Arduino and ESP8266. The demo sketch puts out the current temperature (Celsius) and humidity (%RH) values via the serial port.


Added async sensor reading

new functions: 
  SHT21.update();           call once per loop if setHold(false)
      async sensor reading
  SHT21.setTempWait(int);   increase this value if "Wire not available for: 243"
      delay between write and request for temp reading
  SHT21.setHumdWait(int);   increase this value if "Wire not available for: 245"
      delay between write and request for humd reading
  SHT21.setHold(bool);      if set to true, use markbeee's version
  SHT21.setInterval(int);   used to limit request frequency - minimum = tempWait + humdWait
      (default: 200ms)
