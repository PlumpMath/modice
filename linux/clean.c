#include <linux/kernel.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/cdev.h>

MODULE_LICENSE("GPL");

static int r_init(void);
static void r_cleanup(void);

module_init(r_init);
module_exit(r_cleanup);


const struct file_operations my_fops =
{
//    .read = 0,
//    .write = DEV_WRITE,
//    .open = DEV_OPEN,
//    .release = DEV_RELEASE,
};

static struct cdev r_cdev;
static int r_init(void)
{
    int ret=0;
    dev_t dev;
    dev = MKDEV(222,0);
    if (alloc_chrdev_region(dev, 0, 2, "test"))
        goto error;

    cdev_init(&r_cdev, &my_fops);
    ret = cdev_add(&r_cdev, dev, 2);
    return 0;
error:
    unregister_chrdev_region(dev, 2);
    return 0;
}


static void r_cleanup(void)
{
    cdev_del(&r_cdev);
    unregister_chrdev_region(MKDEV(222,0),2);
    unregister_chrdev_region(MKDEV(248,0),2);
    unregister_chrdev_region(MKDEV(249,0),2);
    unregister_chrdev_region(MKDEV(250,0),2);
    unregister_chrdev_region(MKDEV(251,0),2);
    unregister_chrdev_region(MKDEV(252,0),2);
    return;
}