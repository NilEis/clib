#include "clib_math.h"

#define CLIB_MAGIC_DEBRUIJN_NUMBER UINT32_C(0x077CB531)
#ifndef USE_BUILTINS
#define USE_BUILTINS 1
#endif

#if !(defined(__GNUC__) && USE_BUILTINS)
/**
 * Lookup table for count trailing zeros
 * @see https://graphics.stanford.edu/~seander/bithacks.html#ZerosOnRightMultLookup
 */
static const uint32_t ctz_lut[] = {0, 1, 28, 2, 29, 14, 24, 3, 30, 22, 20, 15, 25, 17, 4, 8,
                                   31, 27, 13, 23, 21, 19, 16, 7, 26, 12, 18, 6, 11, 5, 10, 9};

static const uint32_t clz_lut[] = {31, 22, 30, 21, 18, 10, 29, 2, 20, 17, 15, 13, 9, 6, 28, 1,
                                   23, 19, 11, 3, 16, 14, 7, 24, 12, 4, 8, 25, 5, 26, 27, 0};
#endif

#ifndef CLIB_MATH_INLINE
double clib_math_lerp(double x, double a, double b)
{
    return a + x * (b - a);
}

int32_t clib_math_abs(int32_t x)
{
    return x < 0 ? -x : x;
}

#endif

uint32_t clib_math_ctz(uint32_t v)
{
#if defined(__GNUC__) && USE_BUILTINS
    return (uint32_t)__builtin_ctzg(v);
#else
    return ctz_lut[((uint32_t)((v & -v) * CLIB_MAGIC_DEBRUIJN_NUMBER)) >> 27];
#endif
}

/**
 * @todo fix clz
 */
uint32_t clib_math_clz(uint32_t v)
{
#if defined(__GNUC__) && USE_BUILTINS
    return (uint32_t)__builtin_clzg(v);
#else
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
    return clz_lut[(uint32_t)(v * 0x07C4ACDDU) >> 27];
#endif
}

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
