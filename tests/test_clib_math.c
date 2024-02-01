#ifndef __BASE_FILE__
#define __BASE_FILE__ __FILE__
#endif
#ifndef CATCH_CONFIG_MAIN
#define CATCH_CONFIG_MAIN
#endif

#ifndef __cplusplus
#include "cheat.h"
#include "cheats.h"
#define test(name, name2, func) CHEAT_TEST(name, func)
#else
#include "catch.hpp"
#define test(name, name2, func) TEST_CASE(name2, "["##name"]") { func }
#endif

#include "clib.h"
#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#ifndef CLIB_MATH_INLINED_EXPECTED
#define CLIB_MATH_INLINED_EXPECTED 0
#endif

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

#define TEST_EPSILON 0.0000001

test(clib_math_inlined,"[is_inlined]",
           init_console();
           printf("- Testing %s\n", __func__);
           cheat_assert(CLIB_MATH_INLINED == CLIB_MATH_INLINED_EXPECTED);)

test(clib_math_int_width,"[clib_math_int_width]",
           init_console();
           printf("- Testing %s\n", __func__);
           cheat_assert(5 == clib_math_int_width(16, CLIB_RADIX_BIN));
           cheat_assert(2 == clib_math_int_width(9, CLIB_RADIX_OCT));
           cheat_assert(5 == clib_math_int_width(54321, CLIB_RADIX_DEC));
           cheat_assert(6 == clib_math_int_width(0xabcdef, CLIB_RADIX_HEX));)

test(clib_math_lerp,"[clib_math_lerp]",
           init_console();
           printf("- Testing %s\n", __func__);
           cheat_assert_double(clib_math_lerp(0.5, 1.5, 2.0), 1.75, TEST_EPSILON);
           cheat_assert_double(clib_math_lerp(0.5, -10, 30), 10, TEST_EPSILON);
           cheat_assert_double(clib_math_lerp(0.5, -10, 10), 0, TEST_EPSILON);)

test(
    clib_math_ctz,"[clib_math_ctz]",
    init_console();
    printf("- Testing %s\n", __func__);
    cheat_assert(clib_math_ctz(0) == 0);
    for (int i = 0; i < 32; i++) {
        cheat_assert(clib_math_ctz((uint32_t)pow(2, i)) == i);
    })

test(
    clib_math_clz,"[clib_math_clz]",
    init_console();
    printf("- Testing %s\n", __func__);
    cheat_assert(clib_math_clz(0) == 31);
    for (int i = 0; i < 32; i++) {
        cheat_assert(clib_math_clz((uint32_t)pow(2, i)) == (31 - i));
    })

test(
    clib_math_ffs,"[clib_math_ffs]",
    init_console();
    printf("- Testing %s\n", __func__);
    cheat_assert(clib_math_ffs(0) == 0);
    for (int i = 0; i < 32; i++) {
        cheat_assert(clib_math_ffs((uint32_t)pow(2, i)) == i + 1);
    })

test(
    clib_math_gcd,"[clib_math_gcd]",
    init_console();
    printf("- Testing %s\n", __func__);
    cheat_assert(clib_math_gcd(0, 1) == 1);
    cheat_assert(clib_math_gcd(-15, 5) == 5);
    cheat_assert(clib_math_gcd(-15, -5) == 5);
    cheat_assert(clib_math_gcd(15, 5) == 5);
    cheat_assert(clib_math_gcd(9, 15) == 3);
    cheat_assert(clib_math_gcd(10, 20) == 10);
    cheat_assert(clib_math_gcd(33, 22) == 11);)