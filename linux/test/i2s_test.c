#include <stdio.h>
#include <stdint.h> // uint8_t
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sched.h>
#include <string.h>
#include <dirent.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
//#include <bcm2835.h>
#include <signal.h>

#define I2S_321_BASE 0xF2200000  //3.2.1
#define I2S_320_BASE 0xF2200000  //3.2.0
#define I2S_50_BASE 0xF2200000  //5.0

#include "gpio_pins.h"
#include "gpio_macros.h"

int  mem_fd;
void *gpio_map;

#include <linux/i2c-dev.h>

// I/O access
volatile unsigned *gpio;

int open_i2c();
int close_i2c(int fd);
unsigned pad = GPA0_;

void sig_handler(int signo, siginfo_t *info, void *context);
int do_i2c(int fd);
int i2cfd;
int main(int argc, char **argv)
{
  int i;
  struct sigaction act = {.sa_sigaction=sig_handler, .sa_flags=SA_SIGINFO};
//  if (argc != 3) {
//    printf("usage: %s | aplay \n", argv[0]);
//  	return 1;
//  }

  i2cfd = open_i2c();

  // register signal
  sigemptyset(&act.sa_mask);
  sigaction(SIGUSR1, &act, NULL);
  sigaction(SIGKILL, &act, NULL);
  sigaction(SIGINT, &act, NULL);

  setup_gpio();
  for(i=0;i<8;i++)
    OUT_GPIO(pad, i);

  while(do_i2c(i2cfd));

  return 0;
}

int open_i2c(){
  int fd = open("/dev/i2c-0", O_RDWR), rst;
  if(fd<0) exit(1);
  if((rst=ioctl(fd, I2C_SLAVE_FORCE, 0x40)) < 0) exit(rst);
  return fd;
}
int close_i2c(int fd){
  return close(fd);
}

void sig_handler(int signo, siginfo_t *info, void *context){
  munmap((caddr_t)gpio_map, BLOCK_SIZE);
  close_i2c(i2cfd);
}
int do_i2c(int fd){
  __u8 reg = 0x10; /* Device register to access */
  __s32 res;
  unsigned char b;//, buf[10];
//  int pad, pin;
//  printf("pad:");
//  scanf("%d", &pad);
//  printf("pin:");
//  scanf("%d", &pin);

  /* Using SMBus commands */
//  res = i2c_smbus_read_word_data(fd, reg);
//  if (res < 0) {
    /* ERROR HANDLING: i2c transaction failed */
//  } else {
    /* res contains the read word */
//  }

  /* Using I2C Write, equivalent of
     i2c_smbus_write_word_data(fd, reg, 0x6543) */
//  buf[0] = reg;
//  buf[1] = 0x43;
//  buf[2] = 0x65;
//  if (write(fd, buf, 3) != 3) {
//  if (i2c_smbus_write_word_data(fd,reg, 0x6543) != 3) {
    /* ERROR HANDLING: i2c transaction failed */
//  }

  /* Using I2C Read, equivalent of i2c_smbus_read_byte(file) */
  if (read(fd, &b, 1) != 1) {
    printf("cannot raed i2s\n");
    /* ERROR HANDLING: i2c transaction failed */
    return 1;
  } else {
    printf("read i2s:%c\n", b);
    SET_VAL_GPIO(pad, b);

    /* buf[0] contains the read byte */
    return 1;
  }
}