#include "stdlib.h"

#ifdef __cplusplus
extern "C" {
#endif

_Noreturn void exit(int __status)
{
	_exit(__status);
}

#ifdef __cplusplus
}
#endif
