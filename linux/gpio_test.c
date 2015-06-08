#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/mman.h>
#include <sched.h>

//#include <alsa/asoundlib.h>

#define GPIO_BASE 0xE0300000

#define BLOCK_SIZE (1024) // 0xE030_0000 ~ 0xE030_0FFF

#define ENUM_GPIO(NAME, REL) NAME=0x20*REL/4
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
  ENUM_GPIO(GPK2_,23),
  ENUM_GPIO(GPK3_,24),
  ENUM_GPIO(GPL0_,25),
  ENUM_GPIO(GPL1_,26),
  ENUM_GPIO(GPL2_,27),
  ENUM_GPIO(GPL3_,28),
  ENUM_GPIO(GPL4_,29)
};
void *gpio_map;

// I/O access
volatile unsigned *gpio;

// GPIO setup macros. Always use INP_GPIO(x) before using OUT_GPIO(x) or SET_GPIO_ALT(x,y)
#define _INIT_GPIO(g) *(gpio + g) //pin 0~7 -> 0
#define INP_GPIO(g, f) (_INIT_GPIO(g) &= ~(0xF << (f * 4))) // clear to 0000 = INPUT
#define _OUT_GPIO(g, f) (_INIT_GPIO(g) |= (1 << (f * 4))) // not sure on some pins which reset value is not zero
#define OUT_GPIO(g, f) INP_GPIO(g, f); _OUT_GPIO(g, f); //can sure
//#define ALT_GPIO(g, f) INP_GPIO(g, f); *(gpio+(g/10)) |= (((a)<=3?(a)+4:(a)==4?3:2)<<(((g)%10)*3)) // not implemented yet !!!!
//#define ALT_STRICT_GPIO(g, f) INP_GPIO(g, f); _INIT_GPIO(g, f) |= (1<<(1+(f%2)*4)); // not implemented yet !!!!

#define GPIO_DAT(g) *(gpio + g + 1)  // sets   bits which are 1 ignores bits which are 0

#define CLR_GPIO(g, f) (GPIO_DAT(g) &= ~(1 << f))
#define CLR_VAL_GPIO(g) (GPIO_DAT(g) &= 0)
#define SET_GPIO(g, f) (GPIO_DAT(g) |= 1 << f)
#define _SET_VAL_GPIO(g, v) (GPIO_DAT(g) |= v)
#define SET_VAL_GPIO(g, v) CLR_VAL_GPIO(g); _SET_VAL_GPIO(g,v)
#define GET_GPIO(g, f) (GPIO_DAT(g)&(1<<f)) // 0 if LOW, (1<<g) if HIGH
#define GET_STRICT_GPIO(g, f) (GET_GPIO(g)!=0) // 0 if LOW, 1 if HIGH
#define GET_VAL_GPIO(g) GPIO_DAT(g) // 0 if LOW, (1<<g) if HIGH

#define GPIO_PULL(g) *(gpio + g + 2) // Pull up/pull down 0 = off, 1 = down, 2 = up
#define GPIO_PULL_CLR(g, f) GPIO_PULL(g) |= ~(3 << (f*2))
#define _GPIO_PULL_DOWN(g, f) GPIO_PULL(g) |= (1 << (f*2))
#define GPIO_PULL_DOWN(g, f) GPIO_PULL_CLR(g,f); _GPIO_PULL_DOWN(g, f)
#define _GPIO_PULL_UP(g, f)  GPIO_PULL(g) |= (2 << (f*2))
#define GPIO_PULL_UP(g, f)  GPIO_PULL_CLR(g,f); _GPIO_PULL_UP(g, f)

void setup_io()
{
  int mem_fd;
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
   gpio = (volatile unsigned*)gpio_map;
}
void close_all(){
  munmap((caddr_t)gpio_map, BLOCK_SIZE);
  exit(0);
}
void sig_handler(int signo, siginfo_t *info, void *context){
  close_all();
}
/*void add_sine_wave(int16_t* buffer, int buffer_length, float frequency, float sampling_ratio, float amplitude)
{
    for (int i = 0; i < buffer_length; i++)
    {
        float theta = ((float)i / sampling_ratio) * M_PI;
        // make sure to correct for overflows and underflows
        buffer[i] += (int16_t)(sin(theta * frequency) * 32767.0f * amplitude);
    }
}*/
void setup_snd();
int main(int argc, char*argv[]){
//  int loc;
  unsigned i;
  int err;
  unsigned char c;
  struct sched_param sp;
  struct sigaction act = {.sa_sigaction=sig_handler, .sa_flags=SA_SIGINFO};

  // signal setting
  sigemptyset(&act.sa_mask);
  sigaction(SIGINT, &act, NULL);
  sigaction(SIGKILL, &act, NULL);
  sigaction(SIGSTOP, &act, NULL);

  //schedule priority setting
  memset(&sp, 0, sizeof(sp));
  sp.sched_priority = sched_get_priority_max(SCHED_FIFO);
  sched_setscheduler(0, SCHED_FIFO, &sp);
  mlockall(MCL_CURRENT | MCL_FUTURE);

  setup_io();

  _INIT_GPIO(GPJ0_) = 0x11111111; //OUT
  _INIT_GPIO(GPJ3_) = 0; //IN

  for(i=0;i<0xFFFFFFFF;i++){
    GPIO_DAT(GPJ0_) = i&0xFF;
    usleep(1);
    fprintf(stdout, "%X %X\n",i&0xFF, GPIO_DAT(GPJ3_));
  }
  GPIO_DAT(GPJ0_) = 0;

  close_all();
  return 0;
}