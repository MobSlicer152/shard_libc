#pragma once

#ifndef _STDLIB_H
#define _STDLIB_H 1

/* size_t is actually supposed to be defined here. */
#define __need_size_t
#include "internal/alltypes.h"

/** @brief Terminate program execution with code __status and do cleanup. */
extern void exit(int __status) __attribute__((__noreturn__));

/** @brief Allocate some memory from the heap of size __size */
extern void *malloc(size_t __size);

#endif /* !_STDLIB_H */
