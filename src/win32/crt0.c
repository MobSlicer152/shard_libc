#include <heapapi.h>
#include <shellapi.h>
#include <windows.h>
#include "dumbass_windows_stuff.h"
#include "internal/startup.h"

/* wchar_t might not be defined by the compiler */
#define __need_wchar_t
#include "alltypes.h"

#ifdef _WINMAIN_
#define startup WinMainCRTStartup
#else /* _WINMAIN_ */
#define startup mainCRTStartup
#endif /* _WINMAIN_ */

HANDLE __libc_windows_heap;

int startup(void)
{
	int argc;
	char **argv;
	wchar_t *cmdline;
	wchar_t **argv_w;

	/* Retrieve a handle to the heap */
	__libc_windows_heap = GetProcessHeap();

	/* Get the commandline */
	cmdline = GetCommandLineW();

	/* Now turn it into an array of strings */
	argv_w = CommandLineToArgvW(cmdline, &argc);

	/* And finally turn it into ASCII */

}
