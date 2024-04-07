#include "clib_io.h"
#include <stdio.h>
#include <stdlib.h>

const char *clib_io_module_name (void) { return "clib_io"; }

#ifdef __unix__

#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <termios.h>
#include <unistd.h>

int clib_getch (void)
{
    struct termios oldattr;
    struct termios newattr;
    int in_char = 0;
    tcgetattr (STDIN_FILENO, &oldattr);
    newattr = oldattr;
    newattr.c_lflag &= ~((unsigned int)ICANON | (unsigned int)ECHO);
    tcsetattr (STDIN_FILENO, TCSANOW, &newattr);
    in_char = getchar ();
    tcsetattr (STDIN_FILENO, TCSANOW, &oldattr);
    return in_char;
}

/**
 Linux (POSIX) implementation of _kbhit().
 Morgan McGuire, morgan@cs.brown.edu
 */
int clib_kbhit (void)
{
    struct termios term;
    struct termios term_old;
    int bytes = 0;
    tcgetattr (0, &term_old);
    tcgetattr (0, &term);
    term.c_lflag &= ~((unsigned int)ICANON);
    term.c_lflag &= ~((unsigned int)ECHO);
    tcsetattr (0, TCSANOW, &term);
    setbuf (stdin, NULL);
    ioctl (0, FIONREAD, &bytes);
    tcsetattr (0, TCSANOW, &term_old);
    return bytes > 0;
}

size_t clib_safe_gets (char *buffer, size_t size)
{
    size_t count = 0;
    int in_char = '\0';
    struct termios term;
    struct termios term_old;
    tcgetattr (0, &term_old);
    tcgetattr (0, &term);
    term.c_lflag &= ~((unsigned int)ICANON);
    term.c_lflag &= ~((unsigned int)ECHO);
    tcsetattr (0, TCSANOW, &term);
    setbuf (stdin, NULL);
    while (size - 1)
    {
        in_char = getchar ();
        switch (in_char)
        {
        case '\0':
        case '\n':
            size = 1;
            break;
        case '\b':
            buffer[count] = '\0';
            size++;
            count--;
            break;
        default:
            buffer[count] = (char)in_char;
            count++;
            size--;
        }
    }
    buffer[count] = '\0';
    tcsetattr (0, TCSANOW, &term_old);
    return count;
}

int clib_mkdir (const char *name, int mode)
{
    struct stat stat_str = { 0 };

    if (stat (name, &stat_str) == -1)
    {
        return mkdir (name, (mode_t)mode);
    }
    return 0;
}

#elif defined(_WIN32) || defined(_WIN64)

#include <conio.h>
#include <windows.h>

int clib_getch (void) { return _getch (); }

int clib_kbhit (void) { return _kbhit (); }

size_t clib_safe_gets (char *buffer, size_t size)
{
    size_t count = 0;
    int in_char = '\0';
    while (size - 1)
    {
        in_char = clib_getch ();
        switch (in_char)
        {
        case '\0':
        case '\n':
        case 'r':
            printf ("\n");
            size = 1;
            break;
        case '\b':
            printf ("%c \b", in_char);
            buffer[count] = '\0';
            size++;
            count--;
            break;
        default:
            printf ("%c", in_char);
            buffer[count] = (char)in_char;
            count++;
            size--;
        }
    }
    buffer[count] = '\0';
    return count;
}

int clib_mkdir (const char *name, int mode)
{
    (void)mode;
    return CreateDirectoryA (name, NULL);
}

#endif

char *clib_read_variable_string (char **dest, size_t initial_size)
{
    int in_char = clib_getch ();
    size_t max = initial_size;
    size_t index = 0;
#ifndef __GNUC__
    if (dest == NULL)
    {
        return NULL;
    }
#endif /* !__GNUC__ */
    *dest = (char *)calloc (initial_size, sizeof (char));
    if (*dest == NULL)
    {
        return NULL;
    }
    while (in_char != '\r' && in_char != '\n' && in_char != '\0'
           && in_char != EOF)
    {
        *dest[index++] = (char)in_char;
        if (index >= max)
        {
            *dest = realloc (*dest, max + initial_size);
            if (*dest == NULL)
            {
                return NULL;
            }
            max += initial_size;
        }
    }
    if (index == max - 1)
    {
        *dest = realloc (*dest, max + 1);
        *dest[index + 1] = '\0';
    }
    return *dest;
}
