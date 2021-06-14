#pragma once

#ifdef _MSC_VER
#ifndef _STDINT_H
#define _STDINT_H 1

/**
 * @brief A 32-bit signed integer
 */
typedef int int32_t;

/**
 * @brief A 32-bit unsigned integer
 */
typedef unsigned int uint32_t;

/**
 * @brief A 64-bit signed integer
 */
typedef long long int64_t;

/**
 * @brief A 64-bit unsigned integer
 */
typedef unsigned long long uint64_t;

/**
 * @brief Biggest possible signed integral type
 */
typedef long long intmax_t;

/**
 * @brief A signed integer the same size as a pointer
 */
typedef long long intptr_t;

/**
 * @brief Biggest possible unsigned integral type
 */
typedef unsigned long long uintmax_t;

/**
 * @brief An unsigned integer the same size as a pointer
 */
typedef unsigned long long uintptr_t;

#endif /* !_STDINT_H */
#else
#include_next "stdint.h"
#endif /* _MSC_VER */
