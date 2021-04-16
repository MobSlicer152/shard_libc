/* Windows needs wchar_t */
#include "stddef.h"

#include "unistd.h"

/* Function signatures */
extern int WriteFile(void *file, void *buf, unsigned int n,
		     unsigned int *written, void *unused);

long write(void *__fh, const void *__buf, size_t __n)
{
	long ret;

	/*
	 * This is almost as simple as on Linux except for
	 * the number of written bytes being put in a parameter
	 */
	WriteFile(__fh, __buf, __n, &ret, NULL);

	return ret;
}
