#include "clib_math.h"

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