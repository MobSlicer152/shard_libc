#include "string.h"

void *memccpy(void *restrict __dst, const void *restrict __src, int __c, size_t __n)
{
	size_t i;

	/* Copy until __c occurs or i reaches __n */
	for (i = 0; i < __n; i++) {
		if (((unsigned char *)__src)[i] == __c) {
			((unsigned char *)__dst)[i] = '\0'; /* Terminate the buffer */
			return &((unsigned char *)__src)[i + 1];
		}

		((unsigned char *)__dst)[i] = ((unsigned char *)__src)[i];
	}

	return NULL;
}
