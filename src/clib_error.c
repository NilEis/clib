#include "clib_error.h"

clib_error_code_t clib_errno = 0;

const char *clib_error_get_string(clib_error_code_t error_number)
{
    switch (error_number)
    {
    case CLIB_ERRNO_NO_ERROR:
        return "No error in clib";
    case CLIB_ERRNO_ALLOCATION_ERROR:
        return "Could not allocate memory: malloc returned NULL";
    case CLIB_ERRNO_ALLOCATION_ZEROED_ERROR:
        return "Could not allocate memory: calloc returned NULL";
    case CLIB_ERRNO_REALLOCATION_ERROR:
        return "Could not reallocate memory: realloc returned NULL";
    case CLIB_ERRNO_TREE_EMPTY:
        return "No element in tree";
    case CLIB_ERRNO_STRING_INVALID_BASE:
        return "Invalid base for integer conversion";
    default:
        return "Invalid error code";
    }
}