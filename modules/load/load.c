#include <linux/fs.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/ioctl.h>
#include <linux/uaccess.h>
#include <linux/sched.h>
#include <linux/stacktrace.h>
#include <linux/slab.h>
#include "load.h"

#define MAX_STACK_TRACE_DEPTH 64
#define MAX_ENTRIES 64

static int active = 0;
static int nr_uninterrupt = 0;

long load_ioctl(struct file *filp, unsigned int cmd, unsigned long args) {
	struct task_struct *g, *p;
	struct stack_trace trace;
    	unsigned long *entries;
	int i;
	
	if (_IOC_TYPE(cmd) != LOAD_MAGIC) {
		printk("Invalid load cmd");
		return -ENOTTY;
	}
	
	switch (cmd) {
	case LOAD_ACTIVE:
		active = args;
		break;
	default:
		printk("Invalid load cmd");
		return -ENOTTY;
	}
	
	if (active) {
		do_each_thread(g, p) {
			if (p->state & TASK_UNINTERRUPTIBLE || p->state == TASK_RUNNING) {
				entries = kmalloc(MAX_STACK_TRACE_DEPTH * sizeof(*entries), GFP_KERNEL);
       				if (!entries)
                			return -ENOMEM;

        			trace.nr_entries    = 0;
			        trace.max_entries    = MAX_STACK_TRACE_DEPTH;
			        trace.entries        = entries;
			        trace.skip        = 0;
				save_stack_trace_tsk(p, &trace);
				for (i = 0; i < trace.nr_entries; i++) {
					printk("[<%pK>] %pS\n", (void *)entries[i], (void *)entries[i]);
				}
				kfree(entries);
			}
        	} while_each_thread(g, p);
	}
	
	return 0;
}
EXPORT_SYMBOL_GPL(load_ioctl);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Weichen Chen <splendidsky.cwc@alibaba-inc.com");
MODULE_DESCRIPTION("Linux diagnose module");
