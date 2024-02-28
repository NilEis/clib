#include "clib_file.h"

const char *clib_file_selector_module_name(void)
{
    return "clib_file_selector";
}

#ifdef CLIB_FILE_SELECTOR
#include "nfd.h"
#ifdef CLIB_INCLUDE_STRING
#include "clib_string.h"
#include "clib_error.h"
#endif /* CLIB_INCLUDE_STRING */

char *clib_file_selector_open_file(void)
{
#ifdef CLIB_INCLUDE_STRING
    nfdchar_t *outPath = NULL;
    nfdresult_t result = NFD_OpenDialog(&outPath, NULL, 0, NULL);
    switch (result)
    {
    case NFD_OKAY:
    {
        char *res = clib_string_duplicate(outPath);
        NFD_FreePath(outPath);
        return res;
    }
    case NFD_CANCEL:
        clib_errno = CLIB_ERRNO_FILE_SELECTOR_CANCEL;
        return NULL;
    case NFD_ERROR:
        clib_errno = CLIB_ERRNO_FILE_SELECTOR_ERROR;
        return NULL;
    }

#else
#warning "clib_file_selector needs the string module to work"
#endif /* CLIB_INCLUDE_STRING */
    return NULL;
}

#endif /* CLIB_FILE_SELECTOR */