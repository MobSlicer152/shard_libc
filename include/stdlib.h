#pragma once

#ifndef _STDLIB_H
#define _STDLIB_H 1

/* Yay laziness! */
#define __need_size_t
#include "internal/alltypes.h"

/** @brief Terminate program execution with code __status and do cleanup. */
#ifdef _MSC_VER
__declspec(noreturn) extern void exit(int __status);
#else /* _MSC_VER */
extern void exit(int __status) __attribute__((__noreturn__));
#endif /* _MSC_VER */

/** @brief Allocate some memory from the heap of size __size */
extern void *malloc(size_t __size);

#endif /* !_STDLIB_H */
