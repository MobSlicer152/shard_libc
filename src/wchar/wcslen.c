#include "wchar.h"

#ifdef __cplusplus
extern "C" {
#endif

size_t wcslen(const wchar_t*__str)
{
	size_t i;

	/* Increment i until __str[i] is NULL */
	for (i = 0; __str[i]; i++)
		;

	return i;
}

#ifdef __cplusplus
}
#endif
