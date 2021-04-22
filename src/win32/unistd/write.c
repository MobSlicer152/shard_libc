#include "stddef.h"
#include "unistd.h"

#include <wdm.h>

extern unsigned char WriteFile(void *file, const void *buf, unsigned int n,
			       unsigned int *written, void *unused);

long write(void *__fh, const void *__buf, size_t __n)
{
	IO_STATUS_BLOCK iostat = { 0 };
	int ret;

	/* We have to check if the handle is a kernel handle or not */
	syscall_r(ret, 0x8, __fh, NULL, NULL, NULL, &iostat, __buf, __n);
	if (ret != 0) /* Try again in user mode */
		WriteFile(__fh, __buf, __n, &iostat.Information, NULL);

	return iostat.Information;
}
