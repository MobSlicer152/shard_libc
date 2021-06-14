#include "wchar.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _MSC_VER
#pragma function(wcsicmp)
#endif

int wcsicmp(const wchar_t *__s1, const wchar_t *__s2)
{
	wchar_t c1 = *__s1;
	wchar_t c2 = *__s2;

	while (*__s1 != L'\0' && *__s2 != L'\0') {
		/* Lowercase both chars if they're uppercase */
		if (c1 >= L'A' && c1 <= L'Z')
			c1 += ' ';
		if (c2 >= L'A' && c2 <= L'Z')
			c2 += ' ';

		/* Compare the characters */
		if (c1 != c2)
			break;

		/* Advance both pointers */
		c1 = *__s1++;
		c2 = *__s2++;
	}

	return c1 - c2;
}

#ifdef __cplusplus
}
#endif
