#include "clib_array.h"
#include "clib_error.h"
#include "clib_memory.h"
#include <stdlib.h>

const char *clib_array_module_name (void) { return "clib_array"; }

#if defined(CLIB_INCLUDE_ARRAY) && !defined(CLIB_INCLUDE_MEMORY)
#warning "CLIB_INCLUDE_ARRAY requires CLIB_INCLUDE_MEMORY"
#endif

struct clib_internal_array
{
    size_t length;
    size_t buf_size;
    size_t type_size;
    uint8_t *buf;
    void *zero;
};

#define CLIB_ARRAY_DEFAULT_SIZE 8

clib_array_t *clib_array_create (size_t type_size, size_t initial_size)
{
    clib_array_t *ret = NULL;
    initial_size = initial_size != 0 ? initial_size : CLIB_ARRAY_DEFAULT_SIZE;
    ret = calloc (1, sizeof (clib_array_t));
    if (ret == NULL)
    {
        clib_errno = CLIB_ERRNO_ALLOCATION_ZEROED_ERROR;
        return NULL;
    }
    ret->buf = calloc (initial_size, type_size);
    if (ret->buf == NULL)
    {
        free (ret);
        clib_errno = CLIB_ERRNO_ALLOCATION_ZEROED_ERROR;
        return NULL;
    }
    ret->zero = calloc (1, type_size);
    if (ret->buf == NULL)
    {
        free (ret);
        clib_errno = CLIB_ERRNO_ALLOCATION_ZEROED_ERROR;
        return NULL;
    }
    ret->buf_size = initial_size;
    ret->length = 0;
    ret->type_size = type_size;
    return ret;
}

clib_array_t *clib_array_push (clib_array_t *array, const void *src)
{
    size_t array_index = array->length;
    if (array->buf_size <= array_index)
    {
        size_t new_size = array->buf_size <= 1 ? 4 : array->buf_size * 2;
        void *new_buf = realloc (array->buf, new_size);
        if (new_buf == NULL)
        {
            clib_errno = CLIB_ERRNO_REALLOCATION_ERROR;
            return NULL;
        }
        array->buf = new_buf;
        array->buf_size = new_size;
    }
    clib_memory_copy (
        src, array->buf + (array->type_size * array_index), array->type_size);
    array->length++;
    return array;
}

clib_array_t *clib_array_get (clib_array_t *array, size_t index, const void *dest)
{
    if (index >= array->length)
    {
        clib_errno = CLIB_ERRNO_ARRAY_INDEX_OUT_OF_BOUNDS;
        return NULL;
    }
    clib_memory_copy (
        dest, array->buf + (index * array->type_size), array->type_size);
    return array;
}

clib_array_t *clib_array_pop (clib_array_t *array, const void *dest)
{
    clib_memory_copy (dest,
        array->buf + (array->type_size * (array->length - 1)),
        array->type_size);
    return array;
}

void *clib_array_get_array (const clib_array_t *array)
{
    void *ret = calloc (array->length, array->type_size);
    clib_memory_copy (array->buf, ret, array->length * array->type_size);
    return ret;
}

size_t clib_array_length (const clib_array_t *array) { return array->length; }

void clib_array_free (clib_array_t *array)
{
    free (array->buf);
    free (array);
}
