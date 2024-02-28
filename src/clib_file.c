#include "clib_file.h"
#include <stdlib.h>

const char *clib_file_module_name(void)
{
    return "clib_file";
}

#ifdef CLIB_INCLUDE_FILE

static void *clib_file_load_from_file(FILE *file, size_t size, size_t type_size);

size_t clib_file_get_size(FILE *file)
{
    size_t res;
    size_t p = (size_t)ftell(file);
    (void)fseek(file, 0, SEEK_END);
    res = (size_t)ftell(file);
    (void)fseek(file, (long)p, SEEK_SET);
    return (size_t)res;
}

uint8_t *clib_file_load(const char *path)
{
    FILE *f = fopen(path, "rb");
    uint8_t *res = clib_file_get_content(f);
    fclose(f);
    return res;
}

static void *clib_file_load_from_file(FILE *file, size_t size, size_t type_size)
{
    void *res = calloc(size + 1, type_size);
    if (fread(res, type_size, (unsigned)size, file) == 0)
    {
        free(res);
        return NULL;
    }
    return res;
}

uint8_t *clib_file_get_content(FILE *file)
{
    size_t size = clib_file_get_size(file);
    uint8_t *res = clib_file_load_from_file(file, size, sizeof(uint8_t));
    return res;
}

char *clib_file_get_content_str(FILE *file)
{
    size_t size = clib_file_get_size(file);
    char *res = clib_file_load_from_file(file, size, sizeof(char));
    return res;
}

char *clib_file_load_str(const char *path)
{
    FILE *f = fopen(path, "r");
    size_t size = clib_file_get_size(f);
    char *res = clib_file_load_from_file(f, size, sizeof(char));
    fclose(f);
    return res;
}

#endif /* CLIB_INCLUDE_FILE */