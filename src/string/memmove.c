#include "string.h"

void *memmove(void *__dst, const void *__src, size_t __n)
{
	size_t i;
	unsigned char buf[__n];

	/* Copy the memory */
	__dst = memcpy(buf, __src, __n);

	return __dst;
}
