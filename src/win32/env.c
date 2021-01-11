/* wchar_t might not be defined by the compiler, and the Win32 headers need it defined */
#include "wchar.h"

#include <windows.h>
#include "env.h"

char **__get_envp(int __argc, char **__argv)
{
	return GetEnvironmentStrings();
}
