#pragma once

#ifndef _UNISTD_H
#define _UNISTD_H 1

/**
 * @brief The POSIX-specified variable that contains
 *  the environment variables for the program.
 */
extern char **environ;

/**
 * @brief A likely entirely broken wrapper for making system calls.
 */
extern long __syscall(unsigned long number, ...);

#endif /* !_UNISTD_H */
