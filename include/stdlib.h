#pragma once

#ifndef _STDLIB_H
#define _STDLIB_H 1

#include "stddef.h"

/**
 * @brief Terminate program execution abnormally. Only use this
 *  when something goes _really_ wrong.
 * 
 * @returns If this happens, try rebuilding your compiler.
 */
#ifdef _MSC_VER
__declspec(noreturn) extern void abort(void);
#else /* _MSC_VER */
extern void abort(void) __attribute__((__noreturn__));
#endif /* _MSC_VER */

/**
 * @brief Terminate program execution with code __status
 *  and do cleanup (and once I implement it, atexit registered functions).
 * 
 * @param __status is the code to exit with.
 * @returns It shouldn't come to this. If it does, something is very, very wrong.
 */
#ifdef _MSC_VER
__declspec(noreturn) extern void exit(int __status);
#else /* _MSC_VER */
extern void exit(int __status) __attribute__((__noreturn__));
#endif /* _MSC_VER */

/**
 * @brief Terminate program execution with code __status without
 *  doing any cleanup.
 * 
 * @param __status is the code to exit with.
 * @returns Like exit, something is wrong if this happens
 */
#ifdef _MSC_VER
__declspec(noreturn) extern void _exit(int __status);
#else /* _MSC_VER */
extern void _exit(int __status) __attribute__((__noreturn__));
#endif /* _MSC_VER */

/**
 * @brief Allocate some memory from the heap of size __size.
 * 
 */
extern void *malloc(size_t __size);

#endif /* !_STDLIB_H */