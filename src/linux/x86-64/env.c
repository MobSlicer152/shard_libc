#include "env.h"

char **__get_envp(int __argc, char **__argv)
{
	/* IIRC this should be where envp starts */
	return &__argv[__argc + 1];
}
