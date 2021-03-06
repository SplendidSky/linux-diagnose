#include <linux/fs.h>
#include <linux/stacktrace.h>
#ifndef  _LOAD_H
#define _LOAD_H

#define LOAD_MAGIC    'l'
#define LOAD_ACTIVE    _IOW(LOAD_MAGIC, 0, unsigned int)

long load_ioctl(struct file *, unsigned int, unsigned long);

struct load_diag_buf {
	int active;
	int nr_uninterrupt;
	int nr_running;
	unsigned long *trace;
};

#endif
