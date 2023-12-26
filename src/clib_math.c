#include "clib_math.h"

unsigned int clib_math_int_width(intmax_t value, uint8_t base)
{
    unsigned int l = !value;
    while (value)
    {
        l++;
        value /= base;
    }
    return l;
}