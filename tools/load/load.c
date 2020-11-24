#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <errno.h>

#include "load.h"

int main() {
	int fd, ret;
	
	fd = open("/dev/diagnose", O_RDWR);
	if (fd == -1)
		goto fail;
	
	ret = ioctl(fd, LOAD_ACTIVE, 1);
	return ret;

fail:
	return -1;
}
