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

typedef struct clib_binary_heap clib_binary_heap_t;

/**
 * @brief creates a binary heap of the given type and size
 *
 * @param type CLIB_MIN_HEAP|CLIB_MAX_HEAP
 * @param initial_length the initial size of the internal array
 * @return clib_binary_heap_t* a pointer to the allocated heap
 */
clib_binary_heap_t *clib_binary_heap_create(clib_binary_heap_type_t type, size_t initial_length);

/**
 * @brief returns true if empty
 *
 * @param heap the heap
 * @return int zero if false, otherwise not zero
 */
int clib_binary_heap_is_empty(clib_binary_heap_t *heap);

/**
 * @brief inserts the given data into the heap, using the key for sorting
 *
 * @param heap the heap
 * @param key key
 * @param data a pointer to the data
 * @return clib_binary_heap_t* a pointer to the heap
 */
clib_binary_heap_t *clib_binary_heap_insert(clib_binary_heap_t *heap, int32_t key, void *data);

/**
 * @brief Heapifys the heap
 *
 * @param heap the heap
 * @param index the index of the root node (default is 0)
 */
void clib_binary_heap_heapify(clib_binary_heap_t *heap, size_t index);

/**
 * @brief Returns the data in the first element
 *
 * @param heap the heap
 * @param key if not NULL, a pointer to a variable that will be updated with the key value
 * @return void* the pointer stored in the node
 */
void *clib_binary_heap_get_first(clib_binary_heap_t *heap, int32_t *key);

/**
 * @brief Returns the data in the first element and removes it from the heap
 *
 * @param heap the heap
 * @param key if not NULL, a pointer to a variable that will be updated with the key value
 * @return void* the pointer stored in the node
 */
void *clib_binary_heap_drop_first(clib_binary_heap_t *heap, int32_t *key);

/**
 * @brief Returns the first element and inserts a new element
 * 
 * @param heap the heap
 * @param old_key if not NULL, a pointer to a variable that will be updated with the key value
 * @param key the key of the new element to be inserted
 * @param data the data of the new element
 * @return void* the pointer stored in the node
 */
void *clib_binary_heap_drop_and_insert(clib_binary_heap_t *heap, int32_t *old_key, int32_t key, void *data);

/**
 * @brief returns a stringified version of the heap in the format [ KEY1, KEY2, ..., KEYN ]
 *
 * @param heap the heap
 * @return char* a pointer to the string (has to be free'd by the caller)
 */
char *clib_binary_heap_get_as_string(clib_binary_heap_t *heap);

/**
 * @brief frees the given heap
 *
 * @param heap the heap
 */
void clib_binary_heap_free(clib_binary_heap_t *heap);

#endif /* CLIB_DATA_STRUCTURES_H */
