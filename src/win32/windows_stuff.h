/**
 * @headerfile dumbass_windows_stuff.h
 * @brief Contains handles and other Win32 stuff.
 */

#pragma once

#ifndef _WIN32_WINDOWS_STUFF_H
#define _WIN32_WINDOWS_STUFF_H 1

#ifdef __cplusplus
extern "C" {
#endif

/** @brief A handle to the heap returned by GetProcessHeap */
extern void *__libc_windows_heap;

#ifdef __cplusplus
}
#endif

#endif
