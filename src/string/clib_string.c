#include "clib_string.h"
#include "clib_array.h"
#include "clib_error.h"
#include <stdlib.h>

const char *clib_string_module_name (void) { return "clib_string"; }

static int clib_string_dist_lev_rec (const char *string_a,
    const char *string_b,
    size_t string_a_len,
    size_t string_b_len);

clib_string_builder_t *clib_string_builder_create (const size_t initial_size)
{
    return clib_array_create (sizeof (char), initial_size);
}

clib_string_builder_t *clib_string_builder_append (
    clib_string_builder_t *builder, const char *str)
{
    size_t index = 0;
    for (index = 0; str[index] != '\0'; index++)
    {
        (void)clib_string_builder_append_char (builder, str[index]);
    }
    return builder;
}

clib_string_builder_t *clib_string_builder_append_char (
    clib_string_builder_t *builder, const char value)
{
    clib_array_push (builder, &value);
    return builder;
}

char *clib_string_builder_get_string (const clib_string_builder_t *builder)
{
    char *res = clib_array_get_array (builder);
    char *realloc_res = NULL;
    const size_t len = clib_array_length (builder);
    realloc_res = realloc (res, len + 1);
    if (realloc_res == NULL)
    {
        clib_errno = CLIB_ERRNO_REALLOCATION_ERROR;
        free (res);
        return NULL;
    }
    res = realloc_res;
    res[len] = '\0';
    return res;
}

void clib_string_builder_free (clib_string_builder_t *builder)
{
    clib_array_free (builder);
}

int clib_string_cmp (const char *str_a, const char *str_b)
{
    int index = 0;
    while (str_a[index] == str_b[index] && str_a[index] != '\0'
           && str_b[index] != '\0')
    {
        index++;
    }
    return str_a[index] - str_b[index];
}

size_t clib_string_length (const char *str)
{
    size_t index = 0;
    while (str[index] != '\0')
    {
        index++;
    }
    return index;
}

size_t clib_string_copy (
    char *restrict dest, const char *restrict src, const size_t size)
{
    size_t count = 0;
    size_t index = 0;
    for (index = 0; index < size; index++)
    {
        count++;
        dest[index] = src[index];
    }
    return count;
}

char *clib_string_duplicate (const char *src)
{
    const size_t len = clib_string_length (src);
    char *ret = calloc (len + 1, sizeof (char));
    if (ret == NULL)
    {
        clib_errno = CLIB_ERRNO_ALLOCATION_ZEROED_ERROR;
        return NULL;
    }
    (void)clib_string_copy (ret, src, len + 1);
    return ret;
}

int clib_string_replace_char (char *src, const char char_a, const char char_b)
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
        if (*src == char_a)
        {
            *src = char_b;
            return 1;
        }
        src++;
    }
    src_p = src;
    return 0;
}

size_t clib_string_replace_char_all (
    char *src, const char char_a, const char char_b)
{
    size_t count = 0;
    while (*src != '\0')
    {
        if (*src == char_a)
        {
            *src = char_b;
            count++;
        }
        src++;
    }
    return count;
}

int clib_string_dist_lev (const char *string_a, const char *string_b)
{
    return clib_string_dist_lev_rec (string_a,
        string_b,
        clib_string_length (string_a),
        clib_string_length (string_b));
}

static int clib_string_dist_lev_rec (const char *string_a,
    const char *string_b,
    const size_t string_a_len,
    const size_t string_b_len)
{
    int tab = 0;
    int atb = 0;
    int tatb = 0;
    if (string_a_len == 0)
    {
        return (int)string_b_len;
    }
    if (string_b_len == 0)
    {
        return (int)string_a_len;
    }
    if (string_a[0] == string_b[0])
    {
        return clib_string_dist_lev_rec (
            string_a + 1, string_b + 1, string_a_len - 1, string_b_len - 1);
    }

    tab = clib_string_dist_lev_rec (
        string_a + 1, string_b, string_a_len - 1, string_b_len);
    atb = clib_string_dist_lev_rec (
        string_a, string_b + 1, string_a_len, string_b_len - 1);
    tatb = clib_string_dist_lev_rec (
        string_a + 1, string_b + 1, string_a_len - 1, string_b_len - 1);
    return 1
         + (tab < atb ? (tab < tatb ? tab : tatb) : (atb < tatb ? atb : tatb));
}

char *clib_string_from_int (
    char *dest, intmax_t value, const clib_radix_t radix)
{
    static const char *const num_to_char = "0123456789ABCDEF";
    int dest_index = 0;
    if (radix > CLIB_RADIX_HEX)
    {
        clib_errno = CLIB_ERRNO_STRING_INVALID_BASE;
        return NULL;
    }
    do
    {
        const intmax_t res = value % radix;
        dest[dest_index] = num_to_char[res];
        value /= radix;
        dest_index++;
        dest[dest_index] = '\0';
    }
    while (value != 0);
    clib_string_reverse_in_place (dest, (size_t)dest_index);
    return dest;
}

char *clib_string_reverse (
    const char *restrict src, char *restrict dest, const size_t length)
{
    size_t index = 0;
    for (index = 0; index < length; index++)
    {
        dest[index] = src[length - 1 - index];
    }
    return dest;
}

char *clib_string_reverse_in_place (char *src, const size_t length)
{
    size_t index = 0;
    for (index = 0; index < length / 2; index++)
    {
        const char tmp = src[index];
        src[index] = src[length - 1 - index];
        src[length - 1 - index] = tmp;
    }
    return src;
}
