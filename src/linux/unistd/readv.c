#include "sys/syscall.h"
#include "unistd.h"

#ifdef __cplusplus
extern "C" {
#endif

ssize_t readv(int __fd, struct iovec *__iov, int __iovcnt)
{
	return syscall(__NR_readv, __fd, __iov, __iovcnt, 0, 0, 0, 0);
}

#ifdef __cplusplus
}
#endif
