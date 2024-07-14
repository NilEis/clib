#ifndef CLIB_DATA_STRUCTURES_TREE_H
#define CLIB_DATA_STRUCTURES_TREE_H
#include "clib_c90_support.h"
#include "clib_data_structures.h"
#include "clib_string.h"

typedef struct
{
    void *data;
    int32_t key;
    void *self;
} clib_tree_node_t;

struct clib_internal_tree
{
    clib_data_structure_header_t header;
    /* pointer to internal array */
    clib_tree_node_t *array;
    /* number of elements in heap */
    size_t size;
    /* size of internal array */
    size_t length;
};

char *clib_tree_get_string (const clib_tree_t *tree);

size_t internal_get_parent (size_t index);

size_t internal_get_left (size_t index);

size_t internal_get_right (size_t index);

int internal_node_is_valid (const clib_tree_t *tree, size_t index);

void internal_swap (const clib_tree_t *tree, size_t node_a, size_t node_b, int a_valid, int b_valid);

#endif /* CLIB_DATA_STRUCTURES_TREE_H */
