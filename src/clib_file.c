#include "clib_file.h"
#include <stdlib.h>
#ifdef CLIB_INCLUDE_FILE
#ifdef CLIB_FILE_SELECTOR
#include "nfd.h"
#endif /* CLIB_FILE_SELECTOR */

size_t clib_file_get_size(FILE *file)
{
    size_t res;
    size_t p = (size_t)ftell(file);
    fseek(file, 0, SEEK_END);
    res = (size_t)ftell(file);
    fseek(file, p, SEEK_SET);
    return (size_t)res;
}

const char *clib_file_load(const char *path)
{
    FILE *f = fopen(path, "r");
    size_t size = clib_file_get_size(f);
    char *res = calloc(size + 1, sizeof(char));
    (void)fread(res, sizeof(char), size, f);
    fclose(f);
    return (const char *)res;
}

#endif /* CLIB_INCLUDE_FILE */
