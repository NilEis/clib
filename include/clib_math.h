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

#ifdef CLIB_MATH_INLINE
#define CLIB_MATH_INLINED 1
#define __CLIB_MATH_DEF_FUNCTION(dec, def) \
    inline dec                             \
        def
#else
#define CLIB_MATH_INLINED 0
#define __CLIB_MATH_DEF_FUNCTION(dec, def) dec;
#endif

/**
 * @brief returns the point x between a and b (lerp(0.5, 1, 3) = 2)
 *
 * @param x the percentage of the way between a and b
 * @param a the start point
 * @param b the end point
 * @return double
 */
__CLIB_MATH_DEF_FUNCTION(double clib_math_lerp(double x, double a, double b),
                         {
                             return a + x * (b - a);
                         })

/**
 * @brief returns the absolute value of x
 *
 * @param x x
 * @return int32_t
 */
__CLIB_MATH_DEF_FUNCTION(int32_t clib_math_abs(int32_t x),
                         {
                             return x < 0 ? -x : x;
                         })

/**
 * @brief returns the number of trailing zeros of an unsigned int
 * 
 * @param v 
 * @return uint32_t 
 */
uint32_t clib_math_ctz(uint32_t v);

/**
 * @brief returns the number of leading zeros of an unsigned int
 * 
 * @param v 
 * @return uint32_t 
 */
uint32_t clib_math_clz(uint32_t v);

/**
 * @brief returns the index of the first bit set in an unsigned int
 * @param v
 * @return uint32_t the index of the first bit set
 * 
*/
uint32_t clib_math_ffs(uint32_t v);

/**
 * @brief returns the greatest common divisor of a and b
 * @param a
 * @param b
 * @return int32_t the greatest common divisor
*/
int32_t clib_math_gcd(int32_t a, int32_t b);

/**
 * @brief returns the width of the integer as a string
 *
 * @param value the value
 * @param radix the base of the number
 * @return unsigned int example: base10 -1 = 1, base10 15 = 2, hex 15 = 1
 */
unsigned int clib_math_int_width(intmax_t value, clib_radix_t radix);

#endif /* CLIB_MATH_H */
