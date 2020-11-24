KERNELDIR ?= /lib/modules/$(shell uname -r)/build

PWD := $(shell pwd)

modules: 
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

clean:
	rm -rf *.o *.ko .*.cmd *.mod.* modules.order Module.symvers .tmp_versions
	rm -rf load/*.o

obj-m := diag.o
diag-objs = diagnose.o load/load.o
