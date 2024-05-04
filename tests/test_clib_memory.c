#include "cheat.h"
#include "cheats.h"

#include "clib.h"
#include <assert.h>
#include <stdint.h>
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

CHEAT_TEST (clib_memory_copy, const uint_least64_t in = 0xDEADCFFE;
            const uint_least8_t in_b = 0xA;
            uint_least64_t out = 0;
            uint_least8_t out_b = 0;
            init_console ();
            clib_memory_copy (&in, &out, sizeof (in));
            clib_memory_copy (&in_b, &out_b, sizeof (in_b));
            printf ("- Testing %s\n", __func__);
            cheat_assert (out == in);
            cheat_assert (out_b == in_b);)

CHEAT_TEST (
    clib_memory_set, int i = 0; uint_least64_t out[16] = { 0 };
    const uint_least64_t in = 0xDEADCFFE;
    const uint_least8_t in_b = 0xF;
    init_console ();
    clib_memory_set_u64 (out, in, 16);
    printf ("- Testing %s\n", __func__);
    for (i = 0; i < 16; i++) { cheat_assert  (out[i] == in); })