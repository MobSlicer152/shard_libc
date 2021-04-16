#pragma once

#ifndef _STDLIB_H
#define _STDLIB_H 1

#include "stddef.h"
#include "stdnoreturn.h"

/**
 * @brief Terminate program execution abnormally. Only use this
 *  when something goes _really_ wrong.
 * 
 * @returns If this happens, try rebuilding your compiler.
 */
extern _Noreturn void abort(void);

/**
 * @brief Terminate program execution with code __status
 *  and do cleanup (and once I implement it, atexit registered functions).
 * 
 * @param __status is the code to exit with.
 * @returns It shouldn't come to this. If it does, something is very, very wrong.
 */
extern _Noreturn void exit(int __status);

/**
 * @brief Terminate program execution with code __status without
 *  doing any cleanup.
 * 
 * @param __status is the code to exit with.
 * @returns Like exit, something is wrong if this happens
 */
extern _Noreturn void _exit(int __status);

/**
 * @brief Allocate some memory from the heap of size __size.
 * 
 * @param __size is the number of bytes to allocate
 * @returns Returns either `NULL` or a buffer of `__size` bytes
 */
extern void *malloc(size_t __size);

/**
 * @brief Free a chunk of memory previously allocated by `malloc` or `calloc`
 * 
 * @param __chunk is the memory to release
 */
extern void free(void *__chunk);

#endif /* !_STDLIB_H */
