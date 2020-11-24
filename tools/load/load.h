#include <linux/fs.h>

#ifndef  _LOAD_H
#define _LOAD_H

#define LOAD_MAGIC    'l'
#define LOAD_ACTIVE    _IOW(LOAD_MAGIC, 0, unsigned int)

long load_ioctl(struct file *, unsigned int, unsigned long);

#endif
