#include "unistd.h"

/* The assembly implementation of this function */
extern long __syscall(long rdi, long rsi, long rdx, long rcx, long r8, long r9);

/**
 * Thank you GNU and Linus Torvalds for making this function so easy to make.
 */
long syscall(unsigned long __number, long __rdi, long __rsi, long __rdx, long __rcx, long __r8, long __r9)
{
	/* Move __number into r15 as __syscall expects */
	__asm__ (
		"mov %0, %%r15"
		:
		: "r"(__number)
		: "%r15"
	);

	/* Call __syscall */
	return __syscall(__rdi, __rsi, __rdx, __rcx, __r8, __r9);
}
