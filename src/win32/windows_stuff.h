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
	((type *)((char *)(address) - offsetof(type, field)))

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

/* Stuff added to get Windows parts of dlmalloc to work under MinGW */
#ifndef _MSC_VER
#define __int64 long long
#endif

typedef struct _MEMORY_BASIC_INFORMATION {
	void *BaseAddress;
	void *AllocationBase;
	unsigned int AllocationProtect;
	unsigned short PartitionId;
	size_t RegionSize;
	unsigned int State;
	unsigned int Protect;
	unsigned int Type;
} MEMORY_BASIC_INFORMATION;

typedef struct _SYSTEM_INFO {
	union {
		unsigned int dwOemId;
		struct {
			unsigned short wProcessorArchitecture;
			unsigned short wReserved;
		};
	};
	unsigned int dwPageSize;
	void *lpMinimumApplicationAddress;
	void *lpMaximumApplicationAddress;
	unsigned int dwActiveProcessorMask;
	unsigned int dwNumberOfProcessors;
	unsigned int dwProcessorType;
	unsigned int dwAllocationGranularity;
	unsigned short wProcessorLevel;
	unsigned short wProcessorRevision;
} SYSTEM_INFO;

typedef struct _FILETIME {
	unsigned int dwLowDateTime;
	unsigned int dwHighDateTime;
} FILETIME;

#define MEM_COMMIT 0x1000
#define MEM_RESERVE 0x2000
#define MEM_RELEASE 0x8000
#define MEM_FREE 0x10000
#define MEM_DECOMMIT 0x4000
#define MEM_TOP_DOWN 0x100000
#define PAGE_EXECUTE 0x10
#define PAGE_EXECUTE_READ 0x20
#define PAGE_EXECUTE_READWRITE 0x40
#define PAGE_NOACCESS 0x1
#define PAGE_READONLY 0x2
#define PAGE_READWRITE 0x04
#define ERROR_INVALID_ADDRESS 0x1E7

/* Structures used to define the PEB and other stuff (all internal ones from https://www.vergiliusproject.com/kernels/x64/Windows%2010%20%7C%202016/2009%2020H2%20(October%202020%20Update)) */
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

typedef union _ULARGE_INTEGER {
	struct {
		unsigned int lo;
		unsigned long hi;
	};
	struct {
		unsigned int lo;
		unsigned long hi;
	} u;
	unsigned long long quad;
} ULARGE_INTEGER;

typedef struct _IO_STATUS_BLOCK {
	union {
		long status;
		void *ptr;
	};
	unsigned long info;
} IO_STATUS_BLOCK;

typedef struct _PEB_LDR_DATA {
	unsigned long len;
	unsigned char initialized;
	void *unknown;
	LIST_ENTRY ld_order_mod_list;
	LIST_ENTRY mem_order_mod_list;
	LIST_ENTRY init_order_mod_list;
	void *entry_in_progress;
	unsigned char shutdown_in_progress;
	void *shutdown_thrd_id;
} PEB_LDR_DATA;

typedef struct _LDR_MODULE {
	LIST_ENTRY ld_order_mod_list;
	LIST_ENTRY mem_order_mod_list;
	LIST_ENTRY init_order_mod_list;
	void *base_addr;
	void *entry;
	unsigned long size;
	UNICODE_STRING full_name;
	UNICODE_STRING base_name;
	unsigned long flags;
	short load_count;
	short tls_idx;
	LIST_ENTRY hash_ent;
	unsigned long timestamp;
} LDR_MODULE;

typedef struct _CURDIR {
	UNICODE_STRING path;
	void *handle;
} CURDIR;

typedef struct _RTL_USER_PROCESS_PARAMETERS {
	unsigned long max_len;
	unsigned long len;
	unsigned long flags;
	unsigned long dbg_flags;
	void *console;
	unsigned long con_flags;
	void *in;
	void *out;
	void *err;
	CURDIR cwd;
	UNICODE_STRING dllpath;
	UNICODE_STRING img;
	UNICODE_STRING cmdline;
	void *environ;
	unsigned long start_pos_x;
	unsigned long start_pos_y;
	unsigned long count_w;
	unsigned long count_h;
	unsigned long char_w;
	unsigned long char_h;
	unsigned long fill_attr;
	unsigned long wnd_flags;
	unsigned long sh_wnd_flags;
	UNICODE_STRING wnd_title;
	UNICODE_STRING desktop_info;
	UNICODE_STRING shell_info;
	UNICODE_STRING rt_data;
	char unknown[0x18 * 32];
	unsigned long long environ_size;
	unsigned long long environ_ver;
	void *pkg_dep_data;
	unsigned long process_gid;
	unsigned long ldr_thrds;
	UNICODE_STRING redir_dll_name;
	UNICODE_STRING heap_part_name;
	unsigned long long def_thrd_pool_cpu_set_masks;
	unsigned long def_thrd_pool_cpu_set_mask_count;
	unsigned long def_thrd_pool_max;
} RTL_USER_PROCESS_PARAMETERS;

/* The PEB is the longest structure I have ever encountered. */
typedef struct _PEB {
	unsigned char inherited_addr_spc;
	unsigned char img_exec_opts;
	unsigned char is_being_dbgd;
	union {
		unsigned char bitfield;
		struct {
			unsigned char uses_large_pages : 1;
			unsigned char is_protected : 1;
			unsigned char is_img_dynamically_relocated : 1;
			unsigned char skip_patching_u32_forwarders : 1;
			unsigned char is_pkged_process : 1;
			unsigned char is_app_cont : 1;
			unsigned char is_protected_process_light : 1;
			unsigned char is_long_path_aware : 1;
		};
	};
	unsigned char padding0[4];
	void *mutant;
	void *base;
	PEB_LDR_DATA *ldr;
	RTL_USER_PROCESS_PARAMETERS *params;
	void *subsys_data;
	void *main_heap;
	void *fastlock;
	void *atl_thunk_list_ptr;
	void *ifeokey;
	union {
		unsigned long cross_flags;
		struct {
			unsigned long in_job : 1;
			unsigned long initializing : 1;
			unsigned long using_veh : 1;
			unsigned long using_vch : 1;
			unsigned long using_fth : 1;
			unsigned long previously_throttled : 1;
			unsigned long currently_throttled : 1;
			unsigned long images_hot_patched : 1;
			unsigned long reserved0 : 24;
		};
	};
	unsigned char padding1[4];
	unsigned long sys_reserved;
	unsigned long atl_thunk_list_ptr_32;
	void *api_set_map;
	unsigned long tls_exp_counter;
	unsigned char padding2[4];
	void *tls_bitmap;
	unsigned long tls_bitmap_bits[2];
	void *rdonly_shared_mem_base;
	void *shared_data;
	void **rdonly_static_server_data;
	void *ansi_codepage_data;
	void *oem_codepage_data;
	void *unicode_case_table_data;
	unsigned long n_procs;
	unsigned long nt_globl_flag;
	LARGE_INTEGER critical_timeout;
	unsigned long long heap_seg_res;
	unsigned long long heap_seg_commit;
	unsigned long long heap_decommit_total_free_threshold;
	unsigned long long heap_decommit_free_block_threshold;
	unsigned long n_heaps;
	unsigned long max_n_heaps;
	void **heaps;
	void *gdi_shared_handle_tab;
	void *proc_started_helper;
	unsigned long gdi_dc_attr_list;
	unsigned char padding3[4];
	void *ldr_lock;
	unsigned long os_maj_ver;
	unsigned long os_min_ver;
	unsigned short os_build_no;
	unsigned short os_csd_ver;
	unsigned long os_platform_id;
	unsigned long subsys;
	unsigned long subsys_maj_ver;
	unsigned long subsys_min_ver;
	unsigned char padding4[4];
	unsigned long long active_proc_affinity_mask;
	unsigned long gdi_handle_buf[60];
	void (*post_proc_init_routine)();
	void *tls_exp_bitmap;
	unsigned long tls_exp_bitmap_bits[32];
	unsigned long session_id;
	unsigned char padding5[4];
	ULARGE_INTEGER compat_flags;
	ULARGE_INTEGER compat_flags_user;
	void *shim_data;
	void *compat_info;
	UNICODE_STRING csd_ver;
	void *activation_ctx_data;
	void *proc_assembly_storage_map;
	void *sys_def_activation_ctx;
	void *sys_assembly_storage_map;
	unsigned long long min_stack_commit;
	void *spare_ptrs[4];
	unsigned long spare_ulongs[5];
	void *wer_reg_data;
	void *wer_ship_assert_ptr;
	void *unused;
	void *img_hdr_hash;
	union {
		unsigned long trace_flags;
		struct {
			unsigned long heap_tracing_enabled : 1;
			unsigned long crit_sec_tracing_enabled : 1;
			unsigned long ldr_tracing_enabled : 1;
			unsigned long spare_tracing_bits : 29;
		};
	};
	unsigned char padding6[4];
	unsigned long long csr_server_rdonly_shared_mem_base;
	unsigned long long tpp_workerp_list_lock;
	LIST_ENTRY tpp_workerp_list;
	void *wait_on_addr_hash_tab[128];
	void *telem_coverage_hdr;
	unsigned long cloud_file_flags;
	unsigned long cloud_file_diag_flags;
	char plcholder_compat_mode;
	char plcholder_compat_mode_res[7];
	void *leap_sec_data;
	union {
		unsigned long leap_sec_flags;
		struct {
			unsigned long sixty_sec_enabled : 1;
			unsigned long res : 31;
		};
	};
	unsigned long nt_globl_flag2;
} PEB;

extern PEB *__libc_windows_peb;

/* Assembly function to read gs:60h */
extern PEB *__get_peb(void);

/* Windows-supported image format signatures */
#define IMAGE_DOS_SIGNATURE 0x5A4D
#define IMAGE_NT_SIGNATURE 0x00004550
#define IMAGE_NT_OPTIONAL_HDR64_MAGIC 0x20b

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

/* Windows function signatures that are loaded by dll_loader.c */
extern wchar_t **CommandLineToArgvW(wchar_t *cmdline, int *argc);
extern wchar_t *GetCommandLineW(void);
extern void *GetCurrentProcess(void);
extern void *GetCurrentThread(void);
extern void *GetProcessHeap(void);
extern unsigned char GetProcessTimes(void *process, FILETIME *creation,
				     FILETIME *exit, FILETIME *kernel,
				     FILETIME *user);
void GetSystemInfo(void *info);
unsigned char GetThreadTimes(void *process, FILETIME *creation, FILETIME *exit,
			     FILETIME *kernel, FILETIME *user);
extern void *HeapAlloc(void *heap, unsigned int flags, size_t size);
extern unsigned char HeapFree(void *heap, unsigned int flags, void *chunk);
extern long LdrGetDllHandle(void *unused_1, void *unused_2,
			    UNICODE_STRING *name, void **handle);
extern long LdrGetProcedureAddress(void *base_addr, ANSI_STRING *procedure,
				   unsigned long ordinal, void **function);
extern long LdrLoadDll(void *unused_1, void *unused_2, UNICODE_STRING *name,
		       void **base_addr);
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

#ifdef __cplusplus
}
#endif

#endif
