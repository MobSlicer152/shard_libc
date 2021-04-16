#pragma once

#ifndef _WCHAR_H
#define _WCHAR_H 1

#include "stddef.h"

/**
 * @brief Returns the number of wide characters in __wstr.
 */
extern size_t wcslen(const wchar_t *__str);

#endif /* !_WCHAR_H */
