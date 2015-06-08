// GPIO setup macros. Always use INP_GPIO(x) before using OUT_GPIO(x) or SET_GPIO_ALT(x,y)
#define _INIT_GPIO(g) *(gpio + g) //pin 0~7 -> 0
#define INP_GPIO(g, f) (_INIT_GPIO(g) &= ~(0xF << (f * 4))) // clear to 0000 = INPUT
#define _OUT_GPIO(g, f) (_INIT_GPIO(g) |= (1 << (f * 4))) // not sure on some pins which reset value is not zero
#define OUT_GPIO(g, f) INP_GPIO(g, f); _OUT_GPIO(g, f); //can sure
//#define ALT_GPIO(g, f) INP_GPIO(g, f); *(gpio+(g/10)) |= (((a)<=3?(a)+4:(a)==4?3:2)<<(((g)%10)*3)) // not implemented yet !!!!
//#define ALT_STRICT_GPIO(g, f) INP_GPIO(g, f); _INIT_GPIO(g, f) |= (1<<(1+(f%2)*4)); // not implemented yet !!!!

#define _GPIO_DAT(g) (gpio + g + 1)  // sets   bits which are 1 ignores bits which are 0
#define GPIO_DAT(g) *_GPIO_DAT(g)  // sets   bits which are 1 ignores bits which are 0

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