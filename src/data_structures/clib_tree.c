#include "clib_tree.h"
#include "clib_error.h"
#include "clib_math.h"
#include <stdlib.h>
#include <string.h>

typedef int (*clib_compare_function_t) (int32_t node_a, int32_t node_b);

#define CLIB_NUMBER_MAX_LENGTH_AS_STRING 12

char *clib_tree_get_string (const clib_tree_t *tree)
{
#if !defined(CLIB_INCLUDE_MATH) && !defined(CLIB_INCLUDE_STRING)
    return "[CLIB_MATH AND CLIB_STRING REQUIRED]";
#else
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
#endif
}

size_t internal_get_parent (const size_t index) { return (index - 1) / 2; }

size_t internal_get_left (const size_t index) { return 2 * index + 1; }

size_t internal_get_right (const size_t index) { return 2 * index + 2; }

int internal_node_is_valid (const clib_tree_t *tree, const size_t index)
{
    return (index < tree->size)
        && (&(tree->array[index]) == tree->array[index].self);
}

void internal_swap (const clib_tree_t *tree,
    const size_t node_a,
    const size_t node_b,
    const int a_valid,
    const int b_valid)
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
