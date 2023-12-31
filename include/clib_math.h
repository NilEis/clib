/** @file
 * @brief functions for working with numbers and math in general
 */
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
 * @brief returns the point x between a and b (lerp(0.5, 1, 3) = 2)
 *
 * @param x the percentage of the way between a and b
 * @param a the start point
 * @param b the end point
 * @return double
 */
#ifdef CLIB_MATH_INLINE
inline double clib_math_lerp(double x, double a, double b)
{
    return a + x * (b - a);
}
#else
double clib_math_lerp(double x, double a, double b);
#endif

/**
 * @brief returns the width of the integer as a string
 *
 * @param value the value
 * @param radix the base of the number
 * @return unsigned int example: base10 -1 = 1, base10 15 = 2, hex 15 = 1
 */
unsigned int clib_math_int_width(intmax_t value, clib_radix_t radix);

#endif /* CLIB_MATH_H */
