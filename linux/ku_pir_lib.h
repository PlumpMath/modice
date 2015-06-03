#define xstr(s) str(s)
#define str(s) #s
#define _CONCAT(x, y) x ## y
#define CONCAT(x, y) _CONCAT(x, y)

#define _DEV_NAME(NAME) _CONCAT(NAME, _dev)
#define DEV_NAME _DEV_NAME(NAME)
#define NAME_STR xstr(NAME)
#define DEV_NAME_STR xstr(DEV_NAME)

/* IOCTL */
#include "ku_pir_ioctl.h"

/* user functions */
void sig_handler(int, siginfo_t *, void *);
int ku_pir_insertData(int, long unsigned int, int);
int ku_pir_open();
int ku_pir_close(int);

ku_pir_data *ku_pir_asynchronous(int, long unsigned int);
ku_pir_data *ku_pir_nonblocking(int, long unsigned int);
ku_pir_data *ku_pir_blocking(int, long unsigned int);

/* time associated value and macros */
#define SEC 1
#define MIN 60*SEC
#define HOUR 60*MIN
#define DAY 24*HOUR
#define RANDRANGE(START, END) (rand()%(END - START) + START)