#include "clib_memory.h"
#include <stdint.h>

void *clib_memory_copy(const void *restrict src, void *restrict dest, size_t size)
{
    size_t i = 0;
    const uint8_t *src_b = src;
    uint8_t *dest_b = dest;
    for (i = 0; i < size; i++)
    {
        dest_b[i] = src_b[i];
    }
    return dest;
}

void *clib_memory_set_u8(void *dest, uint8_t value, size_t size)
{
    size_t i = 0;
    uint8_t *dest_p = dest;
    for (i = 0; i < size; i++)
    {
        dest_p[i] = value;
    }
    return dest;
}

void *clib_memory_set_u16(void *dest, uint16_t value, size_t size)
{
    size_t i = 0;
    uint16_t *dest_p = dest;
    for (i = 0; i < size; i++)
    {
        dest_p[i] = value;
    }
    return dest;
}

void *clib_memory_set_u32(void *dest, uint32_t value, size_t size)
{
    size_t i = 0;
    uint32_t *dest_p = dest;
    for (i = 0; i < size; i++)
    {
        dest_p[i] = value;
    }
    return dest;
}

void *clib_memory_set_u64(void *dest, uint64_t value, size_t size)
{
    size_t i = 0;
    uint64_t *dest_p = dest;
    for (i = 0; i < size; i++)
    {
        dest_p[i] = value;
    }
    return dest;
}
