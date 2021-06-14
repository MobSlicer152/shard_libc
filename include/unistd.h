#pragma once

#ifndef _UNISTD_H
#define _UNISTD_H 1

#include "stddef.h"
#include "stdint.h"
#include "sys/types.h"

/**
 * \brief The POSIX-specified buffer that contains
 *  the environment variables for the program.
 */
extern char **environ;

#ifdef __linux__
/**
 * \brief A (so far) usable wrapper for making system calls. *ONLY use this if
 *  the system call you want doesn't have a wrapper around this*.
 * \param __number is the syscall number
 * \param __rdi is the value to put in RDI
 * \param __rsi is the value to put in RSI
 * \param __rdx is the value to put in RDX
 * \param __rcx is the value to put in RCX
 * \param __r8 is the value to put in R8
 * \param __r9 is the value to put in R9
 * 
 * \returns the return value of the syscall (RAX)
 */
extern long syscall(unsigned long __number, long __rdi, long __rsi, long __rdx,
		    long __rcx, long __r8, long __r9);

/**
 * \brief Maps pages (behaviour depends on parameters)
 * \param __addr is the preferred address of the mapping
 * \param __len is the length of the mapping
 * \param __prot is the protection of the pages
 * \param __flags contains the flags for the mapping
 * \param __fd is the file to map (if mapping a file)
 * \param __offset is the offset into a file to map
 * 
 * \returns the address of the mapping on success, (void *)-1 on failure.
 */
extern void *mmap(void *__addr, size_t __len, int __prot, int __flags, int __fd,
		  off_t __offset);

/**
 * \brief Unmaps a region of memory previously mapped by `mmap`
 * \param __addr is the starting address of the mapping
 * \param __len is the length of the mapping
 * \returns 0 for success, -1 for failure
 */
extern int munmap(void *__addr, size_t __len);

/**
 * \brief Resize an existing memory mapping
 * \param __old_addr is the starting address of the original mapping
 * \param __old_size is the size of the original mapping
 * \param __new_size is the new size for the mapping
 * \param __flags contains the flags for the new mapping
 * \param __new_addr is the (optional) new address for the mapping
 */
void *mremap(void *__old_addr, size_t __old_size, size_t __new_size,
	     int __flags, ...);

/**
 * \brief Increase/get the current process break
 * NOT IMPLEMENTED.
 */
void *sbrk(intptr_t __increment);
#elif _WIN32
/* 
 * We need a *function* in assembly to put a number in a register
 *  because of MS making __asm 32-bit only
 */
extern void __move_to_r15(long number);

/* I gotta say, the Windows calling convention is pretty dumb compared to SysV */
extern long __syscall(long rcx, long rdx, long r8, long r9, ...);

/**
 * \brief My own implementation of NTDLL's syscall gate
 */
#define syscall(number, rcx, rdx, r8, r9, ...)            \
	{                                                 \
		__move_to_r15(number);                    \
		__syscall(rcx, rdx, r8, r9, __VA_ARGS__); \
	}

/**
 * \brief `syscall` but you get the return value (usually you want this one)
 */
#define syscall_r(ret, number, rcx, rdx, r8, r9, ...)           \
	{                                                       \
		__move_to_r15(number);                          \
		ret = __syscall(rcx, rdx, r8, r9, __VA_ARGS__); \
	}

#endif

/**
 * \brief Writes __n bytes of __buf to __fd.
 * \param __fd is the file descriptor/handle to write to
 * \param __buf is the buffer to write
 * \param __n is the number of bytes to write
 * 
 * \returns The number of bytes written or -1 if an error occurs
 */
extern long write(int __fd, const void *__buf, size_t __n);

/**
 * \brief Seek to a certain offset into a file, relative to the start,
 *  end, or current offset.
 * 
 * \param __fd is the file to seek in
 * \param __offset is the offset to use
 * \param __whence is where the offset will be relative to
 */
extern off_t lseek(int __fd, off_t __offset, int __whence);

/**
 * \brief Just like lseek, but 64-bit
 * 
 * \param __fd is the file to seek in
 * \param __offset is the offset to use
 * \param __whence is where the offset will be relative to
 */
extern off64_t lseek64(int __fd, off64_t __offset, int __whence);

#endif /* !_UNISTD_H */
