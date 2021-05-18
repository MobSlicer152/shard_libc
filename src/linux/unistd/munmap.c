#include "sys/syscall.h"
#include "unistd.h"

#ifdef __cplusplus
extern "C" {
#endif

int munmap(void *__addr, size_t __len)
{
	return syscall(__NR_munmap, (long)__addr, __len, 0, 0, 0, 0);
}

#ifdef __cplusplus
}
#endif
