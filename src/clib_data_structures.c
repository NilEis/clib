#include "clib_data_structures.h"
#include "clib_error.h"
#include "clib_math.h"
#include "clib_string.h"
#include <stdlib.h>
#include <string.h>

const char *clib_data_structures_module_name (void)
{
    return "clib_data_structures";
}

typedef struct
{
    void *data;
    int32_t key;
    void *self;
} clib_tree_node_t;

typedef int (*clib_compare_function_t) (int32_t node_a, int32_t node_b);

struct clib_internal_tree
{
    /* pointer to internal array */
    clib_tree_node_t *array;
    /* number of elements in heap */
    size_t size;
    /* size of internal array */
    size_t length;
};

#define CLIB_NUMBER_MAX_LENGTH_AS_STRING 12

static char *clib_tree_get_string (clib_tree_t *tree)
{
#if !defined(CLIB_INCLUDE_MATH) && !defined(CLIB_INCLUDE_STRING)
    return "[CLIB_MATH AND CLIB_STRING REQUIRED]";
#endif
    size_t index = 0;
    size_t size_of_string = sizeof ("[  ]");
    char *ret = NULL;
    char tmp[CLIB_NUMBER_MAX_LENGTH_AS_STRING] = { 0 };
    size_of_string += clib_math_int_width (
        tree->array[0].key, CLIB_RADIX_DEC); /* "num" */
    for (index = 1; index < tree->size - 1; index++)
    {
        size_of_string
            += clib_math_int_width (tree->array[index].key, CLIB_RADIX_DEC)
             + 2; /* "num, " */
    }
    if (tree->size >= 3)
    {
        size_of_string += clib_math_int_width (
            tree->array[tree->size - 1].key, CLIB_RADIX_DEC); /* "num" */
    }
    ret = calloc (size_of_string, sizeof (char));
    if (ret == NULL)
    {
        clib_errno = CLIB_ERRNO_ALLOCATION_ZEROED_ERROR;
        return NULL;
    }
    ret[0] = '[';
    ret[1] = ' ';
    clib_string_from_int (tmp, tree->array[0].key, CLIB_RADIX_DEC);
    strcat (ret, tmp);
    strcat (ret, ", ");
    for (index = 1; index < tree->size - 1; index++)
    {
        clib_string_from_int (tmp, tree->array[index].key, CLIB_RADIX_DEC);
        strcat (ret, tmp);
        strcat (ret, ", ");
    }
    clib_string_from_int (
        tmp, tree->array[tree->size - 1].key, CLIB_RADIX_DEC);
    strcat (ret, tmp);
    strcat (ret, " ]");
    return ret;
}

inline size_t internal_get_parent (size_t index) { return (index - 1) / 2; }

inline size_t internal_get_left (size_t index) { return 2 * index + 1; }

inline size_t internal_get_right (size_t index) { return 2 * index + 2; }

inline int internal_node_is_valid (clib_tree_t *tree, size_t index)
{
    return (index < tree->size)
        && (&(tree->array[index]) == tree->array[index].self);
}

inline void internal_swap (
    clib_tree_t *tree, size_t node_a, size_t node_b, int a_valid, int b_valid)
{
    clib_tree_node_t tmp;

    tmp.data = tree->array[node_a].data;
    tmp.key = tree->array[node_a].key;
    tmp.self = tree->array[node_a].self;

    tree->array[node_a].data = tree->array[node_b].data;
    tree->array[node_a].key = tree->array[node_b].key;
    tree->array[node_a].self = a_valid ? &(tree->array[node_a]) : NULL;

    tree->array[node_b].data = tmp.data;
    tree->array[node_b].key = tmp.key;
    tree->array[node_b].self = b_valid ? &(tree->array[node_b]) : NULL;
}

/* #pragma region binary_heap */

static int internal_max_heap_cmp (int32_t node_a, int32_t node_b)
{
    return node_a > node_b;
}
static int internal_min_heap_cmp (int32_t node_a, int32_t node_b)
{
    return node_a < node_b;
}

struct clib_internal_binary_heap
{
    clib_tree_t tree;
    /* min or max heap */
    clib_binary_heap_type_t type;
    /* pointer to the compare function */
    clib_compare_function_t cmp;
};

clib_binary_heap_t *clib_binary_heap_create (
    clib_binary_heap_type_t type, size_t initial_length)
{
    clib_binary_heap_t *ret = calloc (1, sizeof (clib_binary_heap_t));
    if (ret == NULL)
    {
        clib_errno = CLIB_ERRNO_ALLOCATION_ZEROED_ERROR;
        return NULL;
    }
    ret->tree.array = calloc (initial_length, sizeof (clib_binary_heap_t));
    if (ret->tree.array == NULL)
    {
        clib_errno = CLIB_ERRNO_ALLOCATION_ZEROED_ERROR;
        return NULL;
    }
    ret->tree.length = initial_length;
    ret->tree.size = 0;
    ret->type = type;
    ret->cmp = type == CLIB_MAX_HEAP ? internal_max_heap_cmp
                                     : internal_min_heap_cmp;
    return ret;
}

int clib_binary_heap_is_empty (clib_binary_heap_t *heap)
{
    return heap->tree.size > 0;
}

clib_binary_heap_t *clib_binary_heap_insert (
    clib_binary_heap_t *heap, int32_t key, void *data)
{
    size_t index = 0;
    if (heap->tree.length == heap->tree.size)
    {
        heap->tree.length *= 2;
    }
    heap->tree.size++;
    index = heap->tree.size - 1;
    heap->tree.array[index].data = data;
    heap->tree.array[index].key = key;
    heap->tree.array[index].self = &(heap->tree.array[index]);
    while (index != 0
           && !heap->cmp (heap->tree.array[internal_get_parent (index)].key,
               heap->tree.array[index].key))
    {
        internal_swap (
            &(heap->tree), index, internal_get_parent (index), 1, 1);
        index = internal_get_parent (index);
    }
    return heap;
}

void clib_binary_heap_heapify (clib_binary_heap_t *heap, size_t index)
{
    size_t left = internal_get_left (index);
    size_t right = internal_get_right (index);
    int left_valid = internal_node_is_valid (&(heap->tree), left);
    int right_valid = internal_node_is_valid (&(heap->tree), right);
    size_t min_or_max = 0;
    if (!left_valid && !right_valid)
    {
        return;
    }
    if (right_valid)
    {
        min_or_max = right;
        if (left_valid
            && heap->cmp (
                heap->tree.array[left].key, heap->tree.array[right].key))
        {
            min_or_max = left;
        }
    }
    else
    {
        min_or_max = left;
    }
    if (!heap->cmp (
            heap->tree.array[index].key, heap->tree.array[min_or_max].key))
    {
        internal_swap (&(heap->tree), index, min_or_max, 1, 1);
        clib_binary_heap_heapify (heap, min_or_max);
    }
}

void *clib_binary_heap_get_first (clib_binary_heap_t *heap, int32_t *key)
{
    if (heap->tree.size == 0)
    {
        clib_errno = CLIB_ERRNO_TREE_EMPTY;
        return NULL;
    }
    if (key != NULL)
    {
        *key = heap->tree.array[0].key;
    }
    return heap->tree.array[0].data;
}

void *clib_binary_heap_drop_first (clib_binary_heap_t *heap, int32_t *key)
{
    if (heap->tree.size == 0)
    {
        clib_errno = CLIB_ERRNO_TREE_EMPTY;
        return NULL;
    }
    if (key != NULL)
    {
        *key = heap->tree.array[0].key;
    }
    heap->tree.array[0].key = 0;
    heap->tree.array[0].self = NULL;
    if (heap->tree.size > 1)
    {
        internal_swap (&(heap->tree), 0, heap->tree.size - 1, 1, 0);
        clib_binary_heap_heapify (heap, 0);
    }
    heap->tree.size -= 1;
    return heap->tree.array[0].data;
}

void *clib_binary_heap_drop_and_insert (
    clib_binary_heap_t *heap, int32_t *old_key, int32_t key, void *data)
{
    void *ret = heap->tree.array[0].data;
    int32_t o_key = heap->tree.array[0].key;
    if (old_key != NULL)
    {
        *old_key = o_key;
    }
    heap->tree.array[0].data = data;
    heap->tree.array[0].key = key;
    if (!heap->cmp (key, o_key))
    {
        clib_binary_heap_heapify (heap, 0);
    }
    return ret;
}

/* todo: there has to be a better/cleaner solution */
char *clib_binary_heap_get_as_string (clib_binary_heap_t *heap)
{
    clib_tree_t *tree = &(heap->tree);
    return clib_tree_get_string (tree);
}

void clib_binary_heap_free (clib_binary_heap_t *heap)
{
    free (heap->tree.array);
    free (heap);
}

/* #pragma endregion binary_heap */
