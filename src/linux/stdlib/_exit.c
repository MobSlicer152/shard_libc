#include "sys/syscall.h"
#include "unistd.h"
#include "stdlib.h"

void _exit(int __status)
{
	while (1) {
#ifdef __NR_exit_group
		syscall(__NR_exit_group, __status, 0, 0, 0, 0, 0);
#endif /* __NR_exit_group */
		syscall(__NR_exit, __status, 0, 0, 0, 0, 0);

		__asm__("hlt");
	}
}
