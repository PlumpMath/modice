#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

#include <linux/fs.h>
#include <linux/cdev.h>

MODULE_LICENSE("GPL");
#include <linux/sched.h>
#include <linux/list.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include <linux/vmalloc.h>
//#include <linux/spinlock.h>
//#include <asm/delay.h>
#include <linux/interrupt.h>
#include <linux/sched.h>
#include <linux/rcupdate.h>
#include <linux/gpio.h>
#include <asm/siginfo.h>

#include <linux/time.h>

#include <sound/core.h>
#include <sound/control.h>
#include <sound/tlv.h>
#include <sound/pcm.h>
#include <sound/info.h>
#include <sound/initval.h>

#include "ku_pir.h"

static unsigned int sync_irq;
static int fasync_trg_pid = 0;

static int DEV_READ(struct file *file, char *buf, size_t len, loff_t *lof){
//    copy_to_user(buf, entry->data, len);
    DBG_PRTK("read\n");
    return 0;
}

static int DEV_WRITE(struct file *file, const char *buf, size_t len, loff_t *lof){
//    copy_from_user(entry->data, buf, len);
    DBG_PRTK("write : %s\n", buf);
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

static int DEV_FASYNC(int fd, struct file *file, int mode){
	struct siginfo sinfo={.si_signo = SIGUSR1, .si_errno=0, .si_code=0, .si_addr=0, .si_value.sival_int=0};
  struct task_struct *t;
	DBG_PRTK("fasync\n");
  if (!fasync_trg_pid || !(t=pid_task(find_vpid(fasync_trg_pid), PIDTYPE_PID))) return 1;
//  kill_pid_info_as_uid(sinfo.si_signo, &sinfo, fasync_trg_pid, 0,0,0);
  send_sig_info(sinfo.si_signo, &sinfo, t);
  fasync_trg_pid = 0;
  return 0;
}
const struct file_operations DEV_FOPS =
{
    .unlocked_ioctl = DEV_IOCTL,
    .read = DEV_READ,
    .write = DEV_WRITE,
    .open = DEV_OPEN,
    .release = DEV_RELEASE,
    .fasync = DEV_FASYNC,
};

static dev_t dev_num;
static struct cdev *cd_cdev;

static irqreturn_t sensor_pir(int irq, void* data){
    ku_pir_data d = {(long unsigned int)CURRENT_TIME.tv_sec, gpio_get_value(KUPIR_SENSOR) ? RISING : FALLING};

    DBG_PRTK("Sensor data input : %s on %lu\n", rf_flag_name(d.rf_flag), d.timestamp);
    add_pir_data(&d);
    return IRQ_HANDLED;
}
static int __init DEV_INIT(void){
    int ret;
    DBG_PRTK("Init Module\n");
    alloc_chrdev_region(&dev_num, 0, 1, DEV_NAME_STR);
    cd_cdev = cdev_alloc();
    cdev_init(cd_cdev, &DEV_FOPS);
    cdev_add(cd_cdev, dev_num, 1);

    gpio_request_one(KUPIR_SENSOR, GPIOF_IN, str(PIR));

    sync_irq = gpio_to_irq(KUPIR_SENSOR);
    if ((ret = request_irq(sync_irq, sensor_pir, IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING, "sensor_irq", NULL))){
        DBG_PRTK(KERN_ERR " Unable to request IRQ: %d\n", ret);
        free_irq(sync_irq, NULL);
    }

    return 0;
}

void __exit DEV_EXIT(void){
    ku_pir_entry *cp, *t;

    list_for_each_entry_safe(cp, t, &pir_list, entry){ // clear list
        list_del(&cp->entry);
        kfree(cp);
    }
    gpio_free(KUPIR_SENSOR);
    free_irq(sync_irq, NULL);
    cdev_del(cd_cdev);
    unregister_chrdev_region(dev_num, 1);
    DBG_PRTK("Exit Module\n");
}

static int __init initer(void){ return DEV_INIT();}
static void __exit exiter(void){ DEV_EXIT(); }

module_init(initer);
module_exit(exiter);