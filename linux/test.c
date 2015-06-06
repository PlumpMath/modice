#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>


#define GPIO_BASE 0xE0300000

#define GPA1 GPIO_BASE + 0x0020
#define GPB GPIO_BASE + 0x0040
#define GPC GPIO_BASE + 0x0060
#define ENUM_GPIO(NAME, REL) NAME=0x20*REL

#define BLOCK_SIZE (4*1024) // 0xE030_0000 ~ 0xE030_0FFF

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
//unsigned short gpio_pad_sizes[] = {8,5,8,5,7,8,6,8,8,8,4,8,3,7,7,8};
void *gpio_map;
unsigned pad = GPA0_;

// I/O access
volatile unsigned *gpio;

// GPIO setup macros. Always use INP_GPIO(x) before using OUT_GPIO(x) or SET_GPIO_ALT(x,y)
#define _INIT_GPIO(g, f) *(gpio + g + (f / 2))
#define INP_GPIO(g, f) _INIT_GPIO(g, f) &= ~(0xF << ((f % 2) * 4))
#define OUT_GPIO(g, f) _INIT_GPIO(g, f) |= (1 << ((f % 2) * 4)) //not sure on some pins which reset value is not zero
#define OUT_STRICT_GPIO(g, f) INP_GPIO(g, f); OUT_GPIO(g,f); //can sure
//#define ALT_GPIO(g, f) INP_GPIO(g, f); *(gpio+(g/10)) |= (((a)<=3?(a)+4:(a)==4?3:2)<<(((g)%10)*3))
//#define ALT_STRICT_GPIO(g, f) INP_GPIO(g, f); _INIT_GPIO(g, f) |= (1<<(1+(f%2)*4));

#define GPIO_DAT(g) *(gpio + g + 4)  // sets   bits which are 1 ignores bits which are 0

#define SET_GPIO(g, f) (GPIO_DAT(g) |= 1 << f)
#define SET_VAL_GPIO(g, f, v) (GPIO_DAT(g) |= v << f)
#define CLR_GPIO(g, f) (GPIO_DAT(g) &= ~(1 << f))
#define CLR_VAL_GPIO(g, f, v) (GPIO_DAT(g) &= ~(v << f))
#define GET_GPIO(g, f) (GPIO_DAT(g)&(1<<f)) // 0 if LOW, (1<<g) if HIGH
#define GET_STRICT_GPIO(g, f) (GET_GPIO(g)!=0) // 0 if LOW, 1 if HIGH

#define GPIO_PULL(g, f) *(gpio + g + 8 + (f/4)) // Pull up/pull down 0 = off, 1 = down, 2 = up

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
  int loc, len, i;
  if(argc != 3) return 1;
  loc = GPJ0_;
  len = atoi(argv[2]);

  setup_io();
//  loc = 24;
  pad = 0x20*loc;
  for(i=0;i<len;i++)
//    ALT_STRICT_GPIO(pad, i);
     OUT_STRICT_GPIO(pad, i);
  for(i=0;i<30;i++){
    CLR_VAL_GPIO(pad, 0, (0xFF>>(8-len)));
    usleep(1000*100);
    SET_VAL_GPIO(pad, 0, (0xFF>>(8-len)));
    usleep(1000*100);
  }
  munmap((caddr_t)gpio_map, BLOCK_SIZE);
  return 0;
}