obj-m += my_dummy_device.o
obj-m += dummy_register.o

KERN_DIR ?= /usr/src/linux-headers-$(shell uname -r)/
PWD := $(shell pwd)

default:
	$(MAKE) -C $(KERN_DIR) M=$(PWD) modules
	#rm -rf  *~ core .depend .*.cmd  *.mod.c .tmp_versions *.order *.symvers *.mod

clean:
	rm -rf *.o *~ core .depend .*.cmd *.ko *.mod.c .tmp_versions *.order *.symvers *.mod *.mod.o

    #

#obj-m += my_dummy_device.o
#
#all:
#	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
#
#clean:
#	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean