#include "string.h"

#ifdef __cplusplus
extern "C" {
#endif

char *strncpy(char *__dst, const char *__src, size_t __n)
{
	/* Tall brain mode */
	memccpy(__dst, __src, '\0', __n);
	return __dst;
}

#ifdef __cplusplus
}
#endif
