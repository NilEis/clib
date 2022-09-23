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

int clib_replace_char(char *src, char a, char b)
{
    while (*src != '\0')
    {
        if (*src == a)
        {
            *src = b;
            return 1;
        }
        src++;
    }
    return 0;
}

size_t clib_replace_char_all(char *src, char a, char b)
{
    size_t count = 0;
    while (*src != '\0')
    {
        if (*src == a)
        {
            *src = b;
            count++;
        }
        src++;
    }
    return count;
}