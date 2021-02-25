#include "startup.h"

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

	/* Call main */
	ret = main(__argc, __argv, environ);

	/* TODO: add a cleanup function when it's needed */

	/* Call destructors */
	_fini();

	/* Exit */
	exit(ret);
}
