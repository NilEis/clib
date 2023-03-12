#include "test_clib_string.h"
#include "clib.h"
#include <string.h>

static void test_clib_string_length(void)
{
    const char *str = "hello world";
    size_t len = clib_string_length(str);
    printf("Testing %s:\n\tString: '%s', Length: %zu\n", __func__, str, len);
    if (len != strlen(str))
    {
        printf("Error: clib_string_length() returned incorrect length!\n");
    }
    else
    {
        printf("PASSED\n");
    }
}

static void test_clib_string_copy(void)
{
    const char *src = "hello world";
    char dest[20] = {0};
    size_t size = clib_string_copy(dest, src, 5);
    printf("Testing %s:\n\tSource: '%s', Dest: '%s', Size: %zu\n", __func__, src, dest, size);
    if (strcmp(dest, "hello") != 0 || size != 5)
    {
        printf("Error: clib_string_copy() did not copy the correct number of characters!\n");
    }
    else
    {
        printf("PASSED\n");
    }
}

static void test_clib_string_replace_char(void)
{
    char str[] = "hello world";
    int replaced = clib_string_replace_char(str, 'l', 'x');
    printf("Testing %s:\n\tOriginal: '%s', Replaced: '%s', Count: %d\n", __func__, "hello world", str, replaced);
    if (strcmp(str, "hexlo world") != 0 || replaced != 1)
    {
        printf("Error: clib_string_replace_char() did not replace the correct characters!\n");
    }
    else
    {
        printf("PASSED\n");
    }
}

static void test_clib_string_replace_char_all(void)
{
    char str[] = "hello world";
    size_t replaced = clib_string_replace_char_all(str, 'l', 'x');
    printf("Testing %s:\n\tOriginal: '%s', Replaced: '%s', Count: %zu\n", __func__, "hello world", str, replaced);
    if (strcmp(str, "hexxo worxd") != 0 || replaced != 3)
    {
        printf("Error: clib_string_replace_char_all() did not replace the correct characters!\n");
    }
    else
    {
        printf("PASSED\n");
    }
}

static void test_clib_string_dist_lev(void)
{
    const char *a = "kitten";
    const char *b = "sitting";
    int dist = clib_string_dist_lev(a, b);
    printf("Testing %s:\n\tString a: '%s', String b: '%s', Distance: %d\n", __func__, a, b, dist);
    if (dist != 3)
    {
        printf("Error: clib_string_dist_lev() returned incorrect distance!\n");
    }
    else
    {
        printf("PASSED\n");
    }
}

int test_clib_string_main(void)
{
    printf("=======Testing string functions=======\n");
    test_clib_string_length();
    test_clib_string_copy();
    test_clib_string_replace_char();
    test_clib_string_replace_char_all();
    test_clib_string_dist_lev();
    return 0;
}