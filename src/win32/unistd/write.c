/* Windows needs wchar_t */
#include "stddef.h"

#include <Windows.h>
#include "unistd.h"

long write(int __fd, const void *__buf, size_t __n)
{
	long ret;

	/*
	 * This is almost as simple as on Linux except for
	 * the number of written bytes being put in a parameter
	 */
	WriteFile(_get_osfhandle(__fd), __buf, &ret, NULL);

	return ret;
}
