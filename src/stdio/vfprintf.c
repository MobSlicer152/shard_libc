#include "stdio.h"
#include "stdlib.h"
#include "stdarg.h"
#include "unistd.h"

#include "stb_sprintf.h"

#ifdef __cplusplus
extern "C" {
#endif

int vfprintf(FILE *__fp, const char *restrict __str, va_list __alist)
{
	va_list args;
	char *buf;
	int len;

	/* Clone the arglist */
	va_copy(args, __alist);

	/* Figure out how long the string is */
	len = 0;
	len = vsnprintf(NULL, 0, __str, args);
	
	/* Allocate a buffer */
	buf = calloc(len + 1, sizeof(char));
	if (!buf)
		return -1; /* calloc handles errno */

	/* Format the text into buf */
	vsnprintf(buf, len + 1, __str, args);

	/* Return whatever fwrite returns */
	return fwrite(buf, len + 1, 1, __fp);
}

#ifdef __cplusplus
}
#endif
