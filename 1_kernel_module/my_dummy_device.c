#include <linux/init.h>
#include <linux/module.h>
MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Dmitry");


int my_dummy_device_init(void)
{
    printk(KERN_INFO "Load My dummy device\n"); //KERN_INFO
    return 0;
}
void my_dummy_device_exit(void)
{
    printk(KERN_INFO "Unload My dummy device\n");
}


module_init(my_dummy_device_init);
module_exit(my_dummy_device_exit);