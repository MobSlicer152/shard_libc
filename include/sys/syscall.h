#pragma once

#ifndef _SYSCALL_H
#define _SYSCALL_H 1

#ifdef __linux__
#ifdef __X86_64__
#include <asm/unistd_64.h> /* This, which is from the Linux kernel sources, gives us all the syscall numbers */
#else
#include <asm/unistd_32.h>
#endif
#elif defined _WIN32
#endif

#endif /* !_SYSCALL_H */
