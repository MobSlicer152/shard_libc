#include "string.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _MSC_VER
#pragma function(memset)
#endif

void *memset(void *restrict __dst, int __c, size_t __n)
{
	size_t i;

	/* Overwrite while i is less than __n */
	for (i = 0; i < __n; i++)
		((unsigned char *)__dst)[i] = ((unsigned char)(__c & 0xFF));

	return __dst;
}

#ifdef __cplusplus
}
#endif
