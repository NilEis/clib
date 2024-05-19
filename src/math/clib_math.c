#ifdef CLIB_MATH_INLINE
#undef CLIB_MATH_INLINE
#define CLIB_MATH_INLINE_UNDEF
#endif
#include "clib_math.h"
#ifdef CLIB_MATH_INLINE_UNDEF
#undef CLIB_MATH_INLINE_UNDEF
#define CLIB_MATH_INLINE
#endif

const char *clib_math_module_name (void) { return "clib_math"; }

#define CLIB_MAGIC_DEBRUIJN_NUMBER UINT32_C (0x077CB531)
#define CLIB_MAGIC_CLZ_NUMBER      UINT32_C (0x07C4ACDD)

/**
 * Lookup table for count trailing zeros
 * @see
 * https://graphics.stanford.edu/~seander/bithacks.html#ZerosOnRightMultLookup
 */
static const uint_least32_t ctz_lut[] = { 0,
    1,
    28,
    2,
    29,
    14,
    24,
    3,
    30,
    22,
    20,
    15,
    25,
    17,
    4,
    8,
    31,
    27,
    13,
    23,
    21,
    19,
    16,
    7,
    26,
    12,
    18,
    6,
    11,
    5,
    10,
    9 };

static const uint_least32_t clz_lut[] = { 31,
    22,
    30,
    21,
    18,
    10,
    29,
    2,
    20,
    17,
    15,
    13,
    9,
    6,
    28,
    1,
    23,
    19,
    11,
    3,
    16,
    14,
    7,
    24,
    12,
    4,
    8,
    25,
    5,
    26,
    27,
    0 };

double clib_math_lerp (
    const double percent, const double start, const double end)
{
    return start + percent * (end - start);
}

int32_t clib_math_abs (const int32_t value)
{
    return value < 0 ? -value : value;
}

uint_least32_t clib_math_ctz (uint_least32_t value)
{
    return ctz_lut[((uint_least32_t)((value & -value)
                                     * CLIB_MAGIC_DEBRUIJN_NUMBER))
                   >> UINT32_C (27)];
}

uint_least32_t clib_math_clz (uint_least32_t value)
{
    value |= value >> UINT32_C (1);
    value |= value >> UINT32_C (2);
    value |= value >> UINT32_C (4);
    value |= value >> UINT32_C (8);
    value |= value >> UINT32_C (16);
    return clz_lut[(uint_least32_t)(value * CLIB_MAGIC_CLZ_NUMBER)
                   >> UINT32_C (27)];
}

uint_least32_t clib_math_ffs (uint_least32_t value)
{
    if (value == 0)
    {
        return 0;
    }

    return clib_math_ctz (value) + 1;
}

int32_t clib_math_gcd (const int32_t int_a, const int32_t int_b)
{
    uint_least32_t ctz_res = 0;
    uint_least32_t a_u = 0;
    uint_least32_t b_u = 0;
    if (int_a == 0 || int_b == 0)
    {
        return int_a == 0 ? int_b : int_a;
    }

    a_u = (uint_least32_t)clib_math_abs (int_a);
    b_u = (uint_least32_t)clib_math_abs (int_b);

    ctz_res = clib_math_ctz (a_u | b_u);

    a_u >>= clib_math_ctz (a_u);

    do
    {
        b_u >>= clib_math_ctz (b_u);
        if (a_u > b_u)
        {
            uint_least32_t tmp = a_u;
            a_u = b_u;
            b_u = tmp;
        }
        b_u = b_u - a_u;
    }
    while (b_u != 0);
    return (int32_t)(a_u << ctz_res);
}

unsigned int clib_math_int_width (intmax_t value, const clib_radix_t radix)
{
    unsigned int length = !value;
    while (value)
    {
        length++;
        value /= radix;
    }
    return length;
}
