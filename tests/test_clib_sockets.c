#include "cheat.h"
#include "cheats.h"

#include "clib.h"

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

CHEAT_TEST (
    clib_sockets_init, printf ("- Testing %s\n", __func__);
    clib_error_code_t ret = clib_sockets_init ();
    if (ret != CLIB_ERRNO_NO_ERROR) {
        printf ("Error: %s\n", clib_error_get_string (ret));
    };
    cheat_assert (ret == CLIB_ERRNO_NO_ERROR);)