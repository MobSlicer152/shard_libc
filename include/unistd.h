#pragma once

#ifndef _UNISTD_H
#define _UNISTD_H 1

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

#endif /* !_UNISTD_H */
