/**
 * @headerfile string.h
 * @brief String/buffer related functions
 * 
 * Contains the definitions of the standard library functions for
 * string and memory manipulation.
 */

#pragma once

#ifndef _STRING_H
#define _STRING_H 1

#include "stddef.h"

/**
 * @brief Copies up to __n bytes of __src to __dst until __c occurs.
 * Returns a pointer to the byte after __c's occurence or NULL.
 */
extern void *memccpy(void *restrict __dst, const void *restrict __src, int __c,
		     size_t __n);

/**
 * @brief Copies __n bytes of __src to __dst.
 * 
 * If __src and __dst overlap then you get undefined behaviour.
 * 
 * @param __dst is where to copy to
 * @param __src is where to copy from
 * @param __n is how many bytes to copy
 * @returns The value of __dst.
 */
extern void *memcpy(void *restrict __dst, const void *restrict __src,
		    size_t __n);

/**
 * @brief Copies __n bytes of __src to a temporary buffer and then into __dst.
 * Returns __dst. 
 */
extern void *memmove(void *__dst, const void *__src, size_t __n);

/**
 * @brief Overwrites __n bytes of __dst with __c
 * @return Returns __dst
 */
extern void *memset(void *__dst, int __c, size_t __n);

/**
 * @brief Returns the difference between __s1 and __s2
 */
extern int strcmp(const char *__s1, const char *__s2);

/**
 * @brief Returns the number of characters in __str.
 */
extern size_t strlen(const char *__str);

/**
 * @brief Copies up to __n characters of __src to __dst,
 *  until '\0' is encountered.
 */
extern char *strncpy(char *__dst, const char *__src, size_t __n);

#endif /* !_STRING_H */
