#pragma once

#ifdef _MSC_VER
#ifndef _STDBOOL_H
#define _STDBOOL_H 1

/**
 * @brief A boolean value
 */
#define bool _Bool

/**
 * @brief True
 */
#define true 1

/**
 * @brief False
 */
#define false 0

#define __bool_true_false_are_defined 1

#endif /* !_STDBOOL_H */
#else
#include_next "stdbool.h"
#endif /* _MSC_VER */
