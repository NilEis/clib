#include "clib_data_structures.h"
#include <stdlib.h>
#include <string.h>
#include "clib_error.h"
#include "clib_math.h"
#include "clib_string.h"

typedef struct
{
    void *data;
    int32_t key;
    void *self;
} clib_binary_heap_node_t;

typedef int (*clib_compare_function_t)(int32_t a, int32_t b);

struct clib_binary_heap
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
};

inline size_t __get_parent(size_t i)
{
    return (i - 1) / 2;
}

inline size_t __get_left(size_t i)
{
    return 2 * i + 1;
}

inline size_t __get_right(size_t i)
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

inline int __node_is_valid(clib_binary_heap_t *heap, size_t i)
{
    return (i < heap->size) && (&(heap->heap[i]) == heap->heap[i].self);
}

inline void __swap(clib_binary_heap_t *heap, size_t a, size_t b, int a_valid, int b_valid)
{
    clib_binary_heap_node_t tmp;

    tmp.data = heap->heap[a].data;
    tmp.key = heap->heap[a].key;
    tmp.self = heap->heap[a].self;

    heap->heap[a].data = heap->heap[b].data;
    heap->heap[a].key = heap->heap[b].key;
    heap->heap[a].self = a_valid ? &(heap->heap[a]) : NULL;

    heap->heap[b].data = tmp.data;
    heap->heap[b].key = tmp.key;
    heap->heap[b].self = b_valid ? &(heap->heap[b]) : NULL;
}

clib_binary_heap_t *clib_binary_heap_create(clib_binary_heap_type_t type, size_t initial_length)
{
    clib_binary_heap_t *ret = calloc(1, sizeof(clib_binary_heap_t));
    ret->heap = calloc(initial_length, sizeof(clib_binary_heap_t));
    if (ret->heap == NULL)
    {
        clib_errno = CLIB_ERRNO_ALLOCATION_ZEROED_ERROR;
        return NULL;
    }
    ret->length = initial_length;
    ret->size = 0;
    ret->type = type;
    ret->cmp = type == CLIB_MAX_HEAP ? __max_heap_cmp : __min_heap_cmp;
    return ret;
}

int clib_binary_heap_is_empty(clib_binary_heap_t *heap)
{
    return heap->size > 0;
}

clib_binary_heap_t *clib_binary_heap_insert(clib_binary_heap_t *heap, int32_t key, void *data)
{
    size_t i = 0;
    if (heap->length == heap->size)
    {
        heap->length *= 2;
    }
    heap->size++;
    i = heap->size - 1;
    heap->heap[i].data = data;
    heap->heap[i].key = key;
    heap->heap[i].self = &(heap->heap[i]);
    while (i != 0 && !heap->cmp(heap->heap[__get_parent(i)].key, heap->heap[i].key))
    {
        __swap(heap, i, __get_parent(i), 1, 1);
        i = __get_parent(i);
    }
    return heap;
}

void clib_binary_heap_heapify(clib_binary_heap_t *heap, size_t index)
{
    size_t left = __get_left(index);
    size_t right = __get_right(index);
    int left_valid = __node_is_valid(heap, left);
    int right_valid = __node_is_valid(heap, right);
    size_t min_or_max = 0;
    if (!left_valid && !right_valid)
    {
        return;
    }
    if (right_valid)
    {
        min_or_max = right;
        if (left_valid && heap->cmp(heap->heap[left].key, heap->heap[right].key))
        {
            min_or_max = left;
        }
    }
    else
    {
        min_or_max = left;
    }
    if (!heap->cmp(heap->heap[index].key, heap->heap[min_or_max].key))
    {
        __swap(heap, index, min_or_max, 1, 1);
        clib_binary_heap_heapify(heap, min_or_max);
    }
}

void *clib_binary_heap_get_first(clib_binary_heap_t *heap, int32_t *key)
{
    if (heap->size == 0)
    {
        clib_errno = CLIB_ERRNO_TREE_EMPTY;
        return NULL;
    }
    if (key != NULL)
    {
        *key = heap->heap[0].key;
    }
    return heap->heap[0].data;
}

void *clib_binary_heap_drop_first(clib_binary_heap_t *heap, int32_t *key)
{
    if (heap->size == 0)
    {
        clib_errno = CLIB_ERRNO_TREE_EMPTY;
        return NULL;
    }
    if (key != NULL)
    {
        *key = heap->heap[0].key;
    }
    heap->heap[0].key = 0;
    heap->heap[0].self = NULL;
    if (heap->size > 1)
    {
        __swap(heap, 0, heap->size - 1, 1, 0);
        clib_binary_heap_heapify(heap, 0);
    }
    heap->size -= 1;
    return heap->heap[0].data;
}

void *clib_binary_heap_drop_and_insert(clib_binary_heap_t *heap, int32_t *old_key, int32_t key, void *data)
{
    void *ret = heap->heap[0].data;
    *old_key = heap->heap[0].key;
    heap->heap[0].data = data;
    heap->heap[0].key = key;
    if (heap->cmp(key, *old_key))
    {
        clib_binary_heap_heapify(heap, 0);
    }
    return ret;
}

/* todo: there has to be a better/cleaner solution */
char *clib_binary_heap_get_as_string(clib_binary_heap_t *heap)
{
    size_t i = 0;
    size_t size_of_string = 5; /* "[  ]\0" */
    char *ret = NULL;
    char tmp[12] = {0};
    size_of_string += clib_math_int_width(heap->heap[0].key, CLIB_RADIX_DEC); /* "num" */
    for (i = 1; i < heap->size - 1; i++)
    {
        size_of_string += clib_math_int_width(heap->heap[i].key, CLIB_RADIX_DEC) + 2; /* "num, " */
    }
    if (heap->size >= 3)
    {
        size_of_string += clib_math_int_width(heap->heap[heap->size - 1].key, CLIB_RADIX_DEC); /* "num" */
    }
    ret = calloc(size_of_string, sizeof(char));
    ret[0] = '[';
    ret[1] = ' ';
    clib_string_from_int(tmp, heap->heap[0].key, CLIB_RADIX_DEC);
    strcat(ret, tmp);
    strcat(ret, ", ");
    for (i = 1; i < heap->size - 1; i++)
    {
        clib_string_from_int(tmp, heap->heap[i].key, CLIB_RADIX_DEC);
        strcat(ret, tmp);
        strcat(ret, ", ");
    }
    clib_string_from_int(tmp, heap->heap[heap->size - 1].key, CLIB_RADIX_DEC);
    strcat(ret, tmp);
    strcat(ret, " ]");
    return ret;
}

void clib_binary_heap_free(clib_binary_heap_t *heap)
{
    free(heap->heap);
    free(heap);
}