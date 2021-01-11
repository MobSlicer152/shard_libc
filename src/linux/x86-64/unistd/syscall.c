#include "internal/registers.h"
#include "stdarg.h"
#include "unistd.h"

/**
 * Thank you GNU and Linus Torvalds for making this function so easy to make.
 * This implementation is somewhere between musl libc's and glibc's.
 */
long syscall(unsigned long __number, ...)
{
	/* Some registers don't have shorthands */
	__X86_64_REG_DEFS;

	va_list args;
	long ret;

	/* Get our arguments */
	va_start(args, __number);

	/* Put the arguments in their registers */
	rax = __number;
	rdi = va_arg(args, long);
	rsi = va_arg(args, long);
	rdx = va_arg(args, long);
	r10 = va_arg(args, long);
	r8 = va_arg(args, long);
	r9 = va_arg(args, long);

	__asm__ __volatile__(
		"syscall"
		: "=a"(ret)
		: "r"(rax), "r"(rdi), "r"(rsi), "r"(rdx),
		  "r"(r10), "r"(r8), "r"(r9)
		: "rcx", "r11", "memory"
	);

	return ret;
}
