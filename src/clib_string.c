#include "clib_string.h"
#include "clib_error.h"
#include <stdlib.h>
#include <limits.h>

const char *clib_string_module_name(void)
{
    return "clib_string";
}

#ifdef CLIB_INCLUDE_STRING

struct __clib_string_builder
{
    size_t length; /* length without '\0' */
    size_t buf_size;
    char *buf;
};

static int __clib_string_dist_lev_rec(const char *a, const char *b, size_t as, size_t bs);

clib_string_builder_t *clib_string_builder_create(size_t initial_size)
{
    void *memset(void *str, int c, size_t n);
    clib_string_builder_t *ret = NULL;
    initial_size = initial_size != 0 ? initial_size : 8;
    ret = calloc(1, sizeof(clib_string_builder_t));
    if (ret == NULL)
    {
        clib_errno = CLIB_ERRNO_ALLOCATION_ZEROED_ERROR;
        return NULL;
    }
    ret->buf = calloc(initial_size, sizeof(char));
    memset(ret->buf, '\0', initial_size * sizeof(char));
    if (ret->buf == NULL)
    {
        free(ret);
        clib_errno = CLIB_ERRNO_ALLOCATION_ZEROED_ERROR;
        return NULL;
    }
    ret->buf_size = initial_size;
    ret->length = 0;
    return ret;
}

clib_string_builder_t *clib_string_builder_append(clib_string_builder_t *builder, const char *str)
{
    size_t i = 0;
    for (i = 0; str[i] != '\0'; i++)
    {
        size_t builder_index = builder->length;
        if (builder->buf_size <= builder_index + 1)
        {
            size_t new_size = builder->buf_size <= 1 ? 4 : builder->buf_size * 2;
            char *new_buf = realloc(builder->buf, new_size);
            if (new_buf == NULL)
            {
                clib_errno = CLIB_ERRNO_REALLOCATION_ERROR;
                return NULL;
            }
            builder->buf = new_buf;
            builder->buf_size = new_size;
        }
        builder->buf[builder_index] = str[i];
        builder->buf[builder_index + 1] = '\0';
        builder->length++;
    }
    return builder;
}

char *clib_string_builder_get_string(clib_string_builder_t *builder)
{
    char *ret = calloc(builder->length + 1, sizeof(char));
    clib_string_copy(ret, builder->buf, builder->length + 1);
    return ret;
}

void clib_string_builder_free(clib_string_builder_t *builder)
{
    free(builder->buf);
    free(builder);
}

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
    size_t i = 0;
    for (i = 0; i < size && src[i] != '\0'; i++)
    {
        count++;
        dest[i] = src[i];
    }
    return count;
}

char *clib_string_duplicate(const char *src)
{
    size_t len = clib_string_length(src);
    char *ret = calloc(len + 1, sizeof(char));
    if(ret == NULL)
    {
        clib_errno = CLIB_ERRNO_ALLOCATION_ZEROED_ERROR;
        return NULL;
    }
    (void)clib_string_copy(ret, src, len + 1);
    return ret;
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

char *clib_string_from_int(char *dest, intmax_t i, clib_radix_t radix)
{
    static const char *const num_to_char = "0123456789ABCDEF";
    int c = 0;
    if (radix > CLIB_RADIX_HEX)
    {
        clib_errno = CLIB_ERRNO_STRING_INVALID_BASE;
        return NULL;
    }
    do
    {
        intmax_t res = i % radix;
        dest[c] = num_to_char[res];
        i /= radix;
        c++;
        dest[c] = '\0';
    } while (i != 0);
    clib_string_reverse_in_place(dest, (size_t)c);
    return dest;
}

char *clib_string_reverse(const char *restrict src, char *restrict dest, size_t length)
{
    size_t i = 0;
    for (i = 0; i < length; i++)
    {
        dest[i] = src[length - 1 - i];
    }
    return dest;
}

char *clib_string_reverse_in_place(char *src, size_t length)
{
    size_t i = 0;
    for (i = 0; i < length / 2; i++)
    {
        char t = src[i];
        src[i] = src[length - 1 - i];
        src[length - 1 - i] = t;
    }
    return src;
}
#endif /* CLIB_INCLUDE_STRING */
