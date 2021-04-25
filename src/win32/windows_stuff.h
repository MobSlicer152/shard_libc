/**
 * @headerfile dumbass_windows_stuff.h
 * @brief Contains handles and other Win32 stuff.
 */

#pragma once

#ifndef _WIN32_WINDOWS_STUFF_H
#define _WIN32_WINDOWS_STUFF_H 1

#ifdef __cplusplus
extern "C" {
#endif

#include "stddef.h"

/** @brief A handle to the heap returned by GetProcessHeap */
extern void *__libc_windows_heap;

/* Windows macros */
#define CONTAINING_RECORD(address, type, field) \
	((type *)((char *)(address) - (size_t)(&((type *)0)->field)))

/* Counted strings used by NTDLL and kernel functions */
typedef struct _CHAR_STRING {
	unsigned short len;
	unsigned short max_len;
	char *buf;
} CHAR_STRING;
typedef CHAR_STRING ANSI_STRING;
typedef CHAR_STRING UTF8_STRING;

typedef struct _UNICODE_STRING {
	unsigned short len;
	unsigned short max_len;
	wchar_t *buf;
} UNICODE_STRING;

/* Windows function signatures that are loaded by dll_loader.c */
extern wchar_t **CommandLineToArgvW(wchar_t *cmdline, int *argc);
extern void *HeapAlloc(void *heap, unsigned int flags, size_t size);
extern unsigned char HeapFree(void *heap, unsigned int flags, void *chunk);
extern long LdrLoadDll(void *unused_1, void *unused_2, UNICODE_STRING *name,
		       void **base_addr);
extern long LdrGetDllHandle(void *unused_1, void *unused_2,
			    UNICODE_STRING *name, void **handle);
extern long LdrGetProcedureAddress(void *base_addr, ANSI_STRING *procedure,
				   size_t ordinal, void **function);
extern void *LocalFree(void *chunk);
extern void RtlFreeUTF8String(UTF8_STRING *str);
extern long RtlInitAnsiString(ANSI_STRING *dst, const char *src);
extern long RtlInitUnicodeString(UNICODE_STRING *dst, const wchar_t *src);
extern long RtlUnicodeStringToUTF8String(UTF8_STRING *dst,
					 const UNICODE_STRING *src,
					 unsigned char alloc_dst);
extern void *VirtualAlloc(void *addr, size_t size, unsigned int type,
			  unsigned int prot);
extern unsigned char VirtualFree(void *addr, size_t size, unsigned int type);
extern size_t VirtualQuery(const void *addr, void *buf, size_t len);
extern unsigned char WriteFile(void *file, const void *buf, unsigned int n,
			       unsigned int *written, void *overlapped);

/* Structures used to defined the PEB (all from undocumented.ntinternals.net) */
typedef struct _LIST_ENTRY {
	struct _LIST_ENTRY *f;
	struct _LIST_ENTRY *b;
} LIST_ENTRY;

typedef union _LARGE_INTEGER {
	struct {
		unsigned int lo;
		long hi;
	};
	struct {
		unsigned int lo;
		long hi;
	} u;
	long long quad;
} LARGE_INTEGER;

typedef struct _PEB_LDR_DATA {
	size_t len;
	unsigned char initialized;
	void *unknown;
	LIST_ENTRY ld_order_mod_list;
	LIST_ENTRY mem_order_mod_list;
	LIST_ENTRY init_order_mod_list;
} PEB_LDR_DATA;

typedef struct _LDR_MODULE {
	LIST_ENTRY ld_order_mod_list;
	LIST_ENTRY mem_order_mod_list;
	LIST_ENTRY init_order_mod_list;
	void *base_addr;
	void *entry;
	size_t size;
	UNICODE_STRING full_name;
	UNICODE_STRING base_name;
	size_t flags;
	short load_count;
	short tls_idx;
	LIST_ENTRY hash_ent;
	size_t timestamp;
} LDR_MODULE;

typedef struct _RTL_USER_PROCESS_PARAMETERS {
	size_t max_len;
	size_t len;
	size_t flags;
	size_t dbg_flags;
	void *console;
	size_t con_flags;
	void *in;
	void *out;
	void *err;
	UNICODE_STRING cwd;
	void *cwd_handle;
	UNICODE_STRING dllpath;
	UNICODE_STRING img;
	UNICODE_STRING cmdline;
	void *environ;
	size_t start_pos_l;
	size_t start_pos_t;
	size_t width;
	size_t char_w;
	size_t char_h;
	size_t con_txt_attrs;
	size_t wnd_flags;
	size_t sh_wnd_flags;
	UNICODE_STRING wnd_title;
	UNICODE_STRING shell_info;
	UNICODE_STRING rt_data;

	/* I calculated the size of the structure this is supposed to be times 20 */
	char unknown[3840];
} RTL_USER_PROCESS_PARAMETERS;

/* The PEB is the longest structure I have ever encountered. */
typedef struct _PEB {
	unsigned char inherited_addr_spc;
	unsigned char img_exec_opts;
	unsigned char is_being_dbgd;
	unsigned char spare;
	void *mutant;
	void *base;
	PEB_LDR_DATA *ldr;
	RTL_USER_PROCESS_PARAMETERS *params;
	void *subsys_data;
	void *main_heap;
	void *fastlock;
	void *lock_routine;
	void *unlock_routine;
	size_t env_upd_count;
	void **kernel_callbacks;
	void *evt_log_sect;
	void *evt_log;
	void *free_list;
	size_t tls_expansion_counter;
	void *tls_bitmap;
	size_t tls_bitmap_bits[2];
	void *rdonly_mem_base;
	void *rdonly_mem_heap;
	void **rdonly_static_srv_data;
	void *ansi_codepage_data;
	void *oem_codepage_data;
	void *unicode_case_table;
	size_t num_procs;
	size_t globl_flag;
	char spare2[0x4];
	LARGE_INTEGER crit_sect_to;
	size_t heap_res;
	size_t heap_commit;
	size_t heap_decommit_total_free;
	size_t heap_decommit_free_block;
	size_t n_heaps;
	size_t max_heaps;
	void ***heaps;
	void *gdi_shard_handles;
	void *proc_starter_helper;
	void *gdi_dev_ctx_attrs;
	void *ldr_lock;
	size_t os_maj_ver;
	size_t os_min_ver;
	size_t os_bld_num;
	size_t os_plat_id;
	size_t img_subsys_maj_ver;
	size_t img_subsys_min_ver;
	size_t gdi_handle_buffer[0x22];
	size_t post_init_routine;
	size_t tls_expansion_bitmap;
	char tls_expansion_bitmap_bits[0x80];
	size_t session_id;
} PEB;

extern PEB *__libc_windows_peb;

/* Assembly function that stores the PEB (FS:[30]) in RAX */
extern PEB *__get_peb(void);

/* Windows-supported image format signatures */
#define IMAGE_DOS_SIGNATURE 0x5A4D
#define IMAGE_NT_SIGNATURE 0x00004550
#define IMAGE_NT_OPTIONAL_HDR64_MAGIC 0x20b

/* The offset for the export directory in the data directory */
#define IMAGE_DIRECTORY_ENTRY_EXPORT 0

/* PE image headers used for parsing NTDLL */
typedef struct _IMAGE_DOS_HEADER {
	unsigned short magic;
	unsigned short bytes_last_page;
	unsigned short page_count;
	unsigned short n_relocations;
	unsigned short n_header_paragraphs;
	unsigned short min_alloc;
	unsigned short max_alloc;
	unsigned short ss;
	unsigned short sp;
	unsigned short checksum;
	unsigned short ip;
	unsigned short cs;
	unsigned short reloc_tab_addr;
	unsigned short overlay_num;
	unsigned short res1[4];
	unsigned short oemid;
	unsigned short oeminfo;
	unsigned short res2[10];
	long nt_hdr_addr;
} IMAGE_DOS_HEADER;

typedef struct _IMAGE_FILE_HEADER {
	unsigned short mach;
	unsigned short n_sects;
	unsigned int timestamp;
	unsigned int symtab;
	unsigned int n_syms;
	unsigned short opt_hdr_size;
	unsigned short characteristics;
} IMAGE_FILE_HEADER;

typedef struct _IMAGE_DATA_DIRECTORY {
	unsigned int virt_addr;
	unsigned int size;
} IMAGE_DATA_DIRECTORY;

typedef struct _IMAGE_OPTIONAL_HEADER64 {
	unsigned short magic;
	unsigned char lnkr_maj_ver;
	unsigned char lnkr_min_ver;
	unsigned int code_size;
	unsigned int initialized_data_size;
	unsigned int uninitialized_data_size;
	unsigned int entry_addr;
	unsigned int code_base;
	unsigned int data_base;
	unsigned long long img_base;
	unsigned int sect_align;
	unsigned int file_align;
	unsigned short os_maj_ver;
	unsigned short os_min_ver;
	unsigned short img_maj_ver;
	unsigned short img_min_ver;
	unsigned short subsys_maj_ver;
	unsigned short subsys_min_ver;
	unsigned int w32_ver;
	unsigned int img_size;
	unsigned int hdr_size;
	unsigned int checksum;
	unsigned short subsys;
	unsigned short dll_characteristics;
	unsigned long long stack_res;
	unsigned long long stack_commit;
	unsigned long long heap_res;
	unsigned long long head_commit;
	unsigned int ldr_flags;
	unsigned int num_rvas_and_sizes;
	IMAGE_DATA_DIRECTORY data_dir[16];
} IMAGE_OPTIONAL_HEADER64;

typedef struct _IMAGE_NT_HEADERS64 {
	unsigned int sig;
	IMAGE_FILE_HEADER fhdr;
	IMAGE_OPTIONAL_HEADER64 ohdr;
} IMAGE_NT_HEADERS64;

typedef struct _IMAGE_EXPORT_DIRECTORY {
	unsigned int characteristics;
	unsigned int timestamp;
	unsigned short maj_ver;
	unsigned short min_ver;
	unsigned int name;
	unsigned int base;
	unsigned int n_funcs;
	unsigned int n_names;
	unsigned int funcs_addr;
	unsigned int names_addr;
	unsigned int ordinals_addr;
} IMAGE_EXPORT_DIRECTORY;

typedef struct _IMAGE_SECTION_HEADER {
	unsigned char name[8];
	union {
		unsigned int phys_addr;
		unsigned int virt_addr;
	} misc;
	unsigned int virt_addr;
	unsigned int raw_size;
	unsigned int raw_ptr;
	unsigned int reloc_ptr;
	unsigned int line_nums_ptr;
	unsigned short n_relocs;
	unsigned short n_line_nums;
	unsigned int characteristics;
} IMAGE_SECTION_HEADER;

#ifdef __cplusplus
}
#endif

#endif
