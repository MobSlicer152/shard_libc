#pragma once

#ifdef _MSC_VER
#ifndef _LIMITS_H
#define _LIMITS_H 1

/*
 * @brief The width of a boolean (`bool`/`_Bool`)
 */
#define BOOL_WIDTH (sizeof(char) << 3)

/*
 * @brief How thicc the smallest non-bitfield object (`char`) is
 */
#define CHAR_BIT (sizeof(char) << 3)
#define _CHAR_THICCNESS CHAR_BIT

/*
 * @brief The width of an `unsigned short int`
 */
#define USHRT_WIDTH (sizeof(unsigned short) << 3)

/*
 * @brief The width of an `unsigned int`
 */
#define UINT_WIDTH (sizeof(unsigned int) << 3)

/*
 * @brief The width of an `unsigned long`
 */
#define ULONG_WIDTH (sizeof(unsigned long) << 3)

/*
 * @brief The width of an `unsigned long long`
 */
#define ULLONG_WIDTH (sizeof(unsigned long long) << 3)

/*
 * @brief The width of a `short int`
 */
#define SHRT_WIDTH (sizeof(short) << 3)

/*
 * @brief The width of an `int`
 */
#define INT_WIDTH (sizeof(int) << 3)

/*
 * @brief The width of a `long`
 */
#define LONG_WIDTH (sizeof(long) << 3)

/*
 * @brief The width of a `long long`
 */
#define LLONG_WIDTH (sizeof(long long) << 3)

/*
 * @brief Max number of bytes in a multibyte character
 */
#define MB_LEN_MAX 1

/**
 * @brief Minimum value of a `signed char`
 */
#define SCHAR_MIN -128

/**
 * @brief Max value of a `signed char`
 */
#define SCHAR_MAX 128

/**
 * @brief Max value of an `unsigned char`
 */
#define UCHAR_MIN 255

/**
 * @brief Minimum value of a `char`
 */
#define CHAR_MIN SCHAR_MIN

/**
 * @brief Max value of a `char`
 */
#define CHAR_MAX SCHAR_MAX

/**
  * @brief Minimum value of a `short int`
  */
#define SHRT_MIN -32768

/**
   * @brief Max value of a `short int`
   */
#define SHRT_MAX 32767

/**
 * @brief Max value of an `unsigned short int`
 */
#define USHRT_MAX 32767

/**
 * @brief Minimum value of an `int`
 */
#define INT_MIN -2147483647

/**
 * @brief Max value of an `int`
 */
#define INT_MAX 2147483647

/**
 * @brief Max value of an `unsigned int`
 */
#define UINT_MAX 4294967295

/**
 * @brief Minimum value of a `long int`
 */
#define LONG_MIN -2147483647

/**
 * @brief Max value of a `long int`
 */
#define LONG_MAX 2147483647

/**
 * @brief Max value of an `unsigned long int`
 */
#define ULONG_MAX UINT_MAX

/**
 * @brief Minimum value of a `long long int`
 */
#define LLONG_MIN -9223372036854775807

/**
 * @brief Max value of a `long long int`
 */
#define LLONG_MAX 9223372036854775807

/**
 * @brief Max value of an `unsigned long long int`
 */
#define ULLONG_MAX 18446744073709551615

#endif /* !_LIMITS_H */
#else
#include_next "limits.h"
#endif /* _MSC_VER */
