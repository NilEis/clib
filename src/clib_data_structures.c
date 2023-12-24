#include "clib_data_structures.h"
#include <stdlib.h>
#include "clib_error.h"

typedef struct
{
    void *data;
    int32_t key;
    void *__valid;
} clib_binary_heap_node_t;

typedef int (*clib_compare_function_t)(int32_t a, int32_t b);

typedef struct clib_binary_heap
{
    /* pointer to internal array */
    clib_binary_heap_node_t *heap;
    /* number of elements in heap */
    size_t size;
    /* size of internal array */
    size_t length;
    /* min or max heap */
    clib_binary_heap_type_t type;
    /* pointer to the compare function */
    clib_compare_function_t cmp;
} clib_binary_heap_t;

inline int __get_parent(int i)
{
    return (i - 1) / 2;
}

inline int __get_left(int i)
{
    return 2 * i + 1;
}

inline int __get_right(int i)
{
    return 2 * i + 2;
}

static int __max_heap_cmp(int32_t a, int32_t b)
{
    return a > b;
}
static int __min_heap_cmp(int32_t a, int32_t b)
{
    return a < b;
}

clib_binary_heap_handle_t clib_create_binary_heap(clib_binary_heap_type_t type, size_t initial_length)
{
    clib_binary_heap_handle_t ret = calloc(1, sizeof(clib_binary_heap_t));
    ret->heap = calloc(initial_length, sizeof(clib_binary_heap_node_t));
    if (ret->heap == NULL)
    {
        clib_errno = CLIB_ERRNO_ALLOCATION_ZEROED_ERROR;
        return NULL;
    }
    ret->length = initial_length;
    ret->size = 0;
    ret->type = type;
    ret->cmp = type == CLIB_MAX_HEAP ? __max_heap_cmp : __min_heap_cmp;
    (void)__get_parent(0);
    (void)__get_left(0);
    (void)__get_right(0);
    return ret;
}

void clib_free_binary_heap(clib_binary_heap_handle_t heap)
{
    free(heap->heap);
    free(heap);
}