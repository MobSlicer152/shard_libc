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
 * @param __number the syscall number
 * @returns the return value of the syscall (RAX)
 */
extern long syscall(unsigned long __number, ...);
#endif

/**
 * @brief Writes __n bytes of __buf to __fd.
 * @param __fd is the file descriptor to write to
 * @param __buf is the buffer to write
 * @param __n is the number of bytes to write
 * @returns The number of bytes written or -1 if an error occurs
 */
extern long write(int __fd, const void *__buf, size_t __n);

#endif /* !_UNISTD_H */
