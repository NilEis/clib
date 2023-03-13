#include "clib.h"

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

int clib_string_dist_damerau_lev(const char *a, const char *b)
{
    const size_t a_s = clib_string_length(a);
    const size_t b_s = clib_string_length(b);
    const size_t y_w = a_s + 2;
    const size_t x_w = b_s + 2;
#define XY_TO_I(x, y) (((int)(x) + 1) + ((int)(y) + 1) * (int)x_w)
#define MIN(a, b) ((a) < (b) ? (a) : (b))
    int da[CHAR_MAX] = {0};
    int *d = (int *)calloc(y_w * x_w, sizeof(int));
    int max_d = (int)a_s + (int)b_s;
    d[XY_TO_I(-1, -1)] = max_d;
    for (int i = 0; i <= (int)a_s; i++)
    {
        d[XY_TO_I(i, -1)] = max_d;
        d[XY_TO_I(i, 0)] = i;
    }
    for (int i = 0; i <= (int)b_s; i++)
    {
        d[XY_TO_I(-1, i)] = max_d;
        d[XY_TO_I(0, i)] = i;
    }
    for (int i = 1; i <= (int)a_s; i++)
    {
        int db = 0;
        for (int j = 1; j <= (int)b_s; j++)
        {
            int k = da[(int)b[j - 1]];
            int l = db;
            int cost;
            if (a[i - 1] == b[j - 1])
            {
                cost = 0;
                db = j;
            }
            else
            {
                cost = 1;
            }
            int p1 = d[XY_TO_I(i - 1, j - 1)] + cost;
            int p2 = d[XY_TO_I(i, j - 1)] + 1;
            int p3 = d[XY_TO_I(i - 1, j)] + 1;
            int p4 = d[XY_TO_I(k - 1, l - 1)] + (i - k - 1) + 1 + (j - l - 1);
            d[XY_TO_I(i, j)] = MIN(p1, MIN(p2, MIN(p3, p4)));
        }
        da[(int)a[i - 1]] = i;
    }
    return d[XY_TO_I(a_s, b_s)];
#undef MIN
#undef XY_TO_I
}