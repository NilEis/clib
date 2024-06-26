#ifndef __BASE_FILE__
#define __BASE_FILE__ __FILE__
#endif

#include "cheat.h"
#include "cheats.h"

#include "clib.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COMMA        ,
#define INVALID_DATA NULL

#if defined(_WIN32) || defined(WIN32)
#include <windows.h>

CHEAT_DECLARE (void init_console () {
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

#define NUM_TEST_VALUES 5

CHEAT_TEST (
    clib_data_structures_binary_heap_insert, clib_binary_heap_t *heap = NULL;
    int i = 0;
    int test_key_res[NUM_TEST_VALUES * 2] = { 15 COMMA 15 COMMA /* [15, 15] */
        8 COMMA 8 COMMA                                         /* [8, 8] */
        32 COMMA 8 COMMA                                        /* [32, 8] */
        1 COMMA 1 COMMA                                         /* [1, 1] */
        2 COMMA 1 /* [2, 1] */ };
    {
        init_console ();
        printf ("- Testing %s\n", __func__);
        heap = clib_binary_heap_create (CLIB_MIN_HEAP, 5);
        for (i = 0; i < NUM_TEST_VALUES; i++)
        {
            int32_t res = test_key_res[i * 2 + 1];
            int32_t key = 0;
            clib_binary_heap_insert (heap, test_key_res[i * 2], INVALID_DATA);
            (void)clib_binary_heap_get_first (heap, &key);
            cheat_assert (key == res);
        }
        clib_binary_heap_free (heap);
    })

CHEAT_TEST (
    clib_data_structures_binary_heap_drop_first,
    clib_binary_heap_t *heap = NULL;
    int32_t key = 0;
    int i = 0;
    int32_t res_data[] = { 2 COMMA 8 COMMA 15 COMMA 32 };
    int test_key_data[NUM_TEST_VALUES]
    = { 15 COMMA 8 COMMA 32 COMMA 1 COMMA 2 };
    init_console ();
    printf ("- Testing %s\n", __func__);
    heap = clib_binary_heap_create (CLIB_MIN_HEAP, 5);
    for (i = 0; i < NUM_TEST_VALUES; i++) {
        clib_binary_heap_insert (heap, test_key_data[i], INVALID_DATA);
    }

    for (i = 0; i < NUM_TEST_VALUES - 1; i++) {
        clib_binary_heap_drop_first (heap, NULL);
        clib_binary_heap_get_first (heap, &key);
        cheat_assert (key == res_data[i]);
    }

    clib_binary_heap_free (heap);)

CHEAT_TEST (
    clib_data_structures_binary_heap_drop_and_insert,
    clib_binary_heap_t *heap = NULL;
    int32_t key = 0;
    int i = 0;
    int32_t res_data[]
    = { 3 COMMA 2 COMMA 5 COMMA 3 COMMA 15 COMMA 5 COMMA 32 COMMA 8 };
    int test_key_data[NUM_TEST_VALUES]
    = { 15 COMMA 8 COMMA 32 COMMA 1 COMMA 2 };
    {
        init_console ();
        printf ("- Testing %s\n", __func__);
        heap = clib_binary_heap_create (CLIB_MIN_HEAP, 5);
        for (i = 0; i < NUM_TEST_VALUES; i++)
        {
            clib_binary_heap_insert (heap, test_key_data[i], INVALID_DATA);
        }
        for (i = 0; i < NUM_TEST_VALUES - 1; i++)
        {
            clib_binary_heap_drop_and_insert (
                heap, NULL, res_data[i * 2], INVALID_DATA);
            clib_binary_heap_get_first (heap, &key);
            cheat_assert (key == res_data[i * 2 + 1]);
        }

        clib_binary_heap_free (heap);
    })

CHEAT_TEST (
    clib_data_structures_binary_heap_stringify,
    clib_binary_heap_t *heap = NULL;
    int i = 0;
    char *res = NULL;
    int test_key_data[NUM_TEST_VALUES]
    = { 15 COMMA 8 COMMA 32 COMMA 1 COMMA 2 };
    {
        init_console ();
        printf ("- Testing %s\n", __func__);
        heap = clib_binary_heap_create (CLIB_MIN_HEAP, 5);
        for (i = 0; i < NUM_TEST_VALUES; i++)
        {
            clib_binary_heap_insert (heap, test_key_data[i], INVALID_DATA);
        }
        res = clib_binary_heap_get_as_string (heap);
        cheat_assert_string (res, "[ 1, 2, 32, 15, 8 ]");
        free (res);
        clib_binary_heap_free (heap);
    })
CHEAT_TEST (clib_data_structures_stack, clib_stack_t *stack = NULL;
            init_console ();
            printf ("- Testing %s\n", __func__);
            stack = clib_stack_create (2);
            cheat_assert (clib_stack_push (stack, (void *)1) != NULL);
            cheat_assert (clib_stack_size (stack) == 1);
            cheat_assert (clib_stack_push (stack, (void *)2) != NULL);
            cheat_assert (clib_stack_size (stack) == 2);
            cheat_assert (clib_stack_push (stack, (void *)3) != NULL);
            cheat_assert (clib_stack_size (stack) == 3);
            cheat_assert (clib_stack_pop (stack) == (void *)3);
            cheat_assert (clib_stack_size (stack) == 2);
            cheat_assert (clib_stack_pop (stack) == (void *)2);
            cheat_assert (clib_stack_size (stack) == 1);
            cheat_assert (clib_stack_pop (stack) == (void *)1);
            cheat_assert (clib_stack_size (stack) == 0);
            cheat_assert (clib_stack_pop (stack) == NULL);)