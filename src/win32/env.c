#include "win32/env.h"

#ifdef __cplusplus
extern "C" {
#endif

char **__get_envp(int __argc, char **__argv)
{
	/* 
	 * Unlike Linux (which is more big brain), the end of __argv is not
	 *  necessarily right before the start of the environment block.
	 */
	(void)__argc;
	(void)__argv;
	return __libc_windows_peb->params->environ;
}

#ifdef __cplusplus
}
#endif
