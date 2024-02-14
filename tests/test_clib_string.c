#ifndef __cplusplus

#ifndef __BASE_FILE__
#define __BASE_FILE__ __FILE__
#endif

#include "cheat.h"
#include "cheats.h"
#define test(name, name2, func) CHEAT_TEST(name, func)

#else

#ifndef CATCH_CONFIG_MAIN
#define CATCH_CONFIG_MAIN
#endif

#include "catch.hpp"
#define test(name, name2, func) \
    TEST_CASE(name2, "[" #name "]") { func }
#define cheat_assert(v) REQUIRE((v))
#define cheat_assert_double(res, exp, eps) REQUIRE(((res <= (exp + eps)) && (res >= (exp - eps))))
#define cheat_assert_string(res, exp) REQUIRE(strcmp(res, exp) == 0)
#define init_console() ;

#endif

#include "clib.h"
#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#ifndef __cplusplus

#if defined(_WIN32) || defined(WIN32)
#include <windows.h>

CHEAT_DECLARE(

    void init_console() {
        static int set = 0;
        if (set == 1)
        {
            return;
        }
        set = 1;
        HANDLE hOut = CreateFile("CONOUT$", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hOut == INVALID_HANDLE_VALUE)
        {
            char buf[256];
            FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                           NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                           buf, (sizeof(buf) / sizeof(wchar_t)), NULL);
            printf("%d - Error: %s\n", __LINE__, buf);
            return;
        }

        DWORD dwMode = 0;
        if (GetConsoleMode(hOut, &dwMode) == 0)
        {
            char buf[256];
            FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                           NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                           buf, (sizeof(buf) / sizeof(wchar_t)), NULL);
            printf("%d - Error: %s\n", __LINE__, buf);
            return;
        }

        dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        if (SetConsoleMode(hOut, dwMode) == 0)
        {
            char buf[256];
            FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                           NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                           buf, (sizeof(buf) / sizeof(wchar_t)), NULL);
            printf("%d - Error: %s\n", __LINE__, buf);
            return;
        }
    })

#else

CHEAT_DECLARE(

    void init_console() {
        return;
    })

#endif
#endif

test(test_clib_string_builder, "the string builder builds a string",
     clib_string_builder_t *builder = clib_string_builder_create(8);
     char *res = NULL;
     printf("- Testing %s\n", __func__);
     clib_string_builder_append(builder, "Hallo");
     res = clib_string_builder_get_string(builder);
     cheat_assert_string(res, "Hello");
     free(res);
     clib_string_builder_append(builder, ", Welt");
     res = clib_string_builder_get_string(builder);
     cheat_assert_string(res, "Hello, Welt");
     free(res);
     clib_string_builder_free(builder);)

    test(test_clib_string_length,
         "clib_string_length gets the length of a string",
         init_console();
         const char *const str = "hello world";
         const size_t len = clib_string_length(str);
         printf("- Testing %s\n", __func__);
         cheat_assert(len == strlen(str));)

        test(test_clib_string_copy,
             "clib_string_copy copies a string",
             init_console();
             const char *const src = "hello world";
             char dest[20] = {0};
             const size_t size = clib_string_copy(dest, src, 5);
             printf("- Testing %s\n", __func__);
             cheat_assert(strcmp(dest, "hello") == 0 && size == 5);)

            test(test_clib_string_replace_char,
                 "clib_string_replace_char replaces a char in a string",
                 init_console();
                 char str[] = "hello world";
                 const int replaced = clib_string_replace_char(str, 'l', 'x');
                 printf("- Testing %s\n", __func__);
                 cheat_assert(strcmp(str, "hexlo world") == 0 && replaced == 1);)

                test(test_clib_string_replace_char_all,
                     "clib_string_replace_char_all replaces a occurences of char",
                     init_console();
                     char str[] = "hello world";
                     const size_t replaced = clib_string_replace_char_all(str, 'l', 'x');
                     printf("- Testing %s\n", __func__);
                     cheat_assert(strcmp(str, "hexxo worxd") == 0 && replaced == 3);)

                    test(test_clib_string_dist_lev,
                         "clib_string_dist_lev gets the levenshtein distance of to strings",
                         init_console();
                         const char *const a = "kitten";
                         const char *const b = "sitting";
                         const int dist = clib_string_dist_lev(a, b);
                         printf("- Testing %s\n", __func__);
                         cheat_assert(dist == 3);)

                        test(test_clib_string_from_int,
                             "clib_string_from_int stringifys the given number",
                             init_console();
                             const int64_t a = 1243;
                             const int64_t b = 0xDEADCAFE;
                             const char *const expected_a = "1243";
                             const char *const expected_b = "DEADCAFE";
                             char res_a[5] = {0};
                             char res_b[9] = {0};
                             printf("- Testing %s\n", __func__);
                             clib_string_from_int(res_a, a, CLIB_RADIX_DEC);
                             clib_string_from_int(res_b, b, CLIB_RADIX_HEX);
                             cheat_assert_string(res_a, expected_a);
                             cheat_assert_string(res_b, expected_b);)

                            test(test_clib_string_reverse,
                                 "clib_string_reverse reverses a string",
                                 init_console();
                                 const char *const a = "AACHEN";
                                 char res_a[7] = {0};
                                 const char *const expected_a = "NEHCAA";
                                 printf("- Testing %s\n", __func__);
                                 clib_string_reverse(a, res_a, clib_string_length(a));
                                 cheat_assert_string(res_a, expected_a);)

                                test(test_clib_string_reverse_in_place,
                                     "clib_string_reverse_in_place reverses a string in place",
                                     init_console();
                                     char a[] = "AACHEN";
                                     const char *const expected_a = "NEHCAA";
                                     printf("- Testing %s\n", __func__);
                                     clib_string_reverse_in_place(a, clib_string_length(a));
                                     cheat_assert_string(a, expected_a);)