//
// Created by alis on 06.12.23.
//
#include <linux/init.h>
#include <linux/module.h>
#include <linux/slab.h> /* kmalloc() */
#include <linux/cdev.h>

#ifndef STC_MY_DUMMY_DEVICE_H
#define STC_MY_DUMMY_DEVICE_H

#endif //STC_MY_DUMMY_DEVICE_H

// our device
struct dummy_dev {
    struct cdev* cdev;
};

//make singltone structure
static struct dummy_dev* dummy;


int my_dummy_device_init(void)
{
    dummy = kmalloc(sizeof(struct dummy_dev), GFP_KERNEL);
    dummy->cdev->owner = THIS_MODULE;
    printk(KERN_INFO "Load My dummy device\n"); //KERN_INFO
    return 0;
}

void my_dummy_device_exit(void)
{
    kfree(dummy);
    printk(KERN_INFO "Unload My dummy device\n");
}
