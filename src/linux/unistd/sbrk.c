#include "sys/syscall.h"
#include "unistd.h"
#include "errno.h"

void *sbrk(intptr_t __increment)
{
	errno = EOPNOTSUPP; /* This one could take a while to implement */
	return (void *)-1;
}
