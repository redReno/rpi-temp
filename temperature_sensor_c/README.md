# rpi-temp
Small C application that uses a RPi and ds18b20 to measure the temperature.
The temperature is in Celcius, with two digits.

# To run
gcc -o rpi_temp.out thermostat.c
./rpi-temp.out

There is one parameter: 
debug (1 or 0) 
  - 1 if you want explanatory logs. Default 0.
