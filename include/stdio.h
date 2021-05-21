#pragma once

#ifndef _STDIO_H
#define _STDIO_H 1

#include "stddef.h"
#include "stdarg.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct __file {
	unsigned long fd; /* File descriptor (a handle on Windows) */
	char mode[3]; /* The mode the file is open in */
	char *buf; /* Buffer to use */
	char *off; /* Offset from start of file */
	char *base; /* Address of mapped file */
	char *max; /* End address of mapped file (base + len) */
	size_t len; /* Internal initial length of file, for read files */
} *FILE;

/* Standard input */
extern FILE **__stdin(void);
#define stdin (*__stdin())

/* Standard output */
extern FILE **__stdout(void);
#define stdout (*__stdout())

/* Standard error */
extern FILE **__stderr(void);
#define stderr (*__stderr())

#ifdef _INTERNAL_STDIO_DEFS
/* Whether I/O has been initialized */
extern _Bool *__stdio_initialized(void);
#endif

/**
 * @brief Write formatted text to __fp
 * @param __fp is the FILE pointer to use
 * @param __str is the text to write
 * @param __alist is the argument list to use
 * 
 * @returns the number of bytes written
 */
extern int vfprintf(FILE *__fp, const char *restrict __str, va_list __alist);

/**
 * @brief Write formatted text to __fp
 * @param __fp is the FILE pointer to use
 * @param __str is the text to write
 * 
 * @returns the number of bytes written
 */
extern int fprintf(FILE *__fp, const char *restrict __str, ...);

/**
 * @brief Write __count chunks of size __size from __buf to __fp
 * @param __buf is the buffer to use
 * @param __size is the size of the chunks
 * @param __count is the number of chunks to write
 * @param __fp is the FILE pointer to write to
 * 
 * @returns the number of bytes written
 */
extern size_t fwrite(const void *restrict __buf, size_t __size, size_t __count,
	      FILE *restrict __fp);

#ifdef __cplusplus
}
#endif

#endif
