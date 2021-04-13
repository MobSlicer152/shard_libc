#pragma once

#ifndef _SYSCALL_H
#define _SYSCALL_H 1

#ifdef __linux__
#include <asm/unistd.h> /* This, which is from the Linux kernel sources, gives us all the syscall numbers */
#elif defined _WIN32
/*
 * wchar_t might not be defined by the compiler (which it sometimes is).
 * and the Win32 headers need it defined
 */
#include "stddef.h"

#include <windows.h> /* 
		      * This defines the signatures for a lot of Windows API
		      * functions (which are as close as you (practically) get
		      * to system calls on Windows)
		      */
#endif

#endif /* !_SYSCALL_H */
