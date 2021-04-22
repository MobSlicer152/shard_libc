#include "internal/startup.h"
#include "stdio.h"

#ifdef __cplusplus
extern "C" {
#endif

void __shutdown_libc(int __argc, char **__argv, char **__envp)
{
	char *arg = 0;

	/* Free stuff */
	for (arg = __argv[0]; arg; arg += sizeof(char *))
		free(arg);
	LocalFree(__envp);
}

#ifdef __cplusplus
}
#endif
