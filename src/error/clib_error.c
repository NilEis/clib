#include "clib_error.h"
#include <stdlib.h>

const char *clib_error_module_name (void) { return "clib_error"; }

clib_error_code_t clib_errno = 0;
const char *clib_errmsg = NULL;

const char *clib_error_get_string (const clib_error_code_t error_number)
{
    switch (error_number)
    {
    case CLIB_ERRNO_NO_ERROR:
        return "No error in clib";
    case CLIB_ERRNO_ALLOCATION_ERROR:
        return "Could not allocate memory: malloc returned NULL";
    case CLIB_ERRNO_ALLOCATION_ZEROED_ERROR:
        return "Could not allocate memory: calloc returned NULL";
    case CLIB_ERRNO_ARRAY_INDEX_OUT_OF_BOUNDS:
        return "Array index out of bounds";
    case CLIB_ERRNO_CPUID_NOT_SUPPORTED:
        return "CPUID instruction not supported on this platform";
    case CLIB_ERRNO_CPUID_INVALID_LEAF:
        return "Invalid cpuid leaf";
    case CLIB_ERRNO_CPUID_INVALID_SUBLEAF:
        return "Invalid cpuid subleaf";
    case CLIB_ERRNO_FILE_OPEN_ERROR:
        return "Could not open the file";
    case CLIB_ERRNO_FILE_READ_ERROR:
        return "Could not read the file";
    case CLIB_ERRNO_FILE_SELECTOR_CANCEL:
        return "User canceled file selection";
    case CLIB_ERRNO_FILE_SELECTOR_ERROR:
    case CLIB_ERROR_LUA_INVALID_TYPE:
        return clib_errmsg;
    case CLIB_ERROR_LUA_NEW:
        return "Could not create new lua state";
    case CLIB_ERROR_LUA_RUN:
        return clib_errmsg;
    case CLIB_ERRNO_REALLOCATION_ERROR:
        return "Could not reallocate memory: realloc returned NULL";
#ifdef _WIN32
    case CLIB_ERRNO_SOCKET_WSASYSNOTREADY:
        return "The underlying network subsystem is not ready for network "
               "communication.";
    case CLIB_ERRNO_SOCKET_WSAVERNOTSUPPORTED:
        return "The version of Windows Sockets support requested is not "
               "provided by this particular Windows Sockets implementation.";
    case CLIB_ERRNO_SOCKET_WSAEINPROGRESS:
        return "A blocking Windows Sockets 1.1 operation is in progress.";
    case CLIB_ERRNO_SOCKET_WSAEPROCLIM:
        return "A limit on the number of tasks supported by the Windows "
               "Sockets implementation has been reached.";
    case CLIB_ERRNO_SOCKET_WSAEFAULT:
        return "The lpWSAData parameter is not a valid pointer. (This error "
               "should not happen !PLEASE OPEN AN ISSUE!)";
#endif
    case CLIB_ERRNO_STACK_EMPTY:
        return "Stack is empty";
    case CLIB_ERRNO_STRING_INVALID_BASE:
        return "Invalid base for integer conversion";
    case CLIB_ERRNO_TREE_EMPTY:
        return "No element in tree";
    default:
        return "Invalid error code";
    }
}
