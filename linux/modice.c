#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

#include <linux/fs.h>
#include <linux/cdev.h>

MODULE_LICENSE("GPL");
//#include <linux/list.h>
//#include <linux/slab.h>
#include <linux/uaccess.h>
//#include <linux/vmalloc.h>
//#include <linux/spinlock.h>
//#include <asm/delay.h>
//#include <linux/interrupt.h>
#include <linux/sched.h>
//#include <linux/rcupdate.h>
#include <linux/gpio.h>
//#include <asm/siginfo.h>

#include <linux/time.h>
//#include <sound/core.h>
//#include <sound/control.h>
//#include <sound/tlv.h>
//#include <sound/pcm.h>
//#include <sound/info.h>
//#include <sound/initval.h>

#include "modice.h"

//static unsigned int sync_irq;
char sndbuf[256]="";
unsigned gpio_size = S5PC1XX_GPIO_J0_NR;  //H1, L0, L2, K0 is already used
unsigned gpio = S5PC1XX_GPJ0(0);
int gpio_val = 0;
int gpio_cnt = 0;
static int DEV_READ(struct file *file, char *buf, size_t len, loff_t *lof){
    int i, val = 0;
    char *b;
    for(i=0;i<gpio_size;i++){
        gpio_direction_input(gpio+i);
        val |= gpio_get_value(gpio+i);
    }
//    itoa(val, sndbuf, 10);
    copy_to_user(buf, sndbuf, strlen(sndbuf)+1);
    DBG_PRTK("read\n");
    return 1;
}
struct timer_list timers;
void timer_act(unsigned long arg){
    gpio_set_value(gpio, arg%2);
    if (arg<100){
        timers.expires += 100;
        add_timer(&timers);
    }
}
static int DEV_WRITE(struct file *file, const char *buf, size_t len, loff_t *lof){
    int i;
//    copy_from_user(sndbuf, buf, len);

//    DBG_PRTK("write : %s\n", buf);
//    DBG_PRTK("write : %d\n", gpio_val = !gpio_val);

    if (gpio_val < 0xFF){
        gpio_val++;
        for(i=0;i<gpio_size;i++){
            gpio_direction_output(gpio+i, 0);
            gpio_set_value(gpio+i, (gpio_val>>i)&1);
        }
    }


    return 0;
}

static int DEV_OPEN(struct inode *inode, struct file *file){
	DBG_PRTK("open\n");
	return 0;
}

static int DEV_RELEASE(struct inode *inode, struct file *file){
  int i;
	DBG_PRTK("release\n");
	for(i=0;i<gpio_size;i++)
      gpio_direction_output(gpio+i, 0);

	return 0;
}

const struct file_operations DEV_FOPS =
{
    .read = DEV_READ,
    .write = DEV_WRITE,
    .open = DEV_OPEN,
    .release = DEV_RELEASE,
};

static dev_t dev_num;
static struct cdev *cd_cdev;

//static irqreturn_t DEV_PIR(int irq, void* data){
//    ku_pir_data d = {(long unsigned int)CURRENT_TIME.tv_sec, gpio_get_value(KUPIR_SENSOR) ? RISING : FALLING};
//
//    DBG_PRTK("Sensor data input : %s on %lu\n", rf_flag_name(d.rf_flag), d.timestamp);
//    add_pir_data(&d);
//    return IRQ_HANDLED;
//}
static void init_gpio(unsigned pin, unsigned val){
    if(gpio_request(pin,"GPIO")<0){
        DBG_PRTK("GPIO request error");
        return -1;
    }
//    gpio_direction_output(pin, val);
}
static int __init DEV_INIT(void){
//    int ret;
    int i;
    DBG_PRTK("Init Module\n");
    alloc_chrdev_region(&dev_num, 0, 1, DEV_NAME_STR);
    cd_cdev = cdev_alloc();
    cdev_init(cd_cdev, &DEV_FOPS);
    cdev_add(cd_cdev, dev_num, 1);

    for(i=0;i<gpio_size;i++)
        init_gpio(gpio+i, 1);

//    sync_irq = gpio_to_irq(KUPIR_SENSOR);
//    if ((ret = request_irq(sync_irq, DEV_PIR, IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING, xstr(DEV_PIR), NULL))){
//        DBG_PRTK(KERN_ERR " Unable to request IRQ: %d\n", ret);
//        free_irq(sync_irq, NULL);
//    }

    DBG_PRTK("Init Module done\n");
    return 0;
}

void __exit DEV_EXIT(void){
    int i;
//    free_irq(sync_irq, NULL);
    for(i=0;i<gpio_size;i++){
        gpio_direction_output(gpio+i, 0);
        gpio_free(gpio+i);
    }
    cdev_del(cd_cdev);
    unregister_chrdev_region(dev_num, 1);
    DBG_PRTK("Exit Module\n");
}

static int __init initer(void){ return DEV_INIT();}
static void __exit exiter(void){ DEV_EXIT(); }

module_init(initer);
module_exit(exiter);