#include "clib_endianess.h"
#include <inttypes.h>
#include <stdint.h>

const char *clib_endianess_module_name (void) { return "clib_endianess"; }

clib_endianess_t clib_endianess_detect (void)
{
    if (sizeof (uint_least8_t) != 1 && sizeof (uint_least32_t) != 4)
    {
        return CLIB_ENDIAN_UNKNOWN;
    }
    union
    {
        uint_least32_t value;
        uint_least8_t array[sizeof (uint_least32_t)];
    } test = { 0 };
    test.array[0] = 0x00;
    test.array[1] = 0x01;
    test.array[2] = 0x02;
    test.array[3] = 0x03;

    switch (test.value)
    {
    case UINT32_C (0x00010203):
        return CLIB_ENDIAN_BIG;
        break;
    case UINT32_C (0x03020100):
        return CLIB_ENDIAN_LITTLE;
        break;
    case UINT32_C (0x02030001):
        return CLIB_ENDIAN_BIG_WORD;
        break;
    case UINT32_C (0x01000302):
        return CLIB_ENDIAN_LITTLE_WORD;
        break;
    default:
        return CLIB_ENDIAN_UNKNOWN;
        break;
    }
}
