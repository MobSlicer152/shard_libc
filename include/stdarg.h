#pragma once

#ifdef _MSC_VER
#ifndef _STDARG_H
#define _STDARG_H 1

#ifndef _MSC_VER
typedef __builtin_va_list va_list;
#else /* !_MSC_VER */
typedef char *va_list;
#endif /* !_MSC_VER */

/**
 * To ensure they work properly, these are either builtins
 * or slightly changed versions of Microsoft's functions
 */
#ifdef _MSC_VER
#define va_start(__list, __start) __va_start(&__list, __start)
#define va_end(__list) ((void)(__list = (va_list)0))
#define va_arg(__list, __type)                              \
	((sizeof(__type) > sizeof(unsigned long long) ||                \
	  (sizeof(__type) & (sizeof(__type) - 1)) != 0) ?    \
		 **(__type **)((__list += sizeof(unsigned long long)) - \
			       sizeof(unsigned long long)) :            \
		 *(__type *)((__list += sizeof(unsigned long long)) - sizeof(unsigned long long)))
#define va_copy(__dst, __src) ((__dst) = (__src))
#else /* _MSC_VER */
#define va_start(__list, __start) __builtin_va_start(__list, __start)
#define va_end(__list) __builtin_va_end(__list)
#define va_arg(__list, __type) __builtin_va_arg(__list, __type)
#define va_copy(__dst, __src) __builtin_va_copy(__dst, __src)
#endif /* _MSC_VER */

#endif /* !_STDARG_H */
#else
#include_next "stdarg.h"
#endif /* _MSC_VER */
