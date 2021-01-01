#include <asm/unistd_64.h>
#include "unistd.h"
#include "stdlib.h"

extern void exit(int __status)
{
	__syscall(__NR_exit, __status);

	/* 
	 * If exit ever returns somehow, then your build of
	 *  the kernel is broken enough to entirely abandon.
	 */
	__builtin_unreachable();
}
