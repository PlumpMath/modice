#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/mman.h>
#include <alsa/asoundlib.h>

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
//#define ALT_GPIO(g, f) INP_GPIO(g, f); *(gpio+(g/10)) |= (((a)<=3?(a)+4:(a)==4?3:2)<<(((g)%10)*3))
//#define ALT_STRICT_GPIO(g, f) INP_GPIO(g, f); _INIT_GPIO(g, f) |= (1<<(1+(f%2)*4));

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

int main(int argc, char*argv[]){
  setup_io();
  printf("%x\n", _INIT_GPIO(GPA0_)); // 22222222
  printf("%x\n", _INIT_GPIO(GPA1_)); // 2222
  printf("%x\n", _INIT_GPIO(GPB_)); // 0
  printf("%x\n", _INIT_GPIO(GPC_)); // 44444
  printf("%x\n", _INIT_GPIO(GPD_)); // 22022
  printf("%x\n", _INIT_GPIO(GPE0_)); // 22222222
  printf("%x\n", _INIT_GPIO(GPE1_)); // 222222
  printf("%x\n", _INIT_GPIO(GPF0_)); // 22222200
  printf("%x\n", _INIT_GPIO(GPF1_)); // 22222222
  printf("%x\n", _INIT_GPIO(GPF2_)); // 11111111
  printf("%x\n", _INIT_GPIO(GPF3_)); // 0
  printf("%x\n", _INIT_GPIO(GPG0_)); // 0
  printf("%x\n", _INIT_GPIO(GPG1_)); // 0
  printf("%x\n", _INIT_GPIO(GPG2_)); // 0
  printf("%x\n", _INIT_GPIO(GPG3_)); // 0
  printf("%x\n", _INIT_GPIO(GPH0_)); // ERR
  printf("%x\n", _INIT_GPIO(GPH1_)); // ERR
  printf("%x\n", _INIT_GPIO(GPH2_)); // ERR
  printf("%x\n", _INIT_GPIO(GPH3_));
  printf("%x\n", _INIT_GPIO(GPI_)); // 0
  printf("%x\n", _INIT_GPIO(GPJ0_)); // 0
  printf("%x\n", _INIT_GPIO(GPJ1_)); // 0
  printf("%x\n", _INIT_GPIO(GPJ2_)); // ff
  printf("%x\n", _INIT_GPIO(GPJ3_)); // ff
  printf("%x\n", _INIT_GPIO(GPJ4_)); // 0
  printf("%x\n", _INIT_GPIO(GPK0_)); // 0
  printf("%x\n", _INIT_GPIO(GPK1_)); // 0
  printf("%x\n", _INIT_GPIO(GPK2_)); // 0
  printf("%x\n", _INIT_GPIO(GPK3_)); // 200100
  printf("%x\n", _INIT_GPIO(GPL0_)); // 0
  printf("%x\n", _INIT_GPIO(GPL1_)); // 0
  printf("%x\n", _INIT_GPIO(GPL2_)); // 0
  printf("%x\n", _INIT_GPIO(GPL3_)); // 0
  printf("%x\n", _INIT_GPIO(GPL4_)); // 0
 printf(" \n");

  printf("%x\n", GPIO_PULL(GPA0_)); // 5555
  printf("%x\n", GPIO_PULL(GPA1_)); // 1695
  printf("%x\n", GPIO_PULL(GPB_)); // 5555
  printf("%x\n", GPIO_PULL(GPC_)); // 5
  printf("%x\n", GPIO_PULL(GPD_)); // 5555
  printf("%x\n", GPIO_PULL(GPE0_)); // 55
  printf("%x\n", GPIO_PULL(GPE1_)); // 885
  printf("%x\n", GPIO_PULL(GPF0_)); // 0
  printf("%x\n", GPIO_PULL(GPF1_)); // 0
  printf("%x\n", GPIO_PULL(GPF2_)); // 0
  printf("%x\n", GPIO_PULL(GPF3_)); // 8555
  printf("%x\n", GPIO_PULL(GPG0_)); // 8555
  printf("%x\n", GPIO_PULL(GPG1_)); // 0
  printf("%x\n", GPIO_PULL(GPG2_)); // 0
  printf("%x\n", GPIO_PULL(GPG3_)); // 0
  printf("%x\n", GPIO_PULL(GPH0_)); // ERR
  printf("%x\n", GPIO_PULL(GPH1_)); // ERR
  printf("%x\n", GPIO_PULL(GPH2_)); // ERR
  printf("%x\n", GPIO_PULL(GPH3_));
  printf("%x\n", GPIO_PULL(GPI_)); // 0
  printf("%x\n", GPIO_PULL(GPJ0_)); // 0
  printf("%x\n", GPIO_PULL(GPJ1_)); // 0
  printf("%x\n", GPIO_PULL(GPJ2_)); // ff
  printf("%x\n", GPIO_PULL(GPJ3_)); // ff
  printf("%x\n", GPIO_PULL(GPJ4_)); // 0
  printf("%x\n", GPIO_PULL(GPK0_)); // 0
  printf("%x\n", GPIO_PULL(GPK1_)); // 0
  printf("%x\n", GPIO_PULL(GPK2_)); // 0
  printf("%x\n", GPIO_PULL(GPK3_)); // 5955
  printf("%x\n", GPIO_PULL(GPL0_)); // 0
  printf("%x\n", GPIO_PULL(GPL1_)); // 0
  printf("%x\n", GPIO_PULL(GPL2_)); // 0
  printf("%x\n", GPIO_PULL(GPL3_)); // 0
  printf("%x\n", GPIO_PULL(GPL4_)); // 0
 printf(" \n");
  printf("%x\n", _INIT_GPIO(GPA0_)); // 22222222
  printf("%x\n", _INIT_GPIO(GPA1_)); // 22022
  printf("%x\n", _INIT_GPIO(GPB_)); // 22222222
  printf("%x\n", _INIT_GPIO(GPC_)); // 200
  printf("%x\n", _INIT_GPIO(GPD_)); // 0
  printf("%x\n", _INIT_GPIO(GPE0_)); // 0
  printf("%x\n", _INIT_GPIO(GPE1_)); // 44444444
  printf("%x\n", _INIT_GPIO(GPF0_)); // 22222222
  printf("%x\n", _INIT_GPIO(GPF1_)); // 0
  printf("%x\n", _INIT_GPIO(GPF2_)); // 0
  printf("%x\n", _INIT_GPIO(GPF3_)); // 8555
  printf("%x\n", _INIT_GPIO(GPG0_)); // 8555
  printf("%x\n", _INIT_GPIO(GPG1_)); // 0
  printf("%x\n", _INIT_GPIO(GPG2_)); // 0
  printf("%x\n", _INIT_GPIO(GPG3_)); // 0
  printf("%x\n", _INIT_GPIO(GPH0_)); // ERR
  printf("%x\n", _INIT_GPIO(GPH1_)); // ERR
  printf("%x\n", _INIT_GPIO(GPH2_)); // ERR
  printf("%x\n", _INIT_GPIO(GPH3_));
  printf("%x\n", _INIT_GPIO(GPI_)); // 0
  printf("%x\n", _INIT_GPIO(GPJ0_)); // 0
  printf("%x\n", _INIT_GPIO(GPJ1_)); // 0
  printf("%x\n", _INIT_GPIO(GPJ2_)); // ff
  printf("%x\n", _INIT_GPIO(GPJ3_)); // ff
  printf("%x\n", _INIT_GPIO(GPJ4_)); // 0
  printf("%x\n", _INIT_GPIO(GPK0_)); // 0
  printf("%x\n", _INIT_GPIO(GPK1_)); // 0
  printf("%x\n", _INIT_GPIO(GPK2_)); // 0
  printf("%x\n", _INIT_GPIO(GPK3_)); // 200100
  printf("%x\n", _INIT_GPIO(GPL0_)); // 0
  printf("%x\n", _INIT_GPIO(GPL1_)); // 0
  printf("%x\n", _INIT_GPIO(GPL2_)); // 0
  printf("%x\n", _INIT_GPIO(GPL3_)); // 0
  printf("%x\n", _INIT_GPIO(GPL4_)); // 0

  munmap((caddr_t)gpio_map, BLOCK_SIZE);
  return 0;
}