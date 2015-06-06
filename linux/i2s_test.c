#define GPIO_BASE 0xE0300000
#define I2S_321_BASE 0xF2200000  //3.2.1
#define I2S_320_BASE 0xF2200000  //3.2.0
#define I2S_50_BASE 0xF2200000  //5.0

#define ENUM_GPIO(NAME, REL) NAME=0x20*REL

enum gpio_init_loc {
    GPA0_,
    ENUM_GPIO(GPA1_,1),
    ENUM_GPIO(GPB_,2),
    ENUM_GPIO(GPC_,3),
    ENUM_GPIO(GPD_,4),
    ENUM_GPIO(GPE0_,5),
    ENUM_GPIO(GPE1_,6),
    ENUM_GPIO(GPF0_,7),
    ENUM_GPIO(GPF1_,8),
    ENUM_GPIO(GPF2_,9),
    ENUM_GPIO(GPF3_,10),
    ENUM_GPIO(GPG0_,11),
    ENUM_GPIO(GPG1_,12),
    ENUM_GPIO(GPG2_,13),
    ENUM_GPIO(GPG3_,14),
    ENUM_GPIO(GPH0_,96), // memory jumped
    ENUM_GPIO(GPH1_,97),
    ENUM_GPIO(GPH2_,98),
    ENUM_GPIO(GPH3_,99),
    ENUM_GPIO(GPI_,15), // memory jumped back
    ENUM_GPIO(GPJ0_,16),
    ENUM_GPIO(GPJ1_,17),
    ENUM_GPIO(GPJ2_,18),
    ENUM_GPIO(GPJ3_,19),
    ENUM_GPIO(GPJ4_,20),
    ENUM_GPIO(GPK0_,21),
    ENUM_GPIO(GPK1_,22),
    ENUM_GPIO(GPK3_,23),
    ENUM_GPIO(GPL0_,24),
    ENUM_GPIO(GPL1_,25),
    ENUM_GPIO(GPL2_,26),
    ENUM_GPIO(GPL3_,27),
    ENUM_GPIO(GPL4_,28)
    };

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

#define BLOCK_SIZE (4*1024) // 0xE030_0000 ~ 0xE030_0FFF

int  mem_fd;
void *gpio_map;

#include <linux/i2c-dev.h>

// I/O access
volatile uint8_t *gpio;


// GPIO setup macros. Always use INP_GPIO(x) before using OUT_GPIO(x) or SET_GPIO_ALT(x,y)
#define _INIT_GPIO(g, f) *(gpio + g + (f / 2))
#define INP_GPIO(g, f) _INIT_GPIO(g, f) &= ~(0xF << ((f % 2) * 4))
#define OUT_GPIO(g, f) _INIT_GPIO(g, f) |= (1 << ((f % 2) * 4)) //not sure on some pins which reset value is not zero
#define OUT_STRICT_GPIO(g, f) INP_GPIO(g, f); OUT_GPIO(g,f); //can sure
//#define SET_GPIO_ALT(g,a) *(gpio+(g/10)) |= (((a)<=3?(a)+4:(a)==4?3:2)<<(((g)%10)*3))

#define GPIO_DAT(g, f) *(gpio + g + 4 + (f/8))  // sets   bits which are 1 ignores bits which are 0

#define SET_GPIO(g, f) (GPIO_DAT(g,f) |= 1 << f)
#define SET_VAL_GPIO(g, f, v) (GPIO_DAT(g,f) |= v << f)
#define CLR_GPIO(g, f) (GPIO_DAT(g,f) &= ~(1 << f))
#define CLR_VAL_GPIO(g, f, v) (GPIO_DAT(g,f) &= ~(v << f))
#define GET_GPIO(g, f) (GPIO_DAT(g,f)&(1<<f)) // 0 if LOW, (1<<g) if HIGH
#define GET_STRICT_GPIO(g, f) (GET_GPIO(g,f)!=0) // 0 if LOW, 1 if HIGH

#define GPIO_PULL(g, f) *(gpio + g + 8 + (f/4)) // Pull up/pull down 0 = off, 1 = down, 2 = up

int open_i2c();
int close_i2c(int fd);
void setup_io();
unsigned pad = GPA0_;
//
// Set up a memory regions to access GPIO
//
void setup_io()
{
  int i;
  struct sched_param sp;
  memset(&sp, 0, sizeof(sp));
  sp.sched_priority = sched_get_priority_max(SCHED_FIFO);
  sched_setscheduler(0, SCHED_FIFO, &sp);
  mlockall(MCL_CURRENT | MCL_FUTURE);

   /* open /dev/mem */
   if ((mem_fd = open("/dev/mem", O_RDWR|O_SYNC) ) < 0) {
      printf("can't open /dev/mem \n");
      exit(-1);
   }

   /* mmap GPIO */
   gpio_map = mmap(
      NULL,             //Any adddress in our space will do
      BLOCK_SIZE,       //Map length
      PROT_READ|PROT_WRITE,// Enable reading & writting to mapped memory
      MAP_SHARED,       //Shared with other processes
      mem_fd,           //File to map
      GPIO_BASE         //Offset to GPIO peripheral
   );

   close(mem_fd); //No need to keep mem_fd open after mmap

   if (gpio_map == MAP_FAILED) {
      printf("mmap error %d\n", (int)gpio_map);//errno also set!
      exit(-1);
   }

   // Always use volatile pointer!
   gpio = (volatile uint8_t*)gpio_map;
   for(i=0;i<8;i++)
     OUT_STRICT_GPIO(pad, i);
}

void sig_handler(int signo, siginfo_t *info, void *context);
int do_i2c(int fd);
int i2cfd;
int main(int argc, char **argv)
{
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

  setup_io();
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
    CLR_VAL_GPIO(pad, 0, 0xFF);
    SET_VAL_GPIO(pad, 0, b);

    /* buf[0] contains the read byte */
    return 1;
  }
}