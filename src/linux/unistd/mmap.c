#include "sys/syscall.h"
#include "unistd.h"

#ifdef __cplusplus
extern "C" {
#endif

void *mmap(void *__addr, size_t __len, int __prot, int __flags, int __fd,
	    off_t __offset)
{
	return (void *)syscall(__NR_mmap, (long)__addr, __len, __prot, __flags, __fd,
		       __offset);
}

#ifdef __cplusplus
}
#endif
