#include <windows.h>
#include "stdlib.h"

void exit(int __status)
{
	ExitProcess(__status);

	__builtin_unreachable();
}
