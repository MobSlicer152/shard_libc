#pragma once

#ifndef _UNISTD_H
#define _UNISTD_H 1

#include <stddef.h>

/**
 * @brief The POSIX-specified variable that contains
 *  the environment variables for the program.
 */
extern char **environ;

#ifdef __linux__
/**
 * @brief A (so far) usable wrapper for making system calls.
 */
extern long __syscall(unsigned long number, ...);

/* For the sake of being nice to glibc-dependant code, this is here */
#ifdef _GNU_SOURCE
#define syscall __syscall
#endif
#endif /* __linux__ */

/**
 * @brief Writes __n bytes of __buf to __fd.
 */
extern long write(int __fd, const void *__buf, size_t __n);

#endif /* !_UNISTD_H */
