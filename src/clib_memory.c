#include "clib_memory.h"

const char *clib_memory_module_name(void)
{
    return "clib_memory";
}

void *clib_memory_copy(const void *restrict src, void *restrict dest, size_t size)
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

void *clib_memory_set_u8(void *dest, uint8_t value, size_t size)
{
    size_t index = 0;
    uint8_t *dest_p = dest;
    for (index = 0; index < size; index++)
    {
        dest_p[index] = value;
    }
    return dest;
}

void *clib_memory_set_u16(void *dest, uint16_t value, size_t size)
{
    size_t index = 0;
    uint16_t *dest_p = dest;
    for (index = 0; index < size; index++)
    {
        dest_p[index] = value;
    }
    return dest;
}

void *clib_memory_set_u32(void *dest, uint32_t value, size_t size)
{
    size_t index = 0;
    uint32_t *dest_p = dest;
    for (index = 0; index < size; index++)
    {
        dest_p[index] = value;
    }
    return dest;
}

void *clib_memory_set_u64(void *dest, uint64_t value, size_t size)
{
    size_t index = 0;
    uint64_t *dest_p = dest;
    for (index = 0; index < size; index++)
    {
        dest_p[index] = value;
    }
    return dest;
}
