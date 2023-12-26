#ifndef __BASE_FILE__
#define __BASE_FILE__ __FILE__
#endif
#include "cheat.h"
#include "cheats.h"
#include "clib.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
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

#define NUM_TEST_VALUES 5

CHEAT_TEST(
    clib_data_structures_binary_heap_insert,
    clib_binary_heap_t *heap = NULL;
    int i = 0;
    int test_key_data[NUM_TEST_VALUES * 3] = {
        15, 6, 15, /* [15, 6] */
        8, 4, 8, /* [8, 4] */
        32, 2, 8, /* [32, 2] */
        1, 3, 1, /* [1, 3] */
        2, 9, 1 /* [1, 9] */};
    init_console();
    printf("- Testing %s\n", __func__);
    heap = clib_binary_heap_create(CLIB_MAX_HEAP, 5); 
    for (i = 0; i < NUM_TEST_VALUES; i++)
    {
        int32_t res = test_key_data[i*3+2];
        int32_t key = 0;
        clib_binary_heap_insert(heap, test_key_data[i*3], (void*)test_key_data[i*3+1]);
        (void)clib_binary_heap_get_first(heap, &key);
        cheat_assert(key == res);
    }
    clib_binary_heap_free(heap);)

CHEAT_TEST(
    clib_data_structures_binary_heap_stringify,
    clib_binary_heap_t *heap = NULL;
    int i = 0;
    char*res=NULL;
    int test_key_data[NUM_TEST_VALUES * 3] = {
        15, 6, /* [15, 6] */
        8, 4, /* [8, 4] */
        32, 2, /* [32, 2] */
        1, 3, /* [1, 3] */
        2, 9, /* [1, 9] */};
    init_console();
    printf("- Testing %s\n", __func__);
    heap = clib_binary_heap_create(CLIB_MAX_HEAP, 5); 
    for (i = 0; i < NUM_TEST_VALUES; i++)
    {
        clib_binary_heap_insert(heap, test_key_data[i*2], (void*)test_key_data[(i*2)+1]);
    }
    res = clib_binary_heap_get_as_string(heap);
    cheat_assert_string(res, "[ 1, 2, 32, 15, 8 ]");
    free(res);
    clib_binary_heap_free(heap);)