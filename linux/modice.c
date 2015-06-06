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
unsigned gpio = S5PC1XX_GPA0(0);
int gpio_val = 1;
static int DEV_READ(struct file *file, char *buf, size_t len, loff_t *lof){
    sndbuf[0] = '0'+gpio_get_value(gpio);
    sndbuf[1] = '\0';
    copy_to_user(buf, sndbuf, 2);
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

    DBG_PRTK("write : %d\n", gpio_val = !gpio_val);

//    gpio_request(gpio, "GPIO");
    for(i=0;i<S5PC1XX_GPIO_J0_NR;i++)
        gpio_set_value(S5PC1XX_GPJ0(i), gpio_val);
//    for(i=0;i<S5PC1XX_GPIO_J3_NR;i++)
//        gpio_set_value(S5PC1XX_GPJ3(i), gpio_val);
//    for(i=0;i<S5PC1XX_GPIO_J2_NR;i++)
//        gpio_set_value(S5PC1XX_GPJ2(i), gpio_val);
//    setup_timer(&timers, timer_act, 0);
//    timers.expires = jiffies+100;
//    add_timer(&timers);

    return 0;
}

static int DEV_OPEN(struct inode *inode, struct file *file){
	DBG_PRTK("open\n");
	return 0;
}

static int DEV_RELEASE(struct inode *inode, struct file *file){
	DBG_PRTK("release\n");
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
    gpio_direction_output(pin, val); //H3, H1, L, K0 is already used
}
static int __init DEV_INIT(void){
//    int ret;
    int i;
    DBG_PRTK("Init Module\n");
//    register_chrdev(0, DEV_NAME_STR, &DEV_FOPS);
    alloc_chrdev_region(&dev_num, 0, 1, DEV_NAME_STR);
    cd_cdev = cdev_alloc();
    cdev_init(cd_cdev, &DEV_FOPS);
    cdev_add(cd_cdev, dev_num, 1);


    for(i=0;i<S5PC1XX_GPIO_J0_NR;i++)
        init_gpio(S5PC1XX_GPJ0(i), 1);
//    for(i=0;i<S5PC1XX_GPIO_J3_NR;i++)
//        init_gpio(S5PC1XX_GPJ3(i), 0);
//    for(i=0;i<S5PC1XX_GPIO_J2_NR;i++) //LEDs
//        init_gpio(S5PC1XX_GPJ2(i), 0);
//    gpio_set_value(gpio, gpio_val);
//    gpio_request_array(gpio_out, ARRAY_SIZE(gpio_out));
//    gpio_request_array(gpio_in, ARRAY_SIZE(gpio_in));


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
    gpio_free(gpio);
    for(i=0;i<S5PC1XX_GPIO_J0_NR;i++)
        gpio_free(S5PC1XX_GPJ0(i));
    for(i=0;i<S5PC1XX_GPIO_J3_NR;i++)
        gpio_free(S5PC1XX_GPJ3(i));
//    for(i=0;i<S5PC1XX_GPIO_J2_NR;i++)
//        gpio_free(S5PC1XX_GPJ2(i));
    cdev_del(cd_cdev);
    unregister_chrdev_region(dev_num, 1);
    DBG_PRTK("Exit Module\n");
}

static int __init initer(void){ return DEV_INIT();}
static void __exit exiter(void){ DEV_EXIT(); }

module_init(initer);
module_exit(exiter);