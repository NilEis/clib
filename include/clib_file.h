/** @file
 * @brief functions for using files
 */
#if !defined(CLIB_FILE_H) && defined(CLIB_INCLUDE_FILE)
#define CLIB_FILE_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stddef.h>
#include <stdio.h>
#include "clib_c90_support.h"

/**
 * @brief Returns the size of the file
 * 
 * @param file 
 * @return size_t size
 */
size_t clib_file_get_size(FILE *file);

/**
 * @brief Allocates a buffer and reads the whole file into it
 * 
 * @param path 
 * @return const char* (has to be freed by the caller)
 */
const char *clib_file_load(const char *path);

#ifdef __cplusplus
}
#endif

#endif /* CLIB_FILE_H */
