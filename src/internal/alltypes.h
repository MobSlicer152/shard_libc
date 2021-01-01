#pragma once

#ifndef _INTERNAL_ALLTYPES_H
#define _INTERNAL_ALLTYPES_H 1

/**
 * @brief This is a convenience header for internal headers and
 * function implementations to use so that namespace pollution
 * can be avoided. It checks for certain macros and defines the
 * requested types. This method for defining types is used by
 * musl libc and (although implemented differently) glibc.
 */

/* stdint types */
#ifdef __need_int64_t
typedef long long int64_t;
#undef __need_int64_t
#endif /* __need_int64_t */

#ifdef __need_uint64_t
typedef unsigned long long uint64_t;
#undef __need_uint64_t
#endif /* __need_uint64_t */

/* stddef types */
#ifdef __need_intmax_t
typedef long long intmax_t;
#undef __need_intmax_t
#endif /* __need_intmax_t */

#ifdef __need_size_t
typedef unsigned long size_t;
#undef __need_size_t
#endif /* __need_size_t */

#ifdef __need_wchar_t
typedef short wchar_t;
#undef __need_wchar_t
#endif /* __need_wchar_t */

/* stdarg types */
#ifdef __need_va_list
#ifdef __clang__
typedef __builtin_va_list va_list;
#elif _MSC_VER /* __clang__ */
typedef char *va_list; /* MSVC expects this to be a char *, so why not? */
#elif __GNUC__ /* __clang__ */
typedef __gnuc_va_list va_list;
#endif /* __clang__ */
#undef __need_va_list
#endif /* __need_va_list */

#endif /* !_INTERNAL_ALLTYPES_H */
