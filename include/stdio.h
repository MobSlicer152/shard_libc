#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef struct file {
	unsigned long fd; /* File descriptor (a handle on Windows) */
	char *off; /* Offset from start of file */
	char *base; /* Address of mapped file */
	char *max; /* End address of mapped file (base + len) */
	size_t len; /* Internal initial length of file, for read files */
} *FILE;

/* 
 * These are the internal names, don't use them if the function to get
 *  that info is implemented
 */
extern FILE *___stdin; /* Internal name for stdin */
extern FILE *___stdout; /* Internal name for stdout */
extern FILE *___stderr; /* Internal name for stderr */

/* Standard input */
#define stdin (___stdin)

/* Standard output */
#define stdout (___stdout)

/* Standard error */
#define stderr (___stderr)

#ifdef __cplusplus
}
#endif
