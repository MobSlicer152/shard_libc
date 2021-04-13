/* wchar_t might not be defined by the compiler, and the Win32 headers need it defined */
#include "stddef.h"

#include <windows.h>
#include "env.h"

#ifdef __cplusplus
extern "C" {
#endif

char **__get_envp(int __argc, char **__argv)
{
	return GetEnvironmentStrings();
}

#ifdef __cplusplus
}
#endif
