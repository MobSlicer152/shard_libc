#include "sys/syscall.h"
#include "stdarg.h"
#include "unistd.h"

#ifdef __cplusplus
extern "C" {
#endif

void *mremap(void *__old_addr, size_t __old_size, size_t __new_size,
	     int __flags, ...)
{
	va_list args;
	void *__new_addr;

	va_start(args, __flags);
	__new_addr = va_arg(args, void *);

	return (void *)syscall(__NR_mremap, (long)__old_addr, __old_size,
			       __new_size, __flags, (long)__new_addr, 0);
}

#ifdef __cplusplus
}
#endif
