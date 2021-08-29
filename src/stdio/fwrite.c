#include "stdio.h"
#include "errno.h"
#include "unistd.h"

#ifdef __cplusplus
extern "C" {
#endif

size_t fwrite(const void *restrict __buf, size_t __size, size_t __count,
	      FILE *restrict __fp)
{
	size_t i;

	/* Queue each element */
	for (i = 0; i < __count; i += __size) {
		
	}
}

#ifdef __cplusplus
}
#endif
