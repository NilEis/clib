/** @file
 * @brief functions for error managment
 */
#ifndef CLIB_ERROR_H
#define CLIB_ERROR_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "clib_c90_support.h"

/**
 * @brief an enum containing all possible error codes
 */
typedef enum
{
    CLIB_ERRNO_NO_ERROR = 0,
    CLIB_ERRNO_ALLOCATION_ERROR,
    CLIB_ERRNO_ALLOCATION_ZEROED_ERROR,
    CLIB_ERRNO_ARRAY_INDEX_OUT_OF_BOUNDS,
    CLIB_ERRNO_CPUID_INVALID_LEAF,
    CLIB_ERRNO_CPUID_INVALID_SUBLEAF,
    CLIB_ERRNO_FILE_OPEN_ERROR,
    CLIB_ERRNO_FILE_READ_ERROR,
    CLIB_ERRNO_FILE_SELECTOR_CANCEL,
    CLIB_ERRNO_FILE_SELECTOR_ERROR,
    CLIB_ERRNO_REALLOCATION_ERROR,
#ifdef _WIN32
    CLIB_ERRNO_SOCKET_WSASYSNOTREADY,
    CLIB_ERRNO_SOCKET_WSAVERNOTSUPPORTED,
    CLIB_ERRNO_SOCKET_WSAEINPROGRESS,
    CLIB_ERRNO_SOCKET_WSAEPROCLIM,
    CLIB_ERRNO_SOCKET_WSAEFAULT,
#endif
    CLIB_ERRNO_STRING_INVALID_BASE,
    CLIB_ERRNO_TREE_EMPTY,
    CLIB_INTERNAL_ERRNO_MAX_VALUE
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
const char *clib_error_get_string (clib_error_code_t error_number);

#ifdef __cplusplus
}
#endif

#endif /* CLIB_ERROR_H */
