#include "internal/startup.h"
#include "stdio.h"

#ifdef __cplusplus
extern "C" {
#endif

void __shutdown_libc(int __argc, char **__argv, char **__envp)
{
	int i;

	/* Free stuff */
	for (i = 0; i < __argc; i++)
		free(__argv[i]);
	LocalFree(__envp);
}

#ifdef __cplusplus
}
#endif
