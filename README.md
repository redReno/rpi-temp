# rpi-temp
Small C application that uses a RPi and ds18b20 to measure the temperature.
The temperature is in Celcius, with two digits.

# To run
cd temperature_sensor_c
gcc -o rpi-temp.out thermostat.c 
./rpi-temp.out (this runs the program once, and can be repeated)
