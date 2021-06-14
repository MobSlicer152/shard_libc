#pragma once

#ifndef BITHACKS_H
#define BITHACKS_H 1

/* Combine two numbers */
#define CONCAT(lo, hi, type, target) ((target)(((type)hi) << ((target)(sizeof(type) << 3)) | ((type)lo)))

/* Get high and low halves of any built-in integer */
#define HIGH(x, target) ((target)((x) >> (target)((sizeof(target) << 3) >> 1)))
#define LOW(x, target) ((target)((x) & ((target)(1 << (sizeof(x) << 3) - 1))))

/* Word hacks (https://graphics.stanford.edu/~seander/bithacks.html#ValueInWord) */

/* Check if a x has a zero byte */
#define WORD_HAS_ZERO(x) (((x)-0x01010101UL) & ~(x)&0x80808080UL)

/* Check if x has a byte equal to n */
#define WORD_HAS_N(x, n) (WORD_HAS_ZERO((x) ^ (~0UL / 255 * (n))))

/* Check if x has a byte less than n */
#define WORD_HAS_LT_N(x, n) (((x) - ~0L / 255 * (n)) & ~(x) & ~0L / 255 * 128)

/* Count how many bytes of x are less than n */
#define WORD_COUNT_LT_N(x, n)                                            \
	(((~0UL / 255 * (127 + (n)) - ((x) & ~0UL / 255 * 127)) & ~(x) & \
	  ~0UL / 255 * 128) /                                            \
	 128 % 255)

/* Check if x has a byte greater than n */
#define WORD_HAS_GT_N(x, n) \
	(((x) + ~0UL / 255 * (127 - (n)) | (x)) & ~0UL / 255 * 128)

/* Count how many bytes of x are more than n */
#define WORD_COUNT_GT_N(x, n)                                           \
	(((((x) & ~0UL / 255 * 127) + ~0UL / 255 * (127 - (n)) | (x)) & \
	  ~0UL / 255 * 128) /                                           \
	 128 % 255)

/* Check if x has a byte between m and n */
#define WORD_HAS_BETWEEN_M_N(x, m, n)                                  \
	((~0UL / 255 * (127 + (n)) - ((x) & ~0UL / 255 * 127) & ~(x) & \
	  ((x) & ~0UL / 255 * 127) + ~0UL / 255 * (127 - (m))) &       \
	 ~0UL / 255 * 128)

/* Count how many bytes x has that are between m and n */
#define WORD_COUNT_BETWEEN_M_N(x, m, n) \
	(WORD_HAS_BETWEEN_M_N(x, m, n) / 128 % 255)

#endif
