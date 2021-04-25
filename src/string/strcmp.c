#include "string.h"

#ifdef __cplusplus
extern "C" {
#endif

int strcmp(const char *__s1, const char *__s2)
{
	for (; *__s1 == *__s2; __s1++, __s2++) {
		if (*__s2 == '\0')
			return *__s1 - *__s2;
	}

	return (*(const unsigned char *)__s1 < *(const unsigned char *)__s2) ? -1 : 1;
}

#ifdef __cplusplus
}
#endif
