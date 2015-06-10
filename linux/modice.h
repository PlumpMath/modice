#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/mman.h>
#include <sched.h>
#include <string.h>
#include <alsa/asoundlib.h>

#include "gpio_pins.h"
#include "gpio_macros.h"

/* GPIO definitions */
void *gpio_map;
// GPIO access
volatile unsigned *gpio;

void setup_gpio();
void close_gpio();

/* Audio definitions */
/*
char sndbuf;
snd_pcm_t *playback_handle;
snd_pcm_t *capture_handle;
snd_pcm_hw_params_t *hw_params;

void setup_sound();
void close_sound();*/
