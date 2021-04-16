#include "stdlib.h"

_Noreturn void abort(void)
{
	/*
	 * TODO: once I implement signal stuff, I'll use that. For now though,
	 *  AFAIK, the standard allows this.
	 */
	exit(-1);
}
