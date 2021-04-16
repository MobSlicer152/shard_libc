#pragma once

#ifndef _LIMITS_H
#define _LIMITS_H 1

/*
 * @brief The width of a boolean (`bool`/`_Bool`)
 */
#define BOOL_WIDTH 1

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
 * @brief The width of an `unsigned long`
 */
#define ULLONG_WIDTH (sizeof(unsigned long long) << 3)

/*
 * @brief The width of an `short int`
 */
#define SHRT_WIDTH (sizeof(short) << 3)

/*
 * @brief The width of an `int`
 */
#define INT_WIDTH (sizeof(int) << 3)

/*
 * @brief The width of an `long`
 */
#define LONG_WIDTH (sizeof(long) << 3)

/*
 * @brief The width of an `long`
 */
#define LLONG_WIDTH (sizeof(long long) << 3)

/*
 * @brief Max number of bytes in a multibyte character
 */
#define MB_LEN_MAX 1

#endif /* !_LIMITS_H */
