#include <heapapi.h>
#include "win32/dumbass_windows_stuff.h"
#include "stdlib.h"

void *malloc(size_t __size)
{
	size_t real_size;

	/* This is to ensure we allocate at least one byte */
	real_size = __size ? __size : 1;

	return HeapAlloc(__libc_windows_heap, 0, real_size);
}
