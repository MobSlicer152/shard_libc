#include "env.h"

char **__get_envp(int __argc, char **__argv)
{
	/* envp starts here */
	return &__argv[__argc + 1];
}
