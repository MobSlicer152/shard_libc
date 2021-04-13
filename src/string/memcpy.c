#include "string.h"

#ifdef __cplusplus
extern "C" {
#endif

void *memcpy(void *restrict __dst, const void *restrict __src, size_t __n)
{
	size_t i;

	/* Copy while i is less than __n */
	for (i = 0; i < __n; i++)
		((unsigned char *)__dst)[i] = ((unsigned char *)__src)[i];

	return __dst;
}

#ifdef __cplusplus
}
#endif
