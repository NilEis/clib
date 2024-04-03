#ifndef __cplusplus

#ifndef __BASE_FILE__
#define __BASE_FILE__ __FILE__
#endif

#include "cheat.h"
#include "cheats.h"
#define test(name, name2, func) CHEAT_TEST (name, func)

#else

#ifndef CATCH_CONFIG_MAIN
#define CATCH_CONFIG_MAIN
#endif

#include "catch.hpp"
#define test(name, name2, func)                                               \
    TEST_CASE (name2, "[" #name "]") { func }
#define cheat_assert(v) REQUIRE ((v))
#define cheat_assert_double(res, exp, eps)                                    \
    REQUIRE (((res <= (exp + eps)) && (res >= (exp - eps))))
#define cheat_assert_string(res, exp) REQUIRE (strcmp (res, exp) == 0)
#define init_console() ;

#endif

#include "clib.h"
#include <assert.h>
#include <stdint.h>
#include <stdio.h>

#ifndef __cplusplus

#if defined(_WIN32) || defined(WIN32)
#include <windows.h>

CHEAT_DECLARE (

    void init_console () {
        static int set = 0;
        if (set == 1)
        {
            return;
        }
        set = 1;
        HANDLE hOut = CreateFile ("CONOUT$",
            GENERIC_READ | GENERIC_WRITE,
            FILE_SHARE_READ | FILE_SHARE_WRITE,
            NULL,
            OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL,
            NULL);
        if (hOut == INVALID_HANDLE_VALUE)
        {
            char buf[256];
            FormatMessageA (
                FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                NULL,
                GetLastError (),
                MAKELANGID (LANG_NEUTRAL, SUBLANG_DEFAULT),
                buf,
                (sizeof (buf) / sizeof (wchar_t)),
                NULL);
            printf ("%d - Error: %s\n", __LINE__, buf);
            return;
        }

        DWORD dwMode = 0;
        if (GetConsoleMode (hOut, &dwMode) == 0)
        {
            char buf[256];
            FormatMessageA (
                FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                NULL,
                GetLastError (),
                MAKELANGID (LANG_NEUTRAL, SUBLANG_DEFAULT),
                buf,
                (sizeof (buf) / sizeof (wchar_t)),
                NULL);
            printf ("%d - Error: %s\n", __LINE__, buf);
            return;
        }

        dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        if (SetConsoleMode (hOut, dwMode) == 0)
        {
            char buf[256];
            FormatMessageA (
                FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                NULL,
                GetLastError (),
                MAKELANGID (LANG_NEUTRAL, SUBLANG_DEFAULT),
                buf,
                (sizeof (buf) / sizeof (wchar_t)),
                NULL);
            printf ("%d - Error: %s\n", __LINE__, buf);
            return;
        }
    })

#else

CHEAT_DECLARE (

    void init_console () { return; })

#endif
#endif

test (
    clib_cpuid,
    "clib_sockets_init initialises the socket system",
    printf ("- Testing %s\n", __func__);
    clib_error_code_t ret = clib_sockets_init ();
    if (ret != CLIB_ERRNO_NO_ERROR) {
        printf ("Error: %s\n", clib_error_get_string (ret));
    };
    cheat_assert (ret == CLIB_ERRNO_NO_ERROR);)

    test (
        clib_cpuid_test_cmov,
        "Tests cmov",
        printf ("- Testing %s\n", __func__);
        cheat_assert (
            (clib_cpuid_supports_cmov () != 0)
            == (__builtin_cpu_supports ("cmov")
                != 0));) test (clib_cpuid_test_mmx,
                               "Tests mmx",
                               printf ("- Testing %s\n", __func__);
                               cheat_assert (
                                   (clib_cpuid_supports_mmx () != 0)
                                   == (__builtin_cpu_supports ("mmx")
                                       != 0));) test (clib_cpuid_test_popcnt,
                                                      "Tests popcnt",
                                                      printf ("- Testing %s\n",
                                                          __func__);
                                                      cheat_assert (
                                                          (clib_cpuid_supports_popcnt ()
                                                              != 0)
                                                          == (__builtin_cpu_supports (
                                                                  "popcnt")
                                                              != 0));)
        test (
            clib_cpuid_test_sse,
            "Tests sse",
            printf ("- Testing %s\n", __func__);
            cheat_assert (
                (clib_cpuid_supports_sse () != 0)
                == (__builtin_cpu_supports ("sse")
                    != 0));) test (clib_cpuid_test_sse2,
                                   "Tests sse2",
                                   printf ("- Testing %s\n", __func__);
                                   cheat_assert (
                                       (clib_cpuid_supports_sse2 () != 0)
                                       == (__builtin_cpu_supports ("sse2")
                                           != 0));) test (clib_cpuid_test_sse3,
                                                          "Tests sse3",
                                                          printf (
                                                              "- Testing %s\n",
                                                              __func__);
                                                          cheat_assert (
                                                              (clib_cpuid_supports_sse3 ()
                                                                  != 0)
                                                              == (__builtin_cpu_supports (
                                                                      "sse3")
                                                                  != 0));)
            test (
                clib_cpuid_test_ssse3,
                "Tests ssse3",
                printf ("- Testing %s\n", __func__);
                cheat_assert (
                    (clib_cpuid_supports_ssse3 () != 0)
                    == (__builtin_cpu_supports ("ssse3")
                        != 0));) test (clib_cpuid_test_sse4_1,
                                       "Tests sse4_1",
                                       printf ("- Testing %s\n", __func__);
                                       cheat_assert (
                                           (clib_cpuid_supports_sse4_1 () != 0)
                                           == (__builtin_cpu_supports (
                                                   "sse4.1")
                                               != 0));)
                test (
                    clib_cpuid_test_sse4_2,
                    "Tests sse4_2",
                    printf ("- Testing %s\n", __func__);
                    cheat_assert (
                        (clib_cpuid_supports_sse4_2 () != 0)
                        == (__builtin_cpu_supports ("sse4.2")
                            != 0));) test (clib_cpuid_test_avx,
                                           "Tests avx",
                                           printf ("- Testing %s\n", __func__);
                                           cheat_assert (
                                               (clib_cpuid_supports_avx ()
                                                   != 0)
                                               == (__builtin_cpu_supports (
                                                       "avx")
                                                   != 0));)
                    test (
                        clib_cpuid_test_avx2,
                        "Tests avx2",
                        printf ("- Testing %s\n", __func__);
                        cheat_assert (
                            (clib_cpuid_supports_avx2 () != 0)
                            == (__builtin_cpu_supports ("avx2")
                                != 0));) test (clib_cpuid_test_sse4a,
                                               "Tests sse4a",
                                               printf (
                                                   "- Testing %s\n", __func__);
                                               cheat_assert (
                                                   (clib_cpuid_supports_sse4a ()
                                                       != 0)
                                                   == (__builtin_cpu_supports (
                                                           "sse4a")
                                                       != 0));)
                        test (
                            clib_cpuid_test_fma,
                            "Tests fma",
                            printf ("- Testing %s\n", __func__);
                            cheat_assert (
                                (clib_cpuid_supports_fma () != 0)
                                == (__builtin_cpu_supports ("fma")
                                    != 0));) test (clib_cpuid_test_fma4,
                                                   "Tests fma4",
                                                   printf ("- Testing %s\n",
                                                       __func__);
                                                   cheat_assert (
                                                       (clib_cpuid_supports_fma4 ()
                                                           != 0)
                                                       == (__builtin_cpu_supports (
                                                               "fma4")
                                                           != 0));)
                            test (
                                clib_cpuid_test_xop,
                                "Tests xop",
                                printf ("- Testing %s\n", __func__);
                                cheat_assert (
                                    (clib_cpuid_supports_xop () != 0)
                                    == (__builtin_cpu_supports ("xop")
                                        != 0));) test (clib_cpuid_test_avx512f,
                                                       "Tests avx512f",
                                                       printf (
                                                           "- Testing %s\n",
                                                           __func__);
                                                       cheat_assert (
                                                           (clib_cpuid_supports_avx512f ()
                                                               != 0)
                                                           == (__builtin_cpu_supports ("avx512f")
                                                               != 0));)
                                test (
                                    clib_cpuid_test_bmi,
                                    "Tests bmi",
                                    printf ("- Testing %s\n", __func__);
                                    cheat_assert (
                                        (clib_cpuid_supports_bmi () != 0)
                                        == (__builtin_cpu_supports ("bmi")
                                            != 0));) test (clib_cpuid_test_bmi2,
                                                           "Tests bmi2",
                                                           printf ("- Testing "
                                                                   "%s\n",
                                                               __func__);
                                                           cheat_assert (
                                                               (clib_cpuid_supports_bmi2 ()
                                                                   != 0)
                                                               == (__builtin_cpu_supports ("bmi2")
                                                                   != 0));)
                                    test (
                                        clib_cpuid_test_aes,
                                        "Tests aes",
                                        printf ("- Testing %s\n", __func__);
                                        cheat_assert (
                                            (clib_cpuid_supports_aes () != 0)
                                            == (__builtin_cpu_supports ("aes")
                                                != 0));) test (clib_cpuid_test_avx512vl,
                                                               "Tests "
                                                               "avx512vl",
                                                               printf (
                                                                   "- Testing "
                                                                   "%s\n",
                                                                   __func__);
                                                               cheat_assert (
                                                                   (clib_cpuid_supports_avx512vl ()
                                                                       != 0)
                                                                   == (__builtin_cpu_supports ("avx512vl")
                                                                       != 0));)
                                        test (
                                            clib_cpuid_test_avx512bw,
                                            "Tests avx512bw",
                                            printf ("- Testing %s\n",
                                                __func__);
                                            cheat_assert (
                                                (clib_cpuid_supports_avx512bw ()
                                                    != 0)
                                                == (__builtin_cpu_supports (
                                                        "avx512bw")
                                                    != 0));) test (clib_cpuid_test_avx512dq,
                                                                   "Tests "
                                                                   "avx512dq",
                                                                   printf (
                                                                       "- "
                                                                       "Testin"
                                                                       "g "
                                                                       "%s\n",
                                                                       __func__);
                                                                   cheat_assert (
                                                                       (clib_cpuid_supports_avx512dq ()
                                                                           != 0)
                                                                       == (__builtin_cpu_supports (
                                                                               "avx512dq")
                                                                           != 0));)
                                            test (
                                                clib_cpuid_test_avx512cd,
                                                "Tests avx512cd",
                                                printf ("- Testing %s\n",
                                                    __func__);
                                                cheat_assert (
                                                    (clib_cpuid_supports_avx512cd ()
                                                        != 0)
                                                    == (__builtin_cpu_supports (
                                                            "avx512cd")
                                                        != 0));)
                                                test (
                                                    clib_cpuid_test_avx512er,
                                                    "Tests avx512er",
                                                    printf ("- Testing %s\n",
                                                        __func__);
                                                    cheat_assert (
                                                        (clib_cpuid_supports_avx512er ()
                                                            != 0)
                                                        == (__builtin_cpu_supports (
                                                                "avx512er")
                                                            != 0));)
                                                    test (
                                                        clib_cpuid_test_avx512pf,
                                                        "Tests avx512pf",
                                                        printf (
                                                            "- Testing %s\n",
                                                            __func__);
                                                        cheat_assert (
                                                            (clib_cpuid_supports_avx512pf ()
                                                                != 0)
                                                            == (__builtin_cpu_supports (
                                                                    "avx512pf")
                                                                != 0));)
                                                        test (clib_cpuid_test_avx512vbmi,
                                                              "Tests "
                                                              "avx512vbmi",
                                                              printf (
                                                                  "- Testing "
                                                                  "%s\n",
                                                                  __func__);
                                                              cheat_assert (
                                                                  (clib_cpuid_supports_avx512vbmi ()
                                                                      != 0)
                                                                  == (__builtin_cpu_supports (
                                                                          "avx"
                                                                          "512"
                                                                          "vbm"
                                                                          "i")
                                                                      != 0));)
                                                            test (
                                                                clib_cpuid_test_avx512ifma,
                                                                "Tests "
                                                                "avx512ifma",
                                                                printf (
                                                                    "- "
                                                                    "Testing "
                                                                    "%s\n",
                                                                    __func__);
                                                                cheat_assert (
                                                                    (clib_cpuid_supports_avx512ifma ()
                                                                        != 0)
                                                                    == (__builtin_cpu_supports (
                                                                            "a"
                                                                            "v"
                                                                            "x"
                                                                            "5"
                                                                            "1"
                                                                            "2"
                                                                            "i"
                                                                            "f"
                                                                            "m"
                                                                            "a")
                                                                        != 0));)
                                                                test (
                                                                    clib_cpuid_test_gfni,
                                                                    "Tests "
                                                                    "gfni",
                                                                    printf (
                                                                        "- "
                                                                        "Testi"
                                                                        "ng "
                                                                        "%s\n",
                                                                        __func__);
                                                                    cheat_assert (
                                                                        (clib_cpuid_supports_gfni ()
                                                                            != 0)
                                                                        == (__builtin_cpu_supports (
                                                                                "gfni")
                                                                            != 0));)
                                                                    test (
                                                                        clib_cpuid_test_vpclmulqdq,
                                                                        "Tests"
                                                                        " vpcl"
                                                                        "mulqd"
                                                                        "q",
                                                                        printf (
                                                                            "-"
                                                                            " "
                                                                            "T"
                                                                            "e"
                                                                            "s"
                                                                            "t"
                                                                            "i"
                                                                            "n"
                                                                            "g"
                                                                            " "
                                                                            "%"
                                                                            "s"
                                                                            "\n",
                                                                            __func__);
                                                                        cheat_assert (
                                                                            (clib_cpuid_supports_vpclmulqdq ()
                                                                                != 0)
                                                                            == (__builtin_cpu_supports (
                                                                                    "vpclmulqdq")
                                                                                != 0));)