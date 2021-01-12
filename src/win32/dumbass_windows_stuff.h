/**
 * @headerfile dumbass_windows_stuff.h
 * @brief Contains handles and other dumb Win32 stuff.
 * 
 * Dear Microsoft:
 * 
 * I kind of don't like the Windows API that much. It's easy to
 * use and really well documented, but I hate the way it's designed.
 * I mean, a handle is _literally just an arbitrary value with no
 * f*cking use or meaning_ that the kernel gives you and keeps track of.
 * I would much rather just use _sane, logical, Hungarian notation and CamelCase free
 * structs and parameter names, and non-"renamed-for-standard-conformance"
 * POSIX functions, like Linux has
 * 
 * It drives people away from developping for Windows.
 * Please consider this.
 *
 * That said, this file contains handles for Windows-y stuff such as the process's heap.
 */

#pragma once

#ifndef _WIN32_DUMBASS_WINDOWS_STUFF_H
#define _WIN32_DUMBASS_WINDOWS_STUFF_H 1

/* wchar_t might not be defined by the compiler, and the Win32 headers need it defined */
#include "stddef.h"

#include <windows.h>

/** @brief A handle to the heap returned by GetProcessHeap */
extern HANDLE __libc_windows_heap;

#endif
