#pragma once

#ifndef _WCHAR_H
#define _WCHAR_H 1

#include "stddef.h"

/**
 * @brief Returns the difference between __s1 and __s2
 */
extern int wcscmp(const wchar_t *__s1, const wchar_t *__s2);

/**
 * @brief Returns the number of wide characters in __wstr.
 */
extern size_t wcslen(const wchar_t *__str);

#endif /* !_WCHAR_H */
