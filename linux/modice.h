#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/mman.h>
#include <sched.h>
#include <string.h>

#include "gpio_pins.h"
#include "gpio_macros.h"

void *gpio_map;
// GPIO access
volatile unsigned *gpio;

void setup_gpio();
void close_gpio();