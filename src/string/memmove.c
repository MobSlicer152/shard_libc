#include "string.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _MSC_VER
#pragma function(memmove)
#endif

/* malloc and free are needed here */
extern void *malloc(size_t __size);
extern void free(void *__chunk);

void *memmove(void *__dst, const void *__src, size_t __n)
{
	unsigned char *buf;

	/* Allocate a buffer */
	buf = malloc(__n);
	if (!buf)
		return NULL;

	/* Copy the memory */
	memcpy(buf, __src, __n);
	memcpy(__dst, buf, __n);

	/* Free the buffer */
	free(buf);

	return __dst;
}

#ifdef __cplusplus
}
#endif
