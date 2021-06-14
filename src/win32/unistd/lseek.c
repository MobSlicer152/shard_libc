#define _STDIO
#include "stdio.h"
#include "unistd.h"
#include "errno.h"
#include "win32/windows_stuff.h"

off_t lseek(int __fd, off_t __offset, int __whence)
{
	/* These aren't real files */
	if (__fd == (**__stderr())->fd || __fd == (**__stdin())->fd || __fd == (**__stdout())->fd) {
		errno = EBADF;
		return -1;
	}

	/* Seek the file */
	return SetFilePointerEx(__fd, _TMP_LARGE_INT(__offset), NULL, __whence);
}
