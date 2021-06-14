#include "string.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _MSC_VER
#pragma function(strcmp)
#endif

int strcmp(const char *__s1, const char *__s2)
{
	while (*__s1 && (*__s1 == *__s2)) {
		__s1++;
		__s2++;
	}

	return (*(const unsigned char *)__s1) - (*(const unsigned char *)__s2);
}

#ifdef __cplusplus
}
#endif
