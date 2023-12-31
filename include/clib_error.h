/** @file
 * @brief functions for error managment
 */
#ifndef CLIB_ERROR_H
#define CLIB_ERROR_H

#include "clib_c90_support.h"

typedef enum
{
    CLIB_ERRNO_NO_ERROR = 0,
    CLIB_ERRNO_ALLOCATION_ERROR,
    CLIB_ERRNO_ALLOCATION_ZEROED_ERROR,
    CLIB_ERRNO_REALLOCATION_ERROR,
    CLIB_ERRNO_TREE_EMPTY,
    CLIB_ERRNO_STRING_INVALID_BASE,
    __CLIB_ERRNO_MAX_VALUE
} clib_error_code_t;

/**
 * @brief contains the last error_value
 */
extern clib_error_code_t clib_errno;

/**
 * @brief returns the string represantation of an error code
 *
 * @param error_number the error code
 * @return const char* a pointer to the error string
 */
const char *clib_error_get_string(clib_error_code_t error_number);

#endif /* CLIB_ERROR_H */
