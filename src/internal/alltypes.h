#pragma once

#ifndef _INTERNAL_ALLTYPES_H
#define _INTERNAL_ALLTYPES_H 1

/**
 * @brief This is a convenience header for internal headers and
 * function implementations to use so that namespace pollution
 * can be avoided. It checks for certain macros and defines the
 * requested types. This method for defining types is used by
 * both glibc and musl libc.
 */

#ifdef __need_stdlib_types
#define __need_size_t
#endif /* __need_stdlib_types */

/* stdint types */
#if defined __need_int64_t
#ifndef __int64_t_defined
typedef long long int64_t;
#define __int64_t_defined 1
#endif /* !__int64_t_defined */
#endif /* __need_int64_t */

#if defined __need_uint64_t
#ifndef __uint64_t_defined
typedef unsigned long long uint64_t;
#define __uint64_t_defined
#endif /* !__uint64_t_defined */
#endif /* __need_uint64_t */

/* stdlib types */
#ifdef __need_size_t
#ifndef __size_t_defined
typedef unsigned long size_t;
#define __size_t_defined 1
#endif /* !__size_t_defined */
#endif /* __need_size_t */

/* stdarg types */
#ifdef __need_va_list
#ifndef __va_list_t_defined
#ifndef _MSC_VER
/**
 * @brief This is a placeholder borrowed from Stack Overflow at
 * https://stackoverflow.com/questions/4958384/what-is-the-format-of-the-x86-64-va-list-structure
 */
typedef struct {
	unsigned int gp_offset;
	unsigned int fp_offset;
	void *overflow_arg_area;
	void *reg_save_area;
} __va_list_t[1];
#else /* !_MSC_VER */
typedef char *__va_list_t;
#endif /* !_MSC_VER */
#define __va_list_t_defined
#endif /* !__va_list_t_defined */
#endif /* __need_va_list */

/* wchar type */
#ifdef __need_wchar_t
#ifndef __wchar_t_defined
typedef short wchar_t;
#define __wchar_t_defined 1
#endif /* !__wchar_t_defined */
#endif /* __need_wchar_t */

#endif /* !_INTERNAL_ALLTYPES_H */
