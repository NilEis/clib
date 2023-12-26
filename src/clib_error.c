#include "clib_error.h"

clib_error_code_t clib_errno = 0;

static const char *clib_error_messages[] = {
    /* CLIB_ERRNO_NO_ERROR */ "No error in clib",
    /* CLIB_ERRNO_ALLOCATION_ERROR */ "Could not allocate memory: malloc returned NULL",
    /* CLIB_ERRNO_ALLOCATION_ZEROED_ERROR */ "Could not allocate memory: calloc returned NULL",
    /* CLIB_ERRNO_REALLOCATION_ERROR */ "Could not reallocate memory: realloc returned NULL",
    /* CLIB_ERRNO_TREE_EMPTY */ "No element in tree"};

const char *clib_error_get_string(clib_error_code_t error_number)
{
    static const char invalid_code[] = "Invalid error code";
    if (error_number < 0 || __CLIB_ERRNO_MAX_VALUE <= error_number)
    {
        return invalid_code;
    }
    return clib_error_messages[error_number];
}