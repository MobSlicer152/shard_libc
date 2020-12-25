#include <windows.h>
#include "env.h"

char **__get_envp(int __argc, char **__argv)
{
	return GetEnvironmentStrings();
}
