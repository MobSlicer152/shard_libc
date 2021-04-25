#include "stdio.h"
#include "stdlib.h"

#include "windows_stuff.h"

#ifdef __cplusplus
extern "C" {
#endif

FILE *___stdin;
FILE *___stdout;
FILE *___stderr;

void __init_stdio(void)
{
	/* Allocate the file streams */
	___stdin = malloc(sizeof(FILE));
	___stdout = malloc(sizeof(FILE));
	___stderr = malloc(sizeof(FILE));

	/* Allocate the actual structures underneath */
	*___stdin = malloc(sizeof(struct file));
	*___stdout = malloc(sizeof(struct file));
	*___stderr = malloc(sizeof(struct file));

	/* The function that loads the PEB has been called by now */
	(*___stdin)->fd = __libc_windows_peb->params->in;
	(*___stdout)->fd = __libc_windows_peb->params->out;
	(*___stderr)->fd = __libc_windows_peb->params->err;
}

#ifdef __cplusplus
}
#endif
