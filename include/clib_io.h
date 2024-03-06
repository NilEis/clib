/** @file
 * @brief functions for getting user input or output
 */
#if !defined( CLIB_IO_H) && defined(CLIB_INCLUDE_IO)
#define CLIB_IO_H

#ifdef __cplusplus 
extern "C" {
#endif

#include "clib_c90_support.h"
#include <stddef.h>

/**
 * @brief Reads a char from stdin without waiting for '\n'
 * @return (int)
 */
int clib_getch(void);

/**
 * @brief returns 1 if a key was pressed.
 * @return (int)
 */

int clib_kbhit(void);

/**
 * @brief writes the input to the buffer
 * @return (size_t) the number of the bytes read
 */
size_t clib_safe_gets(char *buffer, size_t size);

/**
 * @brief creates a folder
 * @param name the path of the folder
 * @param mode the mode of the folder (0777)
 * @return the return value of the os for creating the folder
 */
int clib_mkdir(const char *name, int mode);

/** @fn char *clib_read_variable_string(char **dest, size_t initial_size)
 * @param dest (nonnull) The address of the destination pointer (NULL)
 * @param initial_size the initial size of the string
 * @return the string
 * @deprecated
 */
char *clib_read_variable_string(char **dest, size_t initial_size)
#ifdef __GNUC__
    __attribute__((nonnull(1)));
#else
    ;
#endif

#ifdef __cplusplus 
}
#endif

#endif /* CLIB_IO_H */
