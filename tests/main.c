#ifndef __BASE_FILE__
#define __BASE_FILE__ __FILE__
#endif
#include "cheat.h"

#if defined(_WIN32) || defined(WIN32)
#include <windows.h>
#else
#include <unistd.h>
#include <sys/types.h>
#endif

CHEAT_DECLARE(
    void init_console()
    {
#if defined(_WIN32) || defined(WIN32)
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
#endif
        return;
    })

CHEAT_DECLARE(
    int run_test(char *name)
    {
#if defined(_WIN32) || defined(WIN32)
        STARTUPINFO startup_info;
        PROCESS_INFORMATION process_info;
        ZeroMemory(&startup_info, sizeof(startup_info));
        startup_info.cb = sizeof(startup_info);
        ZeroMemory(&process_info, sizeof(process_info));
        if (!CreateProcess(NULL, name, NULL, NULL, FALSE, 0, NULL, NULL, &startup_info, &process_info))
        {
            char buf[256];
            FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                           NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                           buf, (sizeof(buf) / sizeof(wchar_t)), NULL);
            printf("%d - Error: %s\n", __LINE__, buf);
            return -1;
        }
        WaitForSingleObject(process_info.hProcess, INFINITE);
        uint32_t ret;

        if (!GetExitCodeProcess(process_info.hProcess, (LPDWORD)&ret))
        {
            char buf[256];
            FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                           NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                           buf, (sizeof(buf) / sizeof(wchar_t)), NULL);
            printf("%d - Error: %s\n", __LINE__, buf);
            return -1;
        }

        CloseHandle(process_info.hProcess);
        CloseHandle(process_info.hThread);

        return ret;
#else
        pid_t pid = fork();
        if (pid == -1)
        {
            return 0xDEAD;
        }
        else if (pid == 0)
        {
            execv(name, (char**){name,NULL});
            _exit(0xDEAD);
        }
        else
        {
            int status;
            if (waitpid(pid, &status, 0) == -1)
            {
                return 0xDEAD;
            }
            else
            {
                return !WEXITSTATUS(status);
            }
        }
#endif
        return 0;
    })

CHEAT_TEST(test_string_functions,
           init_console();
           int p = run_test("./test_clib_string -m");
           printf("%d\n", p);
           cheat_assert(p == 0);)

CHEAT_TEST(test_memory_functions,
           init_console();
           int p = run_test("./test_clib_memory -m");
           printf("%d\n", p);
           cheat_assert(p == 0);)