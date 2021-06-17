#include "win32/windows_stuff.h"
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

void *__libc_windows_heap;
PEB *__libc_windows_peb;

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

	/* First, load the PEB */
	__libc_windows_peb = __get_peb();

	/* Load all the functions we need */
	__load_w32_funcs();

	/* Retrieve a handle to the heap */
	__libc_windows_heap = __libc_windows_peb->main_heap;

	/* Get the commandline */
	cmdline = __libc_windows_peb->params->cmdline.buf;

	/* Now turn it into an array of strings */
	argv_w = CommandLineToArgvW(cmdline, &argc);

	/* Allocate space for each argument and copy the translated string in */
	i = argc * sizeof(char *);
	argv = malloc(i);
	for (i = 0; i < argc; i++) {
		argv[i] = malloc((wcslen(argv_w[i]) + 1) * sizeof(char));
		if (!argv[i]) {
			LocalFree(argv_w);
			abort();
		}

		/* Translate to ASCII */
		memset(&astr, 0, sizeof(UTF8_STRING));
		RtlInitUnicodeString(&ustr, argv_w[i]);
		RtlUnicodeStringToUTF8String(&astr, &ustr, true);
 		strncpy(argv[i], astr.buf, wcslen(argv_w[i]));
		/* RtlFreeUTF8String(&astr); */
	}

	/* Free the memory Windows gave us */
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

#ifndef _MSC_VER
void __main(void)
{
	mainCRTStartup();
}
#endif

#ifdef __cplusplus
}
#endif
