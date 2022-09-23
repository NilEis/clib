/** @file
 * @brief functions for getting user input or output
 */
#ifndef CLIB_IO_H
#define CLIB_IO_H

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

#endif // CLIB_IO_H
