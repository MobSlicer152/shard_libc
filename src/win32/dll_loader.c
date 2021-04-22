#include "errno.h"
#include "stdbool.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"

#include <ntdef.h>

#ifdef __cplusplus
extern "C" {
#endif

/* DLL base addresses and handles */
void *kernel32_handle; /* This is always mapped but the actual kernel isn't? */
void *shell32_base;
void *shell32_handle;

/* Function names */
ANSI_STRING commandlinetoargvw_str;
ANSI_STRING exitprocess_str;
ANSI_STRING getcommandlinew_str;
ANSI_STRING getenvironmentstrings_str;
ANSI_STRING getlasterror_str;
ANSI_STRING getsysteminfo_str;
ANSI_STRING getprocessheap_str;
ANSI_STRING getstdhandle_str;
ANSI_STRING heapalloc_str;
ANSI_STRING heapfree_str;
ANSI_STRING localfree_str;
ANSI_STRING virtualalloc_str;
ANSI_STRING virtualfree_str;
ANSI_STRING virtualquery_str;
ANSI_STRING writefile_str;

/* Function pointers */
void *commandlinetoargvw;
void *exitprocess;
void *getcommandlinew;
void *getenvironmentstrings;
void *getlasterror;
void *getsysteminfo;
void *getprocessheap;
void *getstdhandle;
void *heapalloc;
void *heapfree;
void *localfree;
void *virtualalloc;
void *virtualfree;
void *virtualquery;
void *writefile;

/* 
 * We only link against NTDLL for the loader functions. These function signatures are
 *  based on ReactOS's source code
 */
extern NTSTATUS LdrLoadDll(void *unused_1, void *unused_2, UNICODE_STRING *name,
			   void **base_addr);
extern NTSTATUS LdrGetDllHandle(void *unused_1, void *unused_2,
				UNICODE_STRING *name, void **handle);
extern NTSTATUS LdrGetProcedureAddress(void *base_addr, ANSI_STRING *procedure,
				       size_t ordinal, void **function);

/*
 * The Rtl* functions are implemented in the kernel and are mode-independant
 *  for our purposes
 */
extern long RtlInitAnsiString(ANSI_STRING *dst, const char *src);
extern long RtlInitUnicodeString(UNICODE_STRING *dst, const wchar_t *src);
extern 

/* Loads necessary DLLs and gets function pointers for wrappers */
void *__load_w32_funcs(void)
{
	UNICODE_STRING kernel32_unicode_str;
	UNICODE_STRING shell32_unicode_str;
	NTSTATUS err;

	/* Fill in the strings we need */
	RtlInitUnicodeString(&kernel32_unicode_str, L"kernel32.dll");
	RtlInitUnicodeString(&shell32_unicode_str, L"shell32.dll");
	RtlInitAnsiString(&commandlinetoargvw_str, "CommandLineToArgvW");
	RtlInitAnsiString(&exitprocess_str, "ExitProcess");
	RtlInitAnsiString(&getcommandlinew_str, "GetCommandLineW");
	RtlInitAnsiString(&getenvironmentstrings_str, "GetEnvironmentStrings");
	RtlInitAnsiString(&getlasterror_str, "GetLastError");
	RtlInitAnsiString(&getsysteminfo_str, "GetSystemInfo");
	RtlInitAnsiString(&getprocessheap_str, "GetProcessHeap");
	RtlInitAnsiString(&getstdhandle_str, "GetStdHandle");
	RtlInitAnsiString(&heapalloc_str, "HeapAlloc");
	RtlInitAnsiString(&heapfree_str, "HeapFree");
	RtlInitAnsiString(&localfree_str, "LocalFree");
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

	err = LdrGetProcedureAddress(kernel32_handle,
				     &getenvironmentstrings_str, 0,
				     &getenvironmentstrings);
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

	err = LdrGetProcedureAddress(kernel32_handle, &getsysteminfo_str, 0,
				     &getsysteminfo);
	if (err != 0)
		abort();

	err = LdrGetProcedureAddress(kernel32_handle, &getstdhandle_str, 0,
				     &getstdhandle);
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

char *GetEnvironmentStrings(void)
{
	return ((char *(*)(void))getenvironmentstrings)();
}

unsigned int GetLastError(void)
{
	return ((unsigned int (*)(void))getlasterror)();
}

void GetSystemInfo(void *info)
{
	((void (*)(void *))getsysteminfo)(info);
}

void *GetProcessHeap(void)
{
	return ((void *(*)(void))getprocessheap)();
}

void *GetStdHandle(unsigned int fd)
{
	return ((void *(*)(unsigned int))getstdhandle)(fd);
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

void *LocalFree(void *chunk)
{
	return ((void *(*)(void *))localfree)(chunk);
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
	return ((unsigned char (*)(void *, const void *, unsigned int, unsigned int *, void *))writefile)(file, buf, n, written, overlapped);
}

#ifdef __cplusplus
}
#endif
