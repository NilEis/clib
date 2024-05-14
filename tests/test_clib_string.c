#include "cheat.h"
#include "cheats.h"

#include "clib.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>

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

CHEAT_TEST (test_clib_string_builder,
            clib_string_builder_t *builder = clib_string_builder_create (8);
            char *res = NULL;
            printf ("- Testing %s\n", __func__);
            clib_string_builder_append (builder, "Hallo");
            res = clib_string_builder_get_string (builder);
            cheat_assert_string (res, "Hallo");
            free (res);
            clib_string_builder_append (builder, ", Welt");
            res = clib_string_builder_get_string (builder);
            cheat_assert_string (res, "Hallo, Welt");
            cheat_assert_not_string (res, "Hello, Welt!");
            free (res);
            clib_string_builder_free (builder);)

CHEAT_TEST (test_clib_string_length, init_console ();
            const char *const str = "hello world";
            const size_t len = clib_string_length (str);
            printf ("- Testing %s\n", __func__);
            cheat_assert (len == strlen (str));)

CHEAT_TEST (test_clib_string_copy, init_console ();
            const char *const src = "hello world";
            char dest[20] = { 0 };
            const size_t size = clib_string_copy (dest, src, 5);
            printf ("- Testing %s\n", __func__);
            cheat_assert (strcmp (dest, "hello") == 0 && size == 5);)

CHEAT_TEST (
    test_clib_string_cmp, init_console (); printf ("- Testing %s\n", __func__);
    const char *const str_a1 = "xxABAxx";
    const char *const str_b1 = "xxBABxx";
    cheat_assert ((clib_string_cmp (str_a1, str_b1) < 0)
                  == (strcmp (str_a1, str_b1) < 0));
    const char *const str_a2 = "xxABAxx";
    const char *const str_b2 = "xxABAxx";
    cheat_assert (clib_string_cmp (str_a2, str_b2) == strcmp (str_a2, str_b2));
    const char *const str_a3 = "xxBABxx";
    const char *const str_b3 = "xxABAxx";
    printf ("%d : %d\n",
        clib_string_cmp (str_a3, str_b3),
        strcmp (str_a3, str_b3));
    cheat_assert ((0 < clib_string_cmp (str_a3, str_b3))
                  == (0 < strcmp (str_a3, str_b3)));)

CHEAT_TEST (test_clib_string_replace_char, init_console ();
            char str[] = "hello world";
            const int replaced = clib_string_replace_char (str, 'l', 'x');
            printf ("- Testing %s\n", __func__);
            cheat_assert (strcmp (str, "hexlo world") == 0 && replaced == 1);)

CHEAT_TEST (
    test_clib_string_replace_char_all, init_console ();
    char str[] = "hello world";
    const size_t replaced = clib_string_replace_char_all (str, 'l', 'x');
    printf ("- Testing %s\n", __func__);
    cheat_assert (strcmp (str, "hexxo worxd") == 0 && replaced == 3);)

CHEAT_TEST (test_clib_string_dist_lev, init_console ();
            const char *const a = "kitten";
            const char *const b = "sitting";
            const int dist = clib_string_dist_lev (a, b);
            printf ("- Testing %s\n", __func__);
            cheat_assert (dist == 3);)

CHEAT_TEST (test_clib_string_from_int, init_console (); const int64_t a = 1243;
            const int64_t b = 0xDEADCAFE;
            const char *const expected_a = "1243";
            const char *const expected_b = "DEADCAFE";
            char res_a[5] = { 0 };
            char res_b[9] = { 0 };
            printf ("- Testing %s\n", __func__);
            clib_string_from_int (res_a, a, CLIB_RADIX_DEC);
            clib_string_from_int (res_b, b, CLIB_RADIX_HEX);
            cheat_assert_string (res_a, expected_a);
            cheat_assert_string (res_b, expected_b);)

CHEAT_TEST (test_clib_string_reverse, init_console ();
            const char *const a = "AACHEN";
            char res_a[7] = { 0 };
            const char *const expected_a = "NEHCAA";
            printf ("- Testing %s\n", __func__);
            clib_string_reverse (a, res_a, clib_string_length (a));
            cheat_assert_string (res_a, expected_a);)

CHEAT_TEST (test_clib_string_reverse_in_place, init_console ();
            char a[] = "AACHEN";
            const char *const expected_a = "NEHCAA";
            printf ("- Testing %s\n", __func__);
            clib_string_reverse_in_place (a, clib_string_length (a));
            cheat_assert_string (a, expected_a);)