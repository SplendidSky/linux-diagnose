#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/ioctl.h>

#include "diagnose.h"
#include "load/load.h"

extern long load_ioctl(struct file*, unsigned int, unsigned long);

struct diag_dev {
	struct cdev cdev;
};

static struct diag_dev diag_dev;
static int major;

static long diag_ioctl(struct file *filp, unsigned int cmd, unsigned long args) {
	switch (_IOC_TYPE(cmd)) {
	case 'l':
		load_ioctl(filp, cmd, args);
		break;
	default:
		printk("No cmd match");
	}
	return 0;
}

struct file_operations diag_ops = {
	.owner = THIS_MODULE,
        .unlocked_ioctl = diag_ioctl,
};

static int __init diagnose_module_init(void) {
 	int ret = -1;
	dev_t dev;
	if (ret = alloc_chrdev_region(&dev, 0, 1, "diagnose"))
		goto reg_err;
	
	major = MAJOR(dev);
	cdev_init(&diag_dev.cdev, &diag_ops);
	diag_dev.cdev.owner = THIS_MODULE;

	if (ret = cdev_add(&diag_dev.cdev, dev, 1))
		goto add_err;

	printk("diagnose ko init\n");
    	return 0;

add_err:
	unregister_chrdev_region(dev, 1);
reg_err:
	return ret;
}

static void __exit diagnose_module_exit(void) {
	cdev_del(&diag_dev.cdev);
	unregister_chrdev_region(MKDEV(major, 0), 1);
	printk("diagnose ko exit\n");
}

module_init(diagnose_module_init);
module_exit(diagnose_module_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Weichen Chen <splendidsky.cwc@alibaba-inc.com");
MODULE_DESCRIPTION("Linux diagnose module");
