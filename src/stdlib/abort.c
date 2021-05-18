#include "stdlib.h"

#define _INTERNAL_STDIO_DEFS
#include "stdio.h"
#include "unistd.h"

_Noreturn void abort(void)
{
	if (*__stdio_initialized())
		write((*stderr)->fd, "abort() got called, exiting\n", 29);

	/*
	 * TODO: once I implement signal stuff, I'll use that. For now though,
	 *  AFAIK, the standard allows this.
	 */
	exit(-1);
}
