/*
* led_controller.c
* Makes led lamps attached to a GPIO pin blink once. 
* A blink is initiated if a running program receives
* a SIGINT signal. A SIGTERM signal is required to 
* shut down the program.
* parameters: gpio (int, the gpio pin. Default 14)
*/

#include <stdio.h>
#include <stdlib.h>
#include <pigpio.h>
#include <signal.h>

#define GPIO_DEFAULT 14
#define LED_ON 1
#define LED_OFF 0
#define BLINK_INTERVAL 0.5

void handle_led_request(int);
void handle_sigterm();

int gpio = GPIO_DEFAULT;

int main(int argc, char **argv)
{
  if (argc > 1)
  {
    extern int gpio;
    gpio = atoi(argv[1]);
  }

  if (gpioInitialise() < 0)
  {
    printf("gpio init failed");
    exit(EXIT_FAILURE);
  }

  gpioSetMode(gpio, PI_OUTPUT);
  // create signal handlers
  signal(SIGINT, handle_led_request);
  signal(SIGTERM, handle_sigterm);
  // run until SIGTERM
  while (1)
  {
    ;
  }
}

void handle_led_request(int sig) {
  extern int gpio;
  gpioWrite(gpio, LED_ON);
  time_sleep(BLINK_INTERVAL);
  gpioWrite(gpio, LED_OFF);
  // reset signal
  signal(SIGINT, handle_led_request);
}

void handle_sigterm() {
  // stop all led handling
  extern int gpio;
  signal(SIGINT, SIG_DFL);
  gpioWrite(gpio, LED_OFF);
  gpioTerminate();
  exit(EXIT_SUCCESS);
}
