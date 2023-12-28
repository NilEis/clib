#include "clib_math.h"

#ifndef CLIB_MATH_INLINE
double clib_math_lerp(double x, double a, double b)
{
    return a + x * (b - a);
}
#endif

unsigned int clib_math_int_width(intmax_t value, clib_radix_t radix)
{
    unsigned int l = !value;
    while (value)
    {
        l++;
        value /= radix;
    }
    return l;
}
