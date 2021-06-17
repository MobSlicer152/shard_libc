#include "errno.h"
#include "stdbool.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"
#include "wchar.h"
#include "win32/windows_stuff.h"

#ifdef __cplusplus
extern "C" {
#endif

/* DLL base addresses and handles */
static void *ntdll_base;
static void *kernel32_handle;
static void *shell32_base;
static void *shell32_handle;

/* Function names */
static ANSI_STRING commandlinetoargvw_str;
static ANSI_STRING exitprocess_str;
static ANSI_STRING getcommandlinew_str;
static ANSI_STRING getcurrentprocess_str;
static ANSI_STRING getcurrentthread_str;
static ANSI_STRING getenvironmentstrings_str;
static ANSI_STRING getlasterror_str;
static ANSI_STRING getprocessheap_str;
static ANSI_STRING getprocesstimes_str;
static ANSI_STRING getstdhandle_str;
static ANSI_STRING getsysteminfo_str;
static ANSI_STRING getthreadtimes_str;
static ANSI_STRING heapalloc_str;
static ANSI_STRING heapfree_str;
static ANSI_STRING localfree_str;
static ANSI_STRING setfilepointerex_str;
static ANSI_STRING virtualalloc_str;
static ANSI_STRING virtualfree_str;
static ANSI_STRING virtualquery_str;
static ANSI_STRING writefile_str;

/* Function pointers */
static void *commandlinetoargvw;
static void *exitprocess;
static void *getcommandlinew;
static void *getcurrentprocess;
static void *getcurrentthread;
static void *getlasterror;
static void *getprocessheap;
static void *getprocesstimes;
static void *getsysteminfo;
static void *getthreadtimes;
static void *heapalloc;
static void *heapfree;
static void *ldrgetdllhandle;
static void *ldrgetprocedureaddress;
static void *ldrloaddll;
static void *localfree;
static void *rtlfreeutf8string;
static void *rtlinitansistring;
static void *rtlinitunicodestring;
static void *rtlunicodestringtoutf8string;
static void *setfilepointerex;
static void *virtualalloc;
static void *virtualfree;
static void *virtualquery;
static void *writefile;

/* This function gets the addresses of NTDLL and the Ldr and Rtl functions that we use */
void __load_ntdll_funcs(void)
{
	PEB_LDR_DATA *ldr;
	LIST_ENTRY *head;
	LIST_ENTRY *current;
	LDR_MODULE *dll;
	LDR_MODULE *ntdll = 0;
	IMAGE_DOS_HEADER *dos_hdr;
	IMAGE_NT_HEADERS64 *nt_hdrs;
	IMAGE_EXPORT_DIRECTORY *exports;
	unsigned int *names;
	unsigned int *funcs;
	unsigned int i;

	/* Alias the PEB's loader data */
	ldr = __libc_windows_peb->ldr;

	/* Set the head of the list */
	head = &ldr->mem_order_mod_list;

	/* Enumerate the loaded modules until we bump into NTDLL */
	for (current = head->f; current != head; current = current->f) {
		dll = CONTAINING_RECORD(current, LDR_MODULE,
					mem_order_mod_list);
		if (wcsicmp(dll->full_name.buf,
			    L"C:\\Windows\\System32\\ntdll.dll") == 0) {
			ntdll = dll;
			break;
		}
	}

	/* Check if we got the DLL */
	if (!ntdll)
		abort();

	/* Store NTDLL's base address */
	ntdll_base = ntdll->base_addr;

	/* Parse the DLL header so we can find the functions we need */
	dos_hdr = ntdll_base;
	if (dos_hdr->magic != IMAGE_DOS_SIGNATURE)
		abort();
	nt_hdrs = ((unsigned char *)ntdll_base + (dos_hdr->nt_hdr_addr));
	if (nt_hdrs->sig != IMAGE_NT_SIGNATURE)
		abort();
	if (nt_hdrs->ohdr.magic != IMAGE_NT_OPTIONAL_HDR64_MAGIC)
		abort();
	if (!nt_hdrs->ohdr.num_rvas_and_sizes)
		abort();

	/* Find the export table */
	exports = ((unsigned char *)ntdll_base +
		   nt_hdrs->ohdr.data_dir->virt_addr);

	/* Make a pointer to our functions */
	funcs = ((unsigned char *)ntdll_base + exports->funcs_addr);

	/* Find LdrGetProcedureAddress by its ordinal, which is 137 */
	ldrgetprocedureaddress =
		((unsigned char *)ntdll_base + (funcs[137 - exports->base]));

	/* Now that we have LdrGetProcedureAddress, we don't need the function table anymore */
	LdrGetProcedureAddress(ntdll_base, &_TMP_ANSI_STR("LdrGetDllHandle"), 0,
			       &ldrgetdllhandle);
	LdrGetProcedureAddress(ntdll_base, &_TMP_ANSI_STR("LdrLoadDll"), 0,
			       &ldrloaddll);
	LdrGetProcedureAddress(ntdll_base, &_TMP_ANSI_STR("RtlFreeUTF8String"),
			       0, &rtlfreeutf8string);
	LdrGetProcedureAddress(ntdll_base, &_TMP_ANSI_STR("RtlInitAnsiString"),
			       0, &rtlinitansistring);
	LdrGetProcedureAddress(ntdll_base,
			       &_TMP_ANSI_STR("RtlInitUnicodeString"), 0,
			       &rtlinitunicodestring);
	LdrGetProcedureAddress(ntdll_base, &_TMP_ANSI_STR("RtlUnicodeStringToUTF8String"),
			       0, &rtlunicodestringtoutf8string);
}

/* Loads necessary DLLs and gets function pointers for wrappers */
void __load_w32_funcs(void)
{
	UNICODE_STRING kernel32_unicode_str;
	UNICODE_STRING shell32_unicode_str;
	long err;

	/* Load the NTDLL functions */
	__load_ntdll_funcs();

	/* Fill in the strings we need */
	RtlInitUnicodeString(&kernel32_unicode_str, L"kernel32.dll");
	RtlInitUnicodeString(&shell32_unicode_str, L"shell32.dll");
	RtlInitAnsiString(&commandlinetoargvw_str, "CommandLineToArgvW");
	RtlInitAnsiString(&exitprocess_str, "ExitProcess");
	RtlInitAnsiString(&getcommandlinew_str, "GetCommandLineW");
	RtlInitAnsiString(&getcurrentprocess_str, "GetCurrentProcess");
	RtlInitAnsiString(&getcurrentthread_str, "GetCurrentThread");
	RtlInitAnsiString(&getlasterror_str, "GetLastError");
	RtlInitAnsiString(&getprocessheap_str, "GetProcessHeap");
	RtlInitAnsiString(&getprocesstimes_str, "GetProcessTimes");
	RtlInitAnsiString(&getsysteminfo_str, "GetSystemInfo");
	RtlInitAnsiString(&getthreadtimes_str, "GetThreadTimes");
	RtlInitAnsiString(&heapalloc_str, "HeapAlloc");
	RtlInitAnsiString(&heapfree_str, "HeapFree");
	RtlInitAnsiString(&localfree_str, "LocalFree");
	RtlInitAnsiString(&setfilepointerex_str, "SetFilePointerEx");
	RtlInitAnsiString(&virtualalloc_str, "VirtualAlloc");
	RtlInitAnsiString(&virtualfree_str, "VirtualFree");
	RtlInitAnsiString(&virtualquery_str, "VirtualQuery");
	RtlInitAnsiString(&writefile_str, "WriteFile");

	/* Call LdrLoadDll to load the DLLs we need */
	err = LdrLoadDll(NULL, NULL, &shell32_unicode_str, &shell32_base);
	if (err != 0)
		abort();

	/* Get handles to the DLLs */
	err = LdrGetDllHandle(NULL, NULL, &kernel32_unicode_str,
			      &kernel32_handle);
	if (err != 0)
		abort();

	err = LdrGetDllHandle(NULL, NULL, &shell32_unicode_str,
			      &shell32_handle);
	if (err != 0)
		abort();

	/* Get the addresses of the functions we want */
	err = LdrGetProcedureAddress(shell32_handle, &commandlinetoargvw_str, 0,
				     &commandlinetoargvw);
	if (err != 0)
		abort();

	err = LdrGetProcedureAddress(kernel32_handle, &exitprocess_str, 0,
				     &exitprocess);
	if (err != 0)
		abort();

	err = LdrGetProcedureAddress(kernel32_handle, &getcommandlinew_str, 0,
				     &getcommandlinew);
	if (err != 0)
		abort();

	err = LdrGetProcedureAddress(kernel32_handle, &getcurrentprocess_str, 0,
				     &getcurrentprocess);
	if (err != 0)
		abort();

	err = LdrGetProcedureAddress(kernel32_handle, &getcurrentthread_str, 0,
				     &getcurrentthread);
	if (err != 0)
		abort();

	err = LdrGetProcedureAddress(kernel32_handle, &getlasterror_str, 0,
				     &getlasterror);
	if (err != 0)
		abort();

	err = LdrGetProcedureAddress(kernel32_handle, &getprocessheap_str, 0,
				     &getprocessheap);
	if (err != 0)
		abort();

	err = LdrGetProcedureAddress(kernel32_handle, &getprocesstimes_str, 0,
				     &getprocesstimes);
	if (err != 0)
		abort();

	err = LdrGetProcedureAddress(kernel32_handle, &getsysteminfo_str, 0,
				     &getsysteminfo);
	if (err != 0)
		abort();

	err = LdrGetProcedureAddress(kernel32_handle, &getthreadtimes_str, 0,
				     &getthreadtimes);
	if (err != 0)
		abort();

	err = LdrGetProcedureAddress(kernel32_handle, &heapalloc_str, 0,
				     &heapalloc);
	if (err != 0)
		abort();

	err = LdrGetProcedureAddress(kernel32_handle, &heapfree_str, 0,
				     &heapfree);
	if (err != 0)
		abort();

	err = LdrGetProcedureAddress(kernel32_handle, &localfree_str, 0,
				     &localfree);
	if (err != 0)
		abort();

	err = LdrGetProcedureAddress(kernel32_handle, &setfilepointerex_str, 0,
				     &setfilepointerex);
	if (err != 0)
		abort();

	err = LdrGetProcedureAddress(kernel32_handle, &virtualalloc_str, 0,
				     &virtualalloc);
	if (err != 0)
		abort();

	err = LdrGetProcedureAddress(kernel32_handle, &virtualfree_str, 0,
				     &virtualfree);
	if (err != 0)
		abort();

	err = LdrGetProcedureAddress(kernel32_handle, &virtualquery_str, 0,
				     &virtualquery);
	if (err != 0)
		abort();

	err = LdrGetProcedureAddress(kernel32_handle, &writefile_str, 0,
				     &writefile);
	if (err != 0)
		abort();
}

wchar_t **CommandLineToArgvW(wchar_t *cmdline, int *argc)
{
	return ((wchar_t * *(*)(wchar_t *, int *)) commandlinetoargvw)(cmdline,
								       argc);
}

void ExitProcess(int code)
{
	((void (*)(int))exitprocess)(
		code); /* This will segfault if it's not loaded */
}

wchar_t *GetCommandLineW(void)
{
	return ((wchar_t * (*)(void)) getcommandlinew)();
}

void *GetCurrentProcess(void)
{
	return ((void *(*)(void))getcurrentprocess)();
}

void *GetCurrentThread(void)
{
	return ((void *(*)(void))getcurrentthread)();
}

unsigned int GetLastError(void)
{
	return ((unsigned int (*)(void))getlasterror)();
}

void *GetProcessHeap(void)
{
	return ((void *(*)(void))getprocessheap)();
}

unsigned char GetProcessTimes(void *process, FILETIME *creation, FILETIME *exit,
			      FILETIME *kernel, FILETIME *user)
{
	return ((unsigned char (*)(void *, FILETIME *, FILETIME *, FILETIME *,
				   FILETIME *))getprocesstimes)(
		process, creation, exit, kernel, user);
}

void GetSystemInfo(void *info)
{
	((void (*)(void *))getsysteminfo)(info);
}

unsigned char GetThreadTimes(void *process, FILETIME *creation, FILETIME *exit,
			     FILETIME *kernel, FILETIME *user)
{
	return ((unsigned char (*)(void *, FILETIME *, FILETIME *, FILETIME *,
				   FILETIME *))getthreadtimes)(
		process, creation, exit, kernel, user);
}

void *HeapAlloc(void *heap, unsigned int flags, size_t size)
{
	return ((void *(*)(void *, unsigned int, size_t))heapalloc)(heap, flags,
								    size);
}

unsigned char HeapFree(void *heap, unsigned int flags, void *chunk)
{
	return ((unsigned char (*)(void *, unsigned int, void *))heapfree)(
		heap, flags, chunk);
}

long LdrGetDllHandle(void *unused_1, void *unused_2, UNICODE_STRING *name,
		     void **handle)
{
	return ((long (*)(void *, void *, UNICODE_STRING *,
			  void **))ldrgetdllhandle)(unused_1, unused_2, name,
						    handle);
}

long LdrGetProcedureAddress(void *base_addr, ANSI_STRING *procedure,
			    unsigned long ordinal, void **function)
{
	return ((long (*)(void *, ANSI_STRING *, unsigned long,
			  void **))ldrgetprocedureaddress)(base_addr, procedure,
							   ordinal, function);
}

long LdrLoadDll(void *unused_1, void *unused_2, UNICODE_STRING *name,
		void **base_addr)
{
	return ((long (*)(void *, void *, UNICODE_STRING *,
			  void **))ldrloaddll)(unused_1, unused_2, name,
					       base_addr);
}

void *LocalFree(void *chunk)
{
	return ((void *(*)(void *))localfree)(chunk);
}

void RtlFreeUTF8String(UTF8_STRING *str)
{
	((void (*)(UTF8_STRING *))rtlfreeutf8string)(str);
}

long RtlInitAnsiString(ANSI_STRING *dst, const char *src)
{
	return ((long (*)(ANSI_STRING *, const char *))rtlinitansistring)(dst,
									  src);
}

long RtlInitUnicodeString(UNICODE_STRING *dst, const wchar_t *src)
{
	return ((long (*)(UNICODE_STRING *,
			  const wchar_t *))rtlinitunicodestring)(dst, src);
}

long RtlUnicodeStringToUTF8String(UTF8_STRING *dst, const UNICODE_STRING *src,
				  unsigned char alloc_dst)
{
	return ((long (*)(UTF8_STRING *, const UNICODE_STRING *, unsigned char))
			rtlunicodestringtoutf8string)(dst, src, alloc_dst);
}

long SetFilePointerEx(void *file, LARGE_INTEGER off, void *unused,
		      unsigned int whence)
{
	return ((long (*)(void *, LARGE_INTEGER, void *,
		 unsigned int))setfilepointerex)(file, off, unused, whence);
}

void *VirtualAlloc(void *addr, size_t size, unsigned int type,
		   unsigned int prot)
{
	return ((void *(*)(void *, size_t, unsigned int,
			   unsigned int))virtualalloc)(addr, size, type, prot);
}

unsigned char VirtualFree(void *addr, size_t size, unsigned int type)
{
	return ((unsigned char (*)(void *, size_t, unsigned int))virtualfree)(
		addr, size, type);
}

size_t VirtualQuery(const void *addr, void *buf, size_t len)
{
	return ((size_t(*)(const void *, void *, size_t))virtualquery)(
		addr, buf, len);
}

unsigned char WriteFile(void *file, const void *buf, unsigned int n,
			unsigned int *written, void *overlapped)
{
	return ((unsigned char (*)(void *, const void *, unsigned int,
				   unsigned int *, void *))writefile)(
		file, buf, n, written, overlapped);
}

#ifdef __cplusplus
}
#endif
