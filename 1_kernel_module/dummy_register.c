#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>   /* printk() */
#include <linux/fs.h>       /* everything... */
#include <linux/errno.h>    /* error codes */
#include <linux/types.h>    /* size_t */
#include <linux/fcntl.h>    /* O_ACCMODE */
#include <linux/cdev.h>
#include <asm/uaccess.h>    /* copy_*_user */
#include "my_dummy_device.h"

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Dmitry");


int dummy_major = 0;

int dummy_register_init(void){
    printk(KERN_INFO "Start registration My dummy device\n");
    int dev = 0;
    int result = 0;

    //get major number of device from kernel
    result = alloc_chrdev_region(&dev, 0, 1, "dummy");
    dummy_major = MAJOR(dev);

    //create device
    my_dummy_device_init();

    //register device
    int err, devno = MKDEV(dummy_major, 0);
    err = cdev_add(dummy->cdev, devno, 1);
    // Fail gracefully if need be.
    if (err) {
        printk(KERN_NOTICE
        "Error %d adding dummy%d", err, 0);
        my_dummy_device_exit();
    } else
        printk(KERN_INFO "dummy: %d add success\n", 0);

    return 0;
}

 void dummy_register_exit(void) {
     dev_t devno = MKDEV(dummy_major, 0);

     /* cleanup */
     cdev_del(dummy->cdev);
     unregister_chrdev_region(devno, 1);
     my_dummy_device_exit();

     printk(KERN_INFO "dummy: cleanup success\n");
     printk(KERN_INFO "Finish dummy register\n");
}

module_init(dummy_register_init);
module_exit(dummy_register_exit);