#pragma once

#ifndef _SYSCALL_H
#define _SYSCALL_H 1

#ifdef __linux__
#include <asm/unistd.h> /* This, which is from the Linux kernel sources, gives us all the syscall numbers */
#elif defined _WIN32
#endif

#endif /* !_SYSCALL_H */
