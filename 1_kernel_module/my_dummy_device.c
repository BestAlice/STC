
#include "my_dummy_device.h"
MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Dmitry");

//main body moved into header file

module_init(my_dummy_device_init);
module_exit(my_dummy_device_exit);