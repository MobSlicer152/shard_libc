#pragma once

#ifndef _STDDEF_H
#define _STDDEF_H 1

/**
 * @brief Can hold the max value for an integer.
 */
typedef long long intmax_t;

/**
 * @brief Used to store the sizes of things.
 */
typedef unsigned long size_t;

/**
 * @brief wchar_t holds wide characters (i.e. beyond ASCII)
 */
typedef short wchar_t;

/**
 * @brief NULL is used to represent pointers
 * that don't point anywhere (hence the name)
 */
#ifdef __need_NULL
#define NULL (void *)0
#endif /*  __need_NULL */

/**
 * @brief The offsetof macro finds the offset
 * of a given member of a structure. This version
 * is totally cribbed off of Wikipedia's. Basically
 * it gets the address of the member as if it was
 * part of a structure starting at 0, which means it's
 * just the offset of the member from 0 or the
 * start of the structure.
 */
#define offsetof(structure, member) \
	((size_t)&(((structure *)0)->member))

#endif /* !_STDDEF_H */