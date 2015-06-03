/* macro token/string utilities */
#define xstr(s) str(s)
#define str(s) #s
#define __CONCAT(a,b,c) a ## b ## c
#define _CONCAT(x, y) x ## y
#define CONCAT(x, y) _CONCAT(x, y)

/* device names */
//#define NAME ku_ipc //defined from gcc -D option
#define DEV_NAME POSTFIX(NAME,dev)
#define NAME_STR xstr(NAME)
#define DEV_NAME_STR xstr(DEV_NAME)

/* macro debug utility */
#ifdef DEBUG
	#define _DBG_PRTK(NAME_STR, ...) printk(NAME_STR" "__VA_ARGS__)
	#define DBG_PRTK(...) _DBG_PRTK(NAME_STR, __VA_ARGS__)
#else
	#define DBG_PRTK(...)
#endif

/* device user function names' generalization */
#define POSTFIX(NAME, PFIX) __CONCAT(NAME, _, PFIX)
#define DEV_OPEN POSTFIX(NAME, open)
#define DEV_RELEASE POSTFIX(NAME, release)

#define DEV_CLOSE POSTFIX(NAME, close)
#define DEV_INIT POSTFIX(NAME, init)
#define DEV_IOCTL POSTFIX(NAME, ioctl)

#define DEV_FOPS POSTFIX(NAME, fops)

#define DEV_WRITE POSTFIX(NAME, write)
#define DEV_READ POSTFIX(NAME, read)

#define DEV_FASYNC POSTFIX(NAME, fasync)

#define DEV_EXIT POSTFIX(NAME, exit)


/* Limits */
#define KUPIR_MAX_MSG 256

/* Sensors */
#define KUPIR_SENSOR 17

/* IOCTL */
#include "ku_pir_ioctl.h"

/* List Entries */
typedef struct _ku_pir_entry{
	struct list_head entry;
	ku_pir_data data;
} ku_pir_entry;