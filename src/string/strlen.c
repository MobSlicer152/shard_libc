#include "string.h"

#ifdef __cplusplus
extern "C" {
#endif

size_t strlen(const char *__str)
{
	size_t i;

	/* Increment i until __str[i] is NULL */
	for (i = 0; __str[i]; i++);

	return i;
}

#ifdef __cplusplus
}
#endif
