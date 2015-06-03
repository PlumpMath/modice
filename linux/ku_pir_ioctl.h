/* IOCTL */
#define IOCTL_START_NUM 0x80
#define IOCTL_MAGIC_NUM 'z'
#define IOCTL_NUM(IND) IOCTL_START_NUM+IND

#define IOCTL_ASK _IOWR(IOCTL_MAGIC_NUM, IOCTL_NUM(0), unsigned long)
#define IOCTL_SET _IOWR(IOCTL_MAGIC_NUM, IOCTL_NUM(1), unsigned long)

/* Data through IOCTL */
//enum rf_flags{RISING, FALLING};
#define RISING 0
#define FALLING 1
#define rf_flag_name(VAR) (VAR==RISING?"Rising":VAR==FALLING?"Falling":"None")

typedef struct _ku_pir_data{
  long unsigned int timestamp;
  int rf_flag;
} ku_pir_data;