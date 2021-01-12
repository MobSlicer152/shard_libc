#include "sys/syscall.h"
#include "unistd.h"
#include "stdlib.h"

extern void _exit(int __status)
{
	while (1) {
#ifdef __NR_exit_group
		syscall(__NR_exit_group, __status);
#endif /* __NR_exit_group */
		syscall(__NR_exit, __status);

		__asm__("hlt");
	}
}
