#include "clib.h"

#ifdef __unix__

#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

int terminal_getch(void)
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr(STDIN_FILENO, &oldattr);
    newattr = oldattr;
    newattr.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
    return ch;
}

/**
 Linux (POSIX) implementation of _kbhit().
 Morgan McGuire, morgan@cs.brown.edu
 */
int terminal_kbhit(void)
{
    struct termios term, term_old;
    tcgetattr(0, &term_old);
    tcgetattr(0, &term);
    term.c_lflag &= ~ICANON;
    term.c_lflag &= ~ECHO;
    tcsetattr(0, TCSANOW, &term);
    setbuf(stdin, NULL);
    int bytes;
    ioctl(0, FIONREAD, &bytes);
    tcsetattr(0, TCSANOW, &term_old);
    return bytes > 0;
}

size_t terminal_safe_gets(char *buffer, size_t size)
{
    size_t count = 0;
    char ch = '\0';
    struct termios term, term_old;
    tcgetattr(0, &term_old);
    tcgetattr(0, &term);
    term.c_lflag &= ~ICANON;
    term.c_lflag &= ~ECHO;
    tcsetattr(0, TCSANOW, &term);
    setbuf(stdin, NULL);
    while (size - 1)
    {
        ch = getchar();
        switch (ch)
        {
        case 0x1B:
            break;
        case '\0':
        case '\n':
            size = 1;
            break;
        case '\b':
            buffer[count] = '\0';
            size++;
            count--;
            count = count < 0 ? 0 : count;
            break;
        default:
            buffer[count] = ch;
            count++;
            size--;
        }
    }
    buffer[count] = '\0';
    tcsetattr(0, TCSANOW, &term_old);
    return count;
}

#elif defined(_WIN32) || defined(_WIN64)

#include <windows.h>
#include <conio.h>

int clib_getch(void)
{
    return getch();
}

int clib_kbhit(void)
{
    return kbhit();
}

size_t clib_safe_gets(char *buffer, size_t size)
{
    size_t count = 0;
    int ch = '\0';
    while (size - 1)
    {
        ch = clib_getch();
        switch (ch)
        {
        case 0xE0:
            break;
        case '\0':
        case '\n':
        case 13:
            printf("\n");
            size = 1;
            break;
        case '\b':
            printf("%c \b", ch);
            buffer[count] = '\0';
            size++;
            count--;
            break;
        default:
            printf("%c", ch);
            buffer[count] = (char)ch;
            count++;
            size--;
        }
    }
    buffer[count] = '\0';
    return count;
}

#endif