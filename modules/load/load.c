#include <linux/fs.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/ioctl.h>

#include "load.h"

static int active = 0;

long load_ioctl(struct file *filp, unsigned int cmd, unsigned long args) {
	struct task_struct *g, *p;
	
	if (_IOC_TYPE(cmd) != LOAD_MAGIC) {
		printk("Invalid load cmd");
		return -ENOTTY;
	}
	
	switch (cmd) {
	case LOAD_ACTIVE:
		if (copy_from_user(&active, (unsigned int*) args, sizeof(unsigned int))) {
			return -EFAULT;
		}
		break;
	default:
		printk("Invalid load cmd");
		return -ENOTTY;
	}
	
	if (active) {
		do_each_thread(g, p) {
            		if (p->state & TASK_UNINTERRUPTIBLE)
                	nr_uninterrupt++;
        	} while_each_thread(g, p);
		
	}
	
	printk("load diagnose %s", (active == 0) ? "not active" : "active");
	
	return 0;
}
