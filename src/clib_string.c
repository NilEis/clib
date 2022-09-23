#include "clib.h"

size_t clib_strcpy(char *restrict dest, const char *restrict src, size_t size)
{
    size_t count = 0;
    for (size_t i = 0; i < size && src[i] != '\0'; i++)
    {
        count++;
        dest[i] = src[i];
    }
    return count;
}