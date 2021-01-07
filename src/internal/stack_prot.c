#include <stdint.h>
#include <stdlib.h>

/**
 * This file stops GCC and maybe Clang from
 * complaining about this stuff being undefined
 */

#if UINT32_MAX == UINTPTR_MAX
#define STACK_GUARD 0xe09d013f
#else
#define STACK_GUARD 0xef0293fd02fe8a89
#endif

uintptr_t __stack_chk_guard = STACK_GUARD;

__attribute__((noreturn))
void __stack_chk_fail(void)
{
	exit(-1); /* Totally die. Should be abort() but I haven't done that yet */
}
