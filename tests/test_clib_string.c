#ifndef __BASE_FILE__
#define __BASE_FILE__ __FILE__
#endif
#include "cheat.h"
#include "test_clib_string.h"
#include "clib.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
#if defined(_WIN32) || defined(WIN32)
#include <windows.h>

CHEAT_DECLARE(
    
    void init_console()
    {
        static int set = 0;
        if(set == 1)
        {
            return;
        }
        set = 1;
        HANDLE hOut = CreateFile("CONOUT$", GENERIC_READ|GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
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

CHEAT_SET_UP(init_console();)
#endif

CHEAT_TEST(test_clib_string_length,
           const char *const str = "hello world";
           const size_t len = clib_string_length(str);
           printf("- Testing %s\n", __func__);
           cheat_assert(len == strlen(str));
)

CHEAT_TEST(test_clib_string_copy,
           const char *const src = "hello world";
           char dest[20] = {0};
           const size_t size = clib_string_copy(dest, src, 5);
           printf("- Testing %s\n", __func__);
           cheat_assert(strcmp(dest, "hello") == 0 && size == 5);
)

CHEAT_TEST(test_clib_string_replace_char,
           char str[] = "hello world";
           const int replaced = clib_string_replace_char(str, 'l', 'x');
           printf("- Testing %s\n", __func__);
           cheat_assert(strcmp(str, "hexlo world") == 0 && replaced == 1);
)

CHEAT_TEST(test_clib_string_replace_char_all,
           char str[] = "hello world";
           const size_t replaced = clib_string_replace_char_all(str, 'l', 'x');
           printf("- Testing %s\n", __func__);
           cheat_assert(strcmp(str, "hexxo worxd") == 0 && replaced == 3);
)

CHEAT_TEST(test_clib_string_dist_lev,
           const char *const a = "kitten";
           const char *const b = "sitting";
           const int dist = clib_string_dist_lev(a, b);
           printf("- Testing %s\n", __func__);
           cheat_assert(dist == 3);
)

CHEAT_TEST(clib_string_dist_damerau_lev,
           const char *const a = "CA";
           const char *const b = "ABC";
           const int dist = clib_string_dist_damerau_lev(a, b);
           printf("- Testing %s\n", __func__);
           cheat_assert(dist == 2);
)