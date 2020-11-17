KERNELDIR ?= /lib/modules/$(shell uname -r)/build

PWD := $(shell pwd)

modules: load 
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

load: $(wildcard load/*.c load/*.h)
	$(MAKE) -C load/

clean:
	rm -rf *.o *.ko .*.cmd *.mod.* modules.order Module.symvers .tmp_versions
	rm -rf load/*.o
obj-m := diagnose.o
