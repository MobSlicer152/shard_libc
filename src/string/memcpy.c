#include "string.h"
#include "stdint.h"

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
	uint64_t *cur;

	/* Copy until a quad aligned address */
	for (i = 0; i < __n / sizeof(uint64_t); i++)
		((unsigned char *)__dst)[i] = ((unsigned char *)__src);

	/* Copy quads */
	cur = ((unsigned char *)__dst + i);
	while (cur < ((unsigned char *)__dst + __n)) {
		*cur = ((unsigned char *)cur - (unsigned char *)__dst +
			(unsigned char *)__src);
		cur++;
	}

	return __dst;
}

#ifdef __cplusplus
}
#endif
