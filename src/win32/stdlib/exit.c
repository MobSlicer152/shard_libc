/* wchar_t might not be defined by the compiler, and the Win32 headers need it defined */
#include "wchar.h"

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
