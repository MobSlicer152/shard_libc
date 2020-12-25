#include "startup.h"

/**
 * @brief The address of where the
 * environment variable buffer starts, which is
 * determined by __get_envp.
 */
char **__env;

int __init_libc(int argc, char *argv[])
{
	/* Get the location of envp */
	__env = __get_envp(argc, argv);

	return 0;
}

int __libc_call_main(int __argc, char **__argv)
{
	/* Call main */
	return main(__argc, __argv, __env);
}
