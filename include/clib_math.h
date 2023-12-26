#ifndef CLIB_MATH_H
#define CLIB_MATH_H

#include "clib_c90_support.h"
#include <stdint.h>

/**
 * @brief returns the width of the integer as a string
 * 
 * @param value the value
 * @param base the base of the number
 * @return unsigned int example: base10 -1 = 1, base10 15 = 2, hex 15 = 1
 */
unsigned int clib_math_int_width(intmax_t value, uint8_t base);

#endif /* CLIB_MATH_H */
