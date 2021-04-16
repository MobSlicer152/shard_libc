#pragma once

#ifndef _UNISTD_H
#define _UNISTD_H 1

#include <stddef.h>

/**
 * @brief The POSIX-specified buffer that contains
 *  the environment variables for the program.
 */
extern char **environ;

#ifdef __linux__
/**
 * @brief A (so far) usable wrapper for making system calls. ONLY use this if
 *  the system call you want doesn't have a wrapper *around this*.
 * @param __number is the syscall number
 * @param __rdi is the value to put in RDI
 * @param __rsi is the value to put in RSI
 * @param __rdx is the value to put in RDX
 * @param __rcx is the value to put in RCX
 * @param __r8 is the value to put in R8
 * @param __r9 is the value to put in R9
 * 
 * @returns the return value of the syscall (RAX)
 */
extern long syscall(unsigned long __number, long __rdi, long __rsi, long __rdx, long __rcx, long __r8, long __r9);
#endif

/**
 * @brief Writes __n bytes of __buf to __fd.
 * @param __fh is the Win32 file handle to write to
 * @param __fd is the file descriptor to write to
 * @param __buf is the buffer to write
 * @param __n is the number of bytes to write
 * 
 * @returns The number of bytes written or -1 if an error occurs
 */
#ifdef _WIN32
extern long write(void *__fh, const void *__buf, size_t __n);
#else /* _WIN32 */
extern long write(int __fd, const void *__buf, size_t __n);
#endif  /* _WIN32 */

#endif /* !_UNISTD_H */
