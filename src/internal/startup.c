#include "internal/startup.h"

#ifdef __cplusplus
extern "C" {
#endif

char **environ;
char **__env;

int __init_libc(int __argc, char **__argv)
{
	/* Initialize I/O */
	__init_stdio();

	/* Get the location of environ */
	__env = __get_envp(__argc, __argv);
	environ = __env;

	return 0;
}

int __libc_call_main(int __argc, char **__argv)
{
	/* Call main */
	return main(__argc, __argv, environ);
}

#ifdef __cplusplus
}
#endif
