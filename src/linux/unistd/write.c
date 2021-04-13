#include "sys/syscall.h"
#include "unistd.h"

long write(int __fd, const void *__buf, size_t __n)
{
	return syscall(__NR_write, __fd, __buf, __n, 0, 0, 0);
}
