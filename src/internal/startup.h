#pragma once

#ifndef _STARTUP_H
#define _STARTUP_H 1

#include "registers.h"
#include "stdlib.h"
#include "sys/syscall.h"
#include "unistd.h"

#if defined __linux__ && defined __x86_64__
#include "linux/x86-64/env.h"
#elif defined _WIN32
#include "win32/env.h"
#endif /* defined __linux__ && defined __X86_64__ */

#ifdef __cplusplus
extern "C" {
#endif

/** @brief The signature for the main function */
extern int main(int argc, char **argv, char **envp);

/** @brief Initializes I/O stuff */
extern void __init_stdio(void);

/** @brief Sets stuff up, and retrieves envp */
extern int __init_libc(int __argc, char **__argv);

/** @brief Calls main */
extern int __libc_call_main(int __argc, char **__argv);

/** @brief Clean up */
extern void __shutdown_libc(int __argc, char **__argv,
			    char **__envp);

#ifdef __cplusplus
}
#endif

#endif /* !_STARTUP_H */
