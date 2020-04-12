# led_controller
Small C application that should be run in the backgrund using &.
When it receives a SIGINT signals it closes/opens a GPIO, making
it ideal for making a LED blink once. It will shut down after
receiving a SIGTERM signal. If you don't use & when starting the
program, use ctrl+z to force it to shut down. Made for RPi3.

# To run
gcc -Wall -pthread -o led.out led_controller.c -lpigpio -lrt
sudo chown root:root led.out
sudo chmod 4755 led.out
./led.out &
