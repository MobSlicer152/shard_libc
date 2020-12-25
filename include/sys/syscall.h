#pragma once

#ifndef _SYSCALL_H
#define _SYSCALL_H 1

#ifdef __linux__
#include <asm/unistd.h>
#elif defined _WIN32
#include <windows.h> /* 
		      * Technically this defines the signatures for a lot of Windows API
		      * functions (which are as close as you get to system calls on Windows)
		      */
#endif

#endif /* !_SYSCALL_H */
