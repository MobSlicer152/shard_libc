#include "stdio.h"
#include "stdarg.h"

#ifdef __cplusplus
extern "C" {
#endif

int fprintf(FILE *__fp, const char *restrict __str, ...)
{
	va_list args = 0;
	int ret;

	/* Initialize the arglist and call vfprintf */
	va_start(args, __str);
	ret = vfprintf(__fp, __str, args);
	va_end(args);

	return ret;
}

#ifdef __cplusplus
}
#endif
