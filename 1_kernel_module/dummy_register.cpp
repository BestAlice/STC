#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>   /* printk() */
#include <linux/slab.h>     /* kmalloc() */
#include <linux/fs.h>       /* everything... */
#include <linux/errno.h>    /* error codes */
#include <linux/types.h>    /* size_t */
#include <linux/fcntl.h>    /* O_ACCMODE */
#include <linux/cdev.h>
#include <asm/uaccess.h>    /* copy_*_user */

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Dmitry");


struct dummy_dev {
    unsigned long size;       /* Amount of data stored here. */
    unsigned int access_key;  /* Used by dummyuid and dummypriv. */
    struct cdev cdev;     /* Char device structure. */
};

struct dummy_dev* dummy;
//
//struct file_operations dummy_fops = {
//        .owner =    THIS_MODULE,
//        .llseek =   dummy_llseek,
//        .read =     dummy_read,
//        .write =    dummy_write,
//        .open =     dummy_open,
//        .release =  dummy_release,
//};
int dummy_major = 0;

int dummy_register_init(void){
    int dev = 0;
    int result = 0;

    result = alloc_chrdev_region(&dev, 0, 1, "dummy");
    dummy_major = MAJOR(dev);

    dummy = kmalloc(sizeof(struct dummy_dev), GFP_KERNEL);

//    dummy.quantum = dummy_quantum;
//    dummy.qset = dummy_qset;
//    mutex_init(&dummy.mutex);

    int err, devno = MKDEV(dummy_major, 0);
//    cdev_init(dummy->cdev, &dummy_fops);
    dummy->cdev.owner = THIS_MODULE;
//    dummy->cdev.ops = &dummy_fops;
    err = cdev_add (dummy->cdev, devno, 1);
    /* Fail gracefully if need be. */
    if (err)
        printk(KERN_NOTICE "Error %d adding dummy%d", err, index);
    else
        printk(KERN_INFO "dummy: %d add success\n", index);
}

 void dummy_register_exit(void) {
     int i;
     dev_t devno = MKDEV(dummy_major, 0);
     /* Get rid of our char dev entries. */

     //dummy_trim(dummy_devices + i);
     dev_del(dummy->cdev);
     kfree(dummy);

     /* cleanup_module is never called if registering failed. */
     unregister_chrdev_region(devno, 1);
     printk(KERN_INFO "dummy: cleanup success\n");
}

module_init(dummy_register_init);
module_exit(dummy_register_exit);