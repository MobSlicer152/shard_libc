#include "wchar.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _MSC_VER
#pragma function(wcscmp)
#endif

int wcscmp(const wchar_t *__s1, const wchar_t *__s2)
{
	for (; *__s1 == *__s2; __s1++, __s2++) {
		if (*__s2 == L'\0')
			return *__s1 - *__s2;
	}

	return (*__s1 < *__s2) ? -1 : 1;
}

#ifdef __cplusplus
}
#endif
