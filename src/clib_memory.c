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