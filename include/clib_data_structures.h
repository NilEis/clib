#ifndef CLIB_DATA_STRUCTURES_H
#define CLIB_DATA_STRUCTURES_H

#include "clib_c90_support.h"
#include <stddef.h>
#include <stdint.h>

typedef enum
{
    CLIB_MIN_HEAP,
    CLIB_MAX_HEAP
} clib_binary_heap_type_t;

typedef struct clib_binary_heap *clib_binary_heap_handle_t;

/**
 * @brief creates a binary heap of the given type and size
 * 
 * @param type CLIB_MIN_HEAP|CLIB_MAX_HEAP
 * @param initial_length the initial size of the internal array
 * @return clib_binary_heap_handle_t a pointer to the allocated heap
 */
clib_binary_heap_handle_t clib_create_binary_heap(clib_binary_heap_type_t type, size_t initial_length);

/**
 * @brief frees the given heap
 * 
 * @param heap 
 */
void clib_free_binary_heap(clib_binary_heap_handle_t heap);

#endif /* CLIB_DATA_STRUCTURES_H */
