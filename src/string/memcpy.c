#include "string.h"

#ifdef __cplusplus
extern "C" {
#endif

/* 
 * Microsoft, I know your implementation is better
 *  for now, but I didn't ask you to use it.
 */
#ifdef _MSC_VER
#pragma function(memcpy)
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
