#include "cheat.h"
#include "cheats.h"

#include "clib.h"
#include <stdio.h>

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

CHEAT_TEST (clib_cpuid, {
    printf ("- Testing %s\n", __func__);
    clib_error_code_t ret = clib_sockets_init ();
    if (ret != CLIB_ERRNO_NO_ERROR)
    {
        printf ("Error: %s\n", clib_error_get_string (ret));
    };
    cheat_assert (ret == CLIB_ERRNO_NO_ERROR);
})

CHEAT_TEST (clib_cpuid_test_cmov, {
    printf ("- Testing %s\n", __func__);
    cheat_assert ((clib_cpuid_supports_cmov () != 0)
                  == (__builtin_cpu_supports ("cmov") != 0));
})
CHEAT_TEST (clib_cpuid_test_mmx, {
    printf ("- Testing %s\n", __func__);
    cheat_assert ((clib_cpuid_supports_mmx () != 0)
                  == (__builtin_cpu_supports ("mmx") != 0));
})
CHEAT_TEST (clib_cpuid_test_popcnt, {
    printf ("- Testing %s\n", __func__);
    cheat_assert ((clib_cpuid_supports_popcnt () != 0)
                  == (__builtin_cpu_supports ("popcnt") != 0));
})
CHEAT_TEST (clib_cpuid_test_sse, {
    printf ("- Testing %s\n", __func__);
    cheat_assert ((clib_cpuid_supports_sse () != 0)
                  == (__builtin_cpu_supports ("sse") != 0));
})
CHEAT_TEST (clib_cpuid_test_sse2, {
    printf ("- Testing %s\n", __func__);
    cheat_assert ((clib_cpuid_supports_sse2 () != 0)
                  == (__builtin_cpu_supports ("sse2") != 0));
})
CHEAT_TEST (clib_cpuid_test_sse3, {
    printf ("- Testing %s\n", __func__);
    cheat_assert ((clib_cpuid_supports_sse3 () != 0)
                  == (__builtin_cpu_supports ("sse3") != 0));
})
CHEAT_TEST (clib_cpuid_test_ssse3, {
    printf ("- Testing %s\n", __func__);
    cheat_assert ((clib_cpuid_supports_ssse3 () != 0)
                  == (__builtin_cpu_supports ("ssse3") != 0));
})
CHEAT_TEST (clib_cpuid_test_sse4_1, {
    printf ("- Testing %s\n", __func__);
    cheat_assert ((clib_cpuid_supports_sse4_1 () != 0)
                  == (__builtin_cpu_supports ("sse4.1") != 0));
})
CHEAT_TEST (clib_cpuid_test_sse4_2, {
    printf ("- Testing %s\n", __func__);
    cheat_assert ((clib_cpuid_supports_sse4_2 () != 0)
                  == (__builtin_cpu_supports ("sse4.2") != 0));
})
CHEAT_TEST (clib_cpuid_test_avx, {
    printf ("- Testing %s\n", __func__);
    cheat_assert ((clib_cpuid_supports_avx () != 0)
                  == (__builtin_cpu_supports ("avx") != 0));
})
CHEAT_TEST (clib_cpuid_test_avx2, {
    printf ("- Testing %s\n", __func__);
    cheat_assert ((clib_cpuid_supports_avx2 () != 0)
                  == (__builtin_cpu_supports ("avx2") != 0));
})
CHEAT_TEST (clib_cpuid_test_sse4a, {
    printf ("- Testing %s\n", __func__);
    cheat_assert ((clib_cpuid_supports_sse4a () != 0)
                  == (__builtin_cpu_supports ("sse4a") != 0));
})
CHEAT_TEST (clib_cpuid_test_fma, {
    printf ("- Testing %s\n", __func__);
    cheat_assert ((clib_cpuid_supports_fma () != 0)
                  == (__builtin_cpu_supports ("fma") != 0));
})
CHEAT_TEST (clib_cpuid_test_fma4, {
    printf ("- Testing %s\n", __func__);
    cheat_assert ((clib_cpuid_supports_fma4 () != 0)
                  == (__builtin_cpu_supports ("fma4") != 0));
})
CHEAT_TEST (clib_cpuid_test_xop, {
    printf ("- Testing %s\n", __func__);
    cheat_assert ((clib_cpuid_supports_xop () != 0)
                  == (__builtin_cpu_supports ("xop") != 0));
})
CHEAT_TEST (clib_cpuid_test_avx512f, {
    printf ("- Testing %s\n", __func__);
    cheat_assert ((clib_cpuid_supports_avx512f () != 0)
                  == (__builtin_cpu_supports ("avx512f") != 0));
})
CHEAT_TEST (clib_cpuid_test_bmi1, {
    printf ("- Testing %s\n", __func__);
    cheat_assert ((clib_cpuid_supports_bmi1 () != 0)
                  == (__builtin_cpu_supports ("bmi") != 0));
})
CHEAT_TEST (clib_cpuid_test_bmi2, {
    printf ("- Testing %s\n", __func__);
    cheat_assert ((clib_cpuid_supports_bmi2 () != 0)
                  == (__builtin_cpu_supports ("bmi2") != 0));
})
CHEAT_TEST (clib_cpuid_test_aes, {
    printf ("- Testing %s\n", __func__);
    cheat_assert ((clib_cpuid_supports_aes () != 0)
                  == (__builtin_cpu_supports ("aes") != 0));
})
CHEAT_TEST (clib_cpuid_test_avx512vl, {
    printf ("- Testing %s\n", __func__);
    cheat_assert ((clib_cpuid_supports_avx512vl () != 0)
                  == (__builtin_cpu_supports ("avx512vl") != 0));
})
CHEAT_TEST (clib_cpuid_test_avx512bw, {
    printf ("- Testing %s\n", __func__);
    cheat_assert ((clib_cpuid_supports_avx512bw () != 0)
                  == (__builtin_cpu_supports ("avx512bw") != 0));
})
CHEAT_TEST (clib_cpuid_test_avx512dq, {
    printf ("- "
            "Testing %s\n",
        __func__);
    cheat_assert ((clib_cpuid_supports_avx512dq () != 0)
                  == (__builtin_cpu_supports ("avx512dq") != 0));
})
CHEAT_TEST (clib_cpuid_test_avx512cd, {
    printf ("- Testing %s\n", __func__);
    cheat_assert ((clib_cpuid_supports_avx512cd () != 0)
                  == (__builtin_cpu_supports ("avx512cd") != 0));
})
CHEAT_TEST (clib_cpuid_test_avx512er, {
    printf ("- Testing %s\n", __func__);
    cheat_assert ((clib_cpuid_supports_avx512er () != 0)
                  == (__builtin_cpu_supports ("avx512er") != 0));
})
CHEAT_TEST (clib_cpuid_test_avx512pf, {
    printf ("- Testing %s\n", __func__);
    cheat_assert ((clib_cpuid_supports_avx512pf () != 0)
                  == (__builtin_cpu_supports ("avx512pf") != 0));
})
CHEAT_TEST (clib_cpuid_test_avx512vbmi, {
    printf ("- Testing %s\n", __func__);
    cheat_assert ((clib_cpuid_supports_avx512vbmi () != 0)
                  == (__builtin_cpu_supports ("avx512vbmi") != 0));
})
CHEAT_TEST (clib_cpuid_test_avx512ifma, {
    printf ("- Testing %s\n", __func__);
    cheat_assert ((clib_cpuid_supports_avx512ifma () != 0)
                  == (__builtin_cpu_supports ("avx512ifma") != 0));
})
CHEAT_TEST (clib_cpuid_test_gfni, {
    printf ("- Testing %s\n", __func__);
    cheat_assert ((clib_cpuid_supports_gfni () != 0)
                  == (__builtin_cpu_supports ("gfni") != 0));
})
CHEAT_TEST (clib_cpuid_test_vpclmulqdq, {
    printf ("- Testing %s\n", __func__);
    cheat_assert ((clib_cpuid_supports_vpclmulqdq () != 0)
                  == (__builtin_cpu_supports ("vpclmulqdq") != 0));
})