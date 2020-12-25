#include <Windows.h>
#include "stdlib.h"

void exit(int __status)
{
	ExitProcess(__status);

	/* MinGW */
#ifndef _MSC_VER
	__builtin_unreachable();
#endif /* !_MSC_VER */
}
