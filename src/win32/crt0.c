#include "windows_stuff.h"
#include "internal/startup.h"

/* We need these to transform the Windows commandline into ASCII argv */
#include "stdbool.h"
#include "stdlib.h"
#include "string.h"
#include "wchar.h"
#include "unistd.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Two typedefs from ntdef.h because it doesn't work */
typedef struct _UTF8_STRING {
	unsigned short len;
	unsigned short max_len;
	char *buf;
} UTF8_STRING;

typedef struct _UNICODE_STRING {
	unsigned short len;
	unsigned short max_len;
	wchar_t *buf;
} UNICODE_STRING;

/* Windows function signatures */
extern wchar_t **CommandLineToArgvW(wchar_t *cmdline, int *argc);
extern wchar_t *GetCommandLineW(void);
extern void *GetProcessHeap(void);
extern void *LocalFree(void *chunk);
extern long RtlUnicodeStringToUTF8String(UTF8_STRING *dst,
					 const UNICODE_STRING *src,
					 unsigned char alloc_dst);
extern long RtlInitUnicodeString(UNICODE_STRING *dst, const wchar_t *src);
extern void RtlFreeUTF8String(UTF8_STRING *str);

void *__libc_windows_heap;

void mainCRTStartup(void)
{
	int argc;
	char **argv;
	wchar_t *cmdline;
	wchar_t **argv_w;
	UTF8_STRING astr;
	UNICODE_STRING ustr;
	int ret;
	int i;

	/* Before anything else, load all the functions we need */
	__load_w32_funcs();

	/* Retrieve a handle to the heap */
	__libc_windows_heap = GetProcessHeap();

	/* Get the commandline */
	cmdline = GetCommandLineW();

	/* Now turn it into an array of strings */
	argv_w = CommandLineToArgvW(cmdline, &argc);

	/* Allocate space for each argument and copy the translated string in */
	argv = malloc(argc * sizeof(char *));
	for (i = 0; i < argc; i++) {
		argv[i] = malloc(wcslen(argv_w[i]) * sizeof(wchar_t));
		if (!argv[i]) {
			LocalFree(cmdline);
			LocalFree(argv_w);
			abort();
		}

		/* Translate to ASCII */
		memset(&astr, 0, sizeof(UTF8_STRING));
		RtlInitUnicodeString(&ustr, argv_w[i]);
		RtlUnicodeStringToUTF8String(&astr, &ustr, true);
		strncpy(argv[i], astr.buf, wcslen(argv_w[i]));
		RtlFreeUTF8String(&astr);
	}

	/* Free the memory Windows gave us */
	LocalFree(cmdline);
	LocalFree(argv_w);

	/* Initialize stuff */
	__init_libc(argc, argv);

	/* Call main */
	ret = __libc_call_main(argc, argv);

	/* Shut down all the library stuff */
	__shutdown_libc(argc, argv, environ);

	/* Exit */
	exit(ret);
}

#ifdef __cplusplus
}
#endif
