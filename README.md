# rpi-temp
Small C application that uses a RPi and ds18b20 to measure the temperature.
The temperature is in Celcius, with two digits.

# To run
cd temperature_sensor_c
gcc -o main thermostat.c 
./main (this runs the program once, and can be repeated)
