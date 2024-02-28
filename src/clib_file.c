#include "clib_file.h"
#include "clib_string.h"
#include "clib_error.h"
#include "clib_array.h"
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
    uint8_t *res;
    if (f == NULL)
    {
        clib_errno = CLIB_ERRNO_FILE_OPEN_ERROR;
        return NULL;
    }
    res = clib_file_get_content(f);
    fclose(f);
    return res;
}

static void *clib_file_load_from_file(FILE *file, size_t size, size_t type_size)
{
    void *res = calloc(size + 1, type_size);
    if (res == NULL)
    {
        clib_errno = CLIB_ERRNO_ALLOCATION_ZEROED_ERROR;
        return NULL;
    }
    if (fread(res, type_size, (unsigned)size, file) == 0)
    {
        clib_errno = CLIB_ERRNO_FILE_READ_ERROR;
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

char *clib_file_load_till_eof_str(FILE *file)
{
#ifdef CLIB_INCLUDE_STRING
    int c;
    char *res = NULL;
    clib_string_builder_t *builder = clib_string_builder_create(64);
    while ((c = getc(file)) != EOF)
    {
        clib_string_builder_append_char(builder, (char)c);
    }
    res = clib_string_builder_get_string(builder);
    clib_string_builder_free(builder);
    return res;
#else
#warning "clib_file_load_till_eof_str is not implemented because clib_string is not included"
    (void)file;
    return NULL;
#endif
}

uint8_t *clib_file_load_till_eof(FILE *file)
{
#ifdef CLIB_INCLUDE_STRING
    int c;
    uint8_t c_byte = 0;
    uint8_t *res = NULL;
    clib_array_t *builder = clib_array_create(sizeof(uint8_t), 64);
    while ((c = getc(file)) != EOF)
    {
        c_byte = (uint8_t)c;
        clib_array_push(builder, &c_byte);
    }
    res = clib_array_get_array(builder);
    clib_array_free(builder);
    return res;
#else
#warning "clib_file_load_till_eof is not implemented because clib_array is not included"
    (void)file;
    return NULL;
#endif
}

char *clib_file_load_str(const char *path)
{
    FILE *f = fopen(path, "r");
    size_t size;
    char *res;
    if (f == NULL)
    {
        clib_errno = CLIB_ERRNO_FILE_OPEN_ERROR;
        return NULL;
    }
    size = clib_file_get_size(f);
    res = clib_file_load_from_file(f, size, sizeof(char));
    fclose(f);
    return res;
}

#endif /* CLIB_INCLUDE_FILE */