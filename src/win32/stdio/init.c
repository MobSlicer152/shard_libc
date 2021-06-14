#define _INTERNAL_STDIO_DEFS
#include "stdio.h"
#include "stdlib.h"

#include "win32/windows_stuff.h"

#ifdef __cplusplus
extern "C" {
#endif

/* This is an internal variable stating if I/O is initialied */
_Bool __is_stdio_initialized;

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
	*___stdin = malloc(sizeof(struct __file));
	*___stdout = malloc(sizeof(struct __file));
	*___stderr = malloc(sizeof(struct __file));

	/* The function that loads the PEB has been called by now */
	(*___stdin)->fd = __libc_windows_peb->params->in;
	(*___stdout)->fd = __libc_windows_peb->params->out;
	(*___stderr)->fd = __libc_windows_peb->params->err;

	/* State that initialization is done */
	__is_stdio_initialized = 1;
}

FILE **__stdin(void)
{
	return &___stdin;
}

FILE **__stdout(void)
{
	return &___stdout;
}

FILE **__stderr(void)
{
	return &___stderr;
}

_Bool *__stdio_initialized(void)
{
	return &__is_stdio_initialized;
}

#ifdef __cplusplus
}
#endif
