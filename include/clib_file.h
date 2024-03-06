/** @file
 * @brief functions for using files
 */
#if !defined(CLIB_FILE_H) && defined(CLIB_INCLUDE_FILE)
#define CLIB_FILE_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "clib_c90_support.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

/**
 * @brief Returns the size of the file
 *
 * @param file
 * @return size_t size
 */
size_t clib_file_get_size (FILE *file);

/**
 * @brief Allocates a buffer and reads the whole binary file into it
 *
 * @param path
 * @return uint8_t* (has to be freed by the caller)
 */
uint8_t *clib_file_load (const char *path);

/**
 * @brief Allocates a buffer and reads the whole file into it
 *
 * @param file
 * @return char* (has to be freed by the caller)
 */
char *clib_file_load_till_eof_str (FILE *file);

/**
 * @brief Allocates a buffer and reads the whole binary file into it
 *
 * @param file
 * @return uint8_t* (has to be freed by the caller)
 */
uint8_t *clib_file_load_till_eof (FILE *file);

/**
 * @brief Allocates a buffer and reads the whole file into it
 *
 * @param path
 * @return char* (has to be freed by the caller)
 */
char *clib_file_load_str (const char *path);

/**
 * @brief Allocates a buffer and reads the whole binary file into it
 *
 * @param file
 * @return uint8_t* (has to be freed by the caller)
 */
uint8_t *clib_file_get_content (FILE *file);

/**
 * @brief Allocates a buffer and reads the whole file into it
 *
 * @param file
 * @return char* (has to be freed by the caller)
 */
char *clib_file_get_content_str (FILE *file);

#ifdef CLIB_FILE_SELECTOR

/**
 * @brief Opens a file selector dialog and returns the selected file
 *
 * @return char* path to the selected file (has to be freed by the caller)
 */
char *clib_file_selector_open_file (void);

#endif /* CLIB_FILE_SELECTOR */

#ifdef __cplusplus
}
#endif

#endif /* CLIB_FILE_H */
