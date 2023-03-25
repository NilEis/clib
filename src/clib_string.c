#include "clib.h"
#include <limits.h>

static int __clib_string_dist_lev_rec(const char *a, const char *b, size_t as, size_t bs);

size_t clib_string_length(const char *str)
{
    const char *end = str;
    while (*end != '\0')
    {
        end++;
    }
    return (size_t)end - (size_t)str;
}

size_t clib_string_copy(char *restrict dest, const char *restrict src, size_t size)
{
    size_t count = 0;
    for (size_t i = 0; i < size && src[i] != '\0'; i++)
    {
        count++;
        dest[i] = src[i];
    }
    return count;
}

int clib_string_replace_char(char *src, char a, char b)
{
    static char *last_src = NULL;
    static char *src_p = NULL;
    if (last_src == src)
    {
        src = src_p;
    }
    else
    {
        last_src = src;
    }
    while (*src != '\0')
    {
        if (*src == a)
        {
            *src = b;
            return 1;
        }
        src++;
    }
    src_p = src;
    return 0;
}

size_t clib_string_replace_char_all(char *src, char a, char b)
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

int clib_string_dist_lev(const char *a, const char *b)
{
    return __clib_string_dist_lev_rec(a, b, clib_string_length(a), clib_string_length(b));
}

static int __clib_string_dist_lev_rec(const char *a, const char *b, size_t as, size_t bs)
{
    if (as == 0)
    {
        return (int)bs;
    }
    else if (bs == 0)
    {
        return (int)as;
    }
    else if (a[0] == b[0])
    {
        return __clib_string_dist_lev_rec(a + 1, b + 1, as - 1, bs - 1);
    }
    else
    {
        int tab = __clib_string_dist_lev_rec(a + 1, b, as - 1, bs);
        int atb = __clib_string_dist_lev_rec(a, b + 1, as, bs - 1);
        int tatb = __clib_string_dist_lev_rec(a + 1, b + 1, as - 1, bs - 1);
        return 1 + (tab < atb ? (tab < tatb ? tab : tatb) : (atb < tatb ? atb : tatb));
    }
}