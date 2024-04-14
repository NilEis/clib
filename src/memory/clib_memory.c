#include "clib_memory.h"

const char *clib_memory_module_name (void) { return "clib_memory"; }

void *clib_memory_copy (
    const void *restrict src, void *restrict dest, const size_t size)
{
    size_t index = 0;
    const uint8_t *src_b = src;
    uint8_t *dest_b = dest;
    for (index = 0; index < size; index++)
    {
        dest_b[index] = src_b[index];
    }
    return dest;
}

void *clib_memory_set_u8 (void *dest, const uint8_t value, const size_t size)
{
    size_t index = 0;
    uint8_t *dest_p = dest;
    for (index = 0; index < size; index++)
    {
        dest_p[index] = value;
    }
    return dest;
}

void *clib_memory_set_u16 (void *dest, const uint16_t value, const size_t size)
{
    size_t index = 0;
    uint16_t *dest_p = dest;
    for (index = 0; index < size; index++)
    {
        dest_p[index] = value;
    }
    return dest;
}

void *clib_memory_set_u32 (void *dest, const uint32_t value, const size_t size)
{
    size_t index = 0;
    uint32_t *dest_p = dest;
    for (index = 0; index < size; index++)
    {
        dest_p[index] = value;
    }
    return dest;
}

void *clib_memory_set_u64 (void *dest, const uint64_t value, const size_t size)
{
    size_t index = 0;
    uint64_t *dest_p = dest;
    for (index = 0; index < size; index++)
    {
        dest_p[index] = value;
    }
    return dest;
}
