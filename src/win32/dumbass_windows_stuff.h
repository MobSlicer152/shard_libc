/**
 * @headerfile dumbass_windows_stuff.h
 * @brief Contains handles and other dumb Win32 stuff.
 * 
 * Dear Microsoft:
 * 
 * I kind of don't like the Windows API that much. It's easy to
 *  use and really well documented, but I hate the way it's designed.
 *  I mean, a handle is _literally just an arbitrary opaque value with no
 *  f*cking use or meaning_ that the kernel gives you and keeps track of. At
 *  least Linux tells you specifically when there's nothing to be gained
 *  from an object's internal details. If you're trying to use an internal
 *  API to do a specific task and you CAN'T because it's subject to change
 *  and therefore deemed not worth documenting, you have to do insane amounts
 *  of sifting through ancient blog posts, which hurts.
 *  
 * I would much rather just use _sane, logical, Hungarian notation and
 *  CamelCase free structs and parameter names, by-version function/structure
 *  documentation, and non-"renamed-for-standard-conformance" POSIX functions,
 *  like Linux has.
 * 
 * It drives people away from developping for Windows.
 * Please consider this.
 *
 * That said, this file contains handles for Windows-y stuff such as the process's heap.
 */

#pragma once

#ifndef _WIN32_DUMBASS_WINDOWS_STUFF_H
#define _WIN32_DUMBASS_WINDOWS_STUFF_H 1

#ifdef __cplusplus
extern "C" {
#endif

/** @brief A handle to the heap returned by GetProcessHeap */
extern void *__libc_windows_heap;

#ifdef __cplusplus
}
#endif

#endif
