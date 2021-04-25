#include "errno.h"
#include "stdbool.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"
#include "wchar.h"
#include "windows_stuff.h"

#ifdef __cplusplus
extern "C" {
#endif

/* DLL base addresses and handles */
void *ntdll_base;
void *kernel32_handle;
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
void *getlasterror;
void *getsysteminfo;
void *heapalloc;
void *heapfree;
void *ldrgetdllhandle;
void *ldrgetprocedureaddress;
void *ldrloaddll;
void *localfree;
void *virtualalloc;
void *virtualfree;
void *virtualquery;
void *writefile;

/* This function gets the addresses of NTDLL and the Ldr* functions that we use */
void __load_ntdll_funcs(void)
{
	PEB_LDR_DATA *ldr;
	LIST_ENTRY *head;
	LIST_ENTRY *current;
	LDR_MODULE *dll;
	LDR_MODULE *ntdll = 0;
	IMAGE_DOS_HEADER *dos_hdr;
	IMAGE_NT_HEADERS64 *nt_hdrs;
	unsigned int exports_va;
	IMAGE_SECTION_HEADER *sect_hdr;
	unsigned int sect_count;
	unsigned int export_sect;
	IMAGE_EXPORT_DIRECTORY *exports;
	unsigned char **func_names;
	int i;

	/* First, load the PEB */
	__libc_windows_peb = __get_peb();
	if (!__libc_windows_peb)
		abort();

	/* Alias the PEB's loader data */
	ldr = __libc_windows_peb->ldr;

	/* Set the head of the list */
	head = &ldr->mem_order_mod_list;

	/* Enumerate the loaded modules until we bump into NTDLL */
	for (current = head->f; current != head; current = current->f) {
		dll = CONTAINING_RECORD(current, LDR_MODULE,
					mem_order_mod_list);
		if (wcscmp(dll->full_name.buf,
			   L"C:\\WINDOWS\\SYSTEM32\\ntdll.dll") == 0) {
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
	exports_va = nt_hdrs->ohdr.data_dir[0].virt_addr;
	sect_count = nt_hdrs->fhdr.n_sects;
	sect_hdr = ((unsigned char *)ntdll_base + dos_hdr->nt_hdr_addr +
		    sizeof(*nt_hdrs));
	for (export_sect = 0;
	     export_sect < sect_count && sect_hdr->virt_addr <= exports_va;
	     sect_hdr++, export_sect++)
		;
	sect_hdr--;
	exports = ((unsigned char *)ntdll_base + sect_hdr->raw_ptr) +
		  (exports_va - sect_hdr->virt_addr);

	/* Find our functions */
	func_names = ((unsigned char *)ntdll_base + exports->names_addr);
	for (i = 0; i < exports->n_names; i++) {
		if (strcmp(((((unsigned long long)func_names -
			      sect_hdr->virt_addr) +
			     sect_hdr->raw_ptr) +
			    (unsigned char *)ntdll_base - sect_hdr->virt_addr +
			    sect_hdr->raw_ptr + (unsigned long long)ntdll_base),
			   "LdrLoadDll") == 0)
			ldrloaddll = ((unsigned char *)ntdll_base +
				      exports->funcs_addr)[i];
	}
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
	RtlInitAnsiString(&getlasterror_str, "GetLastError");
	RtlInitAnsiString(&getsysteminfo_str, "GetSystemInfo");
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

	err = LdrGetProcedureAddress(kernel32_handle, &getlasterror_str, 0,
				     &getlasterror);
	if (err != 0)
		abort();

	err = LdrGetProcedureAddress(kernel32_handle, &getsysteminfo_str, 0,
				     &getsysteminfo);
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

unsigned int GetLastError(void)
{
	return ((unsigned int (*)(void))getlasterror)();
}

void GetSystemInfo(void *info)
{
	((void (*)(void *))getsysteminfo)(info);
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
	return ((unsigned char (*)(void *, const void *, unsigned int,
				   unsigned int *, void *))writefile)(
		file, buf, n, written, overlapped);
}

#ifdef __cplusplus
}
#endif
