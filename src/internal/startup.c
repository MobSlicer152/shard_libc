#include "startup.h"

#ifdef __cplusplus
extern "C" {
#endif

char **environ;
char **__env;

int __init_libc(int __argc, char **__argv)
{
	/* Get the location of environ */
	__env = __get_envp(__argc, __argv);
	environ = __env;

	return 0;
}

void __libc_call_main(int __argc, char **__argv)
{
	int ret;
	int i;

	/* Call main */
	ret = main(__argc, __argv, environ);

#ifdef _WIN32
	/* Free __argv on Windows (Linux deals with it for us) */
	for (i = 0; i < __argc; i++)
		free(__argv[i]);
	free(__argv);
#endif

	/* Exit */
	exit(ret);
}

#ifdef __cplusplus
}
#endif
