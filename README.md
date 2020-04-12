# rpi-temp
Small C application that uses a RPi and ds18b20 to measure the temperature.
The temperature is in Celcius, with two digits.

# To run
cd temperature_sensor_c
gcc -Wall -pthread -o rpi_temp.out thermostat.c -lpigpio -lrt
sudo chown root:root rpi_temp.out
sudo chmod 4755 rpi_temp.out

./rpi-temp.out (this runs the program once, and can be repeated)

There are two possible parameters (sequential):
debug (1 or 0) 
  - 1 if you want explanatory logs. Default 0.
led_controller (1 or 0)
  - 1 if you want to control a LED using SIGINT calls. Default 0.
    The led should get its power from GPIO14.
