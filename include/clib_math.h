#ifndef CLIB_MATH_H
#define CLIB_MATH_H

#include "clib_c90_support.h"
#include <stdint.h>

/**
 * @brief A type for all usable bases for number conversions
 * 
 */
typedef enum
{
    CLIB_RADIX_BIN = 2,
    CLIB_RADIX_OCT = 8,
    CLIB_RADIX_DEC = 10,
    CLIB_RADIX_HEX = 16
} clib_radix_t;

/**
 * @brief returns the width of the integer as a string
 *
 * @param value the value
 * @param radix the base of the number
 * @return unsigned int example: base10 -1 = 1, base10 15 = 2, hex 15 = 1
 */
unsigned int clib_math_int_width(intmax_t value, clib_radix_t radix);

#endif /* CLIB_MATH_H */
