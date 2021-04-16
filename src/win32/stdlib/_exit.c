#include "stdlib.h"

/* Function signatures */
extern void ExitProcess(int status);

#ifdef __cplusplus
extern "C" {
#endif

_Noreturn void _exit(int __status)
{
	ExitProcess(__status);

	/* MinGW */
#ifndef _MSC_VER
	__builtin_unreachable();
#endif /* !_MSC_VER */
}

#ifdef __cplusplus
}
#endif
