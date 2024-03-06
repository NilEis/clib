/** @file
 * @brief functions for working with numbers and math in general
 */
#ifndef CLIB_MATH_H
#define CLIB_MATH_H

#ifdef __cplusplus 
extern "C" {
#endif

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
#ifdef CLIB_INCLUDE_MATH

#ifdef CLIB_MATH_INLINE
#define CLIB_MATH_INLINED 1
#define CLIB_INTERNAL_MATH_DEF_FUNCTION(dec, def) \
    inline dec                             \
        def
#else
#define CLIB_MATH_INLINED 0
#define CLIB_INTERNAL_MATH_DEF_FUNCTION(dec, def) dec;
#endif

/**
 * @brief returns the point x between a and b (lerp(0.5, 1, 3) = 2)
 *
 * @param percent the percentage of the way between a and b
 * @param start the start point
 * @param end the end point
 * @return double
 */
CLIB_INTERNAL_MATH_DEF_FUNCTION(double clib_math_lerp(double percent, double start, double end),
                         {
                             return start + percent * (end - start);
                         })

/**
 * @brief returns the absolute value of x
 *
 * @param x x
 * @return int32_t
 */
CLIB_INTERNAL_MATH_DEF_FUNCTION(int32_t clib_math_abs(int32_t value),
                         {
                             return value < 0 ? -value : value;
                         })

/**
 * @brief returns the number of trailing zeros of an unsigned int
 * 
 * @param value 
 * @return uint32_t 
 */
uint32_t clib_math_ctz(uint32_t value);

/**
 * @brief returns the number of leading zeros of an unsigned int
 * 
 * @param value 
 * @return uint32_t 
 */
uint32_t clib_math_clz(uint32_t value);

/**
 * @brief returns the index of the first bit set in an unsigned int
 * @param value
 * @return uint32_t the index of the first bit set
 * 
*/
uint32_t clib_math_ffs(uint32_t value);

/**
 * @brief returns the greatest common divisor of a and b
 * @param int_a
 * @param int_b
 * @return int32_t the greatest common divisor
*/
int32_t clib_math_gcd(int32_t int_a, int32_t int_b);

/**
 * @brief returns the width of the integer as a string
 *
 * @param value the value
 * @param radix the base of the number
 * @return unsigned int example: base10 -1 = 1, base10 15 = 2, hex 15 = 1
 */
unsigned int clib_math_int_width(intmax_t value, clib_radix_t radix);

#endif /* CLIB_INCLUDE_MATH */

#ifdef __cplusplus 
}
#endif

#endif /* CLIB_MATH_H */
