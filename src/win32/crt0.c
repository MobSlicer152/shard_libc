#include "dumbass_windows_stuff.h"
#include "internal/startup.h"

/* We need these to transform the Windows commandline into ASCII argv */
#include "stdlib.h"
#include "string.h"
#include "wchar.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Windows functions signatures */
extern void *GetProcessHeap(void);
extern wchar_t *GetCommandLineW(void);
extern wchar_t **CommandLineToArgvW(wchar_t *cmdline, int *argc);
extern void *LocalFree(void *chunk);

/* Windows' application loader calls this */
#ifdef _WINMAIN_
#define startup WinMainCRTStartup
#else /* _WINMAIN_ */
#define startup mainCRTStartup
#endif /* _WINMAIN_ */

void *__libc_windows_heap;

void startup(void)
{
	int argc;
	char **argv;
	wchar_t *cmdline;
	wchar_t **argv_w;
	int i;

	/* Retrieve a handle to the heap */
	__libc_windows_heap = GetProcessHeap();

	/* Get the commandline */
	cmdline = GetCommandLineW();

	/* Now turn it into an array of strings */
	argv_w = CommandLineToArgvW(cmdline, &argc);

	/* Allocate space for each argument */
	argv = malloc(argc * sizeof(char *));
	for (i = 0; i < argc; i++) {
		argv[i] = malloc(wcslen(argv_w[i]) * sizeof(wchar_t));
		if (!argv[i]) {
			LocalFree(cmdline);
			LocalFree(argv_w);
			abort();
		}
	}

	/* Free the memory Windows gave us */
	LocalFree(cmdline);
	LocalFree(argv_w);

	/* Initialize stuff */
	__init_libc(argc, argv);

	/* Call main (this function exits and cleans up for us) */
	__libc_call_main(argc, argv);
}

#ifdef __cplusplus
}
#endif
