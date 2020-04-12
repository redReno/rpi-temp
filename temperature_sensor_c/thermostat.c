/*
* thermostat.c
* Uses data (1-wire) from GPIO23 (Rpi 3)
* to read the temperature using a DS18B20
* The port is configured in /etc/modules and
* /boot/config.txt
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pigpio.h>
#include <signal.h>

#define BASE_DIR "/sys/bus/w1/devices/"
#define PIN_ADDRESS "28-00000adb99e5"
#define DEVICE_FILE BASE_DIR PIN_ADDRESS "/w1_slave"
#define NUMBER_OF_DECIMALS 3

void run_thermostat(int);
void extract_temp(char *, char *);
void run_led_controller(void);
void handle_led_request(int);
void handle_sigterm();

int main(int argc, char **argv)
{
  int debug = 0;
  int led_controller = 0;

  if (argc > 1) {
    debug = atoi(argv[1]); 
  }
  if (argc > 2) {
    led_controller = atoi(argv[2]);
    if (led_controller)
    {
      run_led_controller();
    }
  }
  run_thermostat(debug);
  exit(EXIT_SUCCESS);
}

void run_led_controller() {
  if (gpioInitialise() < 0)
  {
    printf("fail");
    exit(EXIT_FAILURE);
  }
  gpioSetMode(14, PI_OUTPUT);
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
  gpioWrite(14, 1);
  time_sleep(0.5);
  gpioWrite(14, 0);
  // reset signal
  signal(SIGINT, handle_led_request);
}

void handle_sigterm() {
  // stop all led handling
  signal(SIGINT, SIG_DFL);
  gpioWrite(14, 0);
  gpioTerminate();
  exit(EXIT_SUCCESS);
}

// debug is 1 for true, 0 for false
void run_thermostat(int debug) {
  FILE *fptr;
  int buffer = 256;
  char data[buffer];
  char temperature[7] = "";
  float temperature_result;
  if (debug) puts("Reading temperature...");
  if ((fptr = fopen(DEVICE_FILE, "r")) == NULL) {
    printf("Error reading temperature\n");
    exit(EXIT_FAILURE);
  }
  while ((fgets(data, buffer, fptr)) != NULL);
  fclose(fptr);
  extract_temp(data, temperature);
  temperature_result = strtof(temperature, NULL);
  printf("%.2f", temperature_result);	
}

void extract_temp(char *data, char *temperature) {
  int decimals_nbr = NUMBER_OF_DECIMALS;
  int data_len;
  int decimals_index;
  int temp_index;
  int wholes_len;
  data_len = strlen(data);

  temp_index = (int) (strchr(data, '=') - data + 1);
  decimals_index = data_len - decimals_nbr - 1;
  wholes_len = decimals_index - temp_index;
  strncpy(temperature, data+(temp_index), wholes_len);
  strcat(temperature, ".");
  strncat(temperature, data+(decimals_index), decimals_nbr);
}
