/** @file
 * @brief provides types and functions for data-structures
 */
#if !defined(CLIB_DATA_STRUCTURES_H) && defined(CLIB_INCLUDE_DATA_STRUCTURES)
#define CLIB_DATA_STRUCTURES_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "clib_c90_support.h"
#include <stddef.h>
#include <stdint.h>

/**
 * @brief set type of binary heap
 *
 */
typedef enum
{
    CLIB_MIN_HEAP,
    CLIB_MAX_HEAP
} clib_binary_heap_type_t;

/**
 * @brief typedef for a clib_tree type
 *
 */
typedef struct clib_internal_tree clib_tree_t;

/**
 * @brief typedef for binary heap
 *
 */
typedef struct clib_internal_binary_heap clib_binary_heap_t;

/**
 * @brief The structure is an element of the union_find
 */
typedef struct clib_internal_union_find clib_union_find_t;

/**
 * @brief creates a binary heap of the given type and size
 *
 * @param type CLIB_MIN_HEAP|CLIB_MAX_HEAP
 * @param initial_length the initial size of the internal array
 * @return clib_binary_heap_t* a pointer to the allocated heap
 */
clib_binary_heap_t *clib_binary_heap_create (
    clib_binary_heap_type_t type, size_t initial_length);

/**
 * @brief returns true if empty
 *
 * @param heap the heap
 * @return int zero if false, otherwise not zero
 */
int clib_binary_heap_is_empty (const clib_binary_heap_t *heap);

/**
 * @brief inserts the given data into the heap, using the key for sorting
 *
 * @param heap the heap
 * @param key key
 * @param data a pointer to the data
 * @return clib_binary_heap_t* a pointer to the heap
 */
clib_binary_heap_t *clib_binary_heap_insert (
    clib_binary_heap_t *heap, int32_t key, void *data);

/**
 * @brief Heapifys the heap
 *
 * @param heap the heap
 * @param index the index of the root node (default is 0)
 */
void clib_binary_heap_heapify (clib_binary_heap_t *heap, size_t index);

/**
 * @brief Returns the data in the first element
 *
 * @param heap the heap
 * @param key if not NULL, a pointer to a variable that will be updated with
 * the key value
 * @return void* the pointer stored in the node
 */
void *clib_binary_heap_get_first (
    const clib_binary_heap_t *heap, int32_t *key);

/**
 * @brief Returns the data in the first element and removes it from the heap
 *
 * @param heap the heap
 * @param key if not NULL, a pointer to a variable that will be updated with
 * the key value
 * @return void* the pointer stored in the node
 */
void *clib_binary_heap_drop_first (clib_binary_heap_t *heap, int32_t *key);

/**
 * @brief Returns the first element and inserts a new element
 *
 * @param heap the heap
 * @param old_key if not NULL, a pointer to a variable that will be updated
 * with the key value
 * @param key the key of the new element to be inserted
 * @param data the data of the new element
 * @return void* the pointer stored in the node
 */
void *clib_binary_heap_drop_and_insert (
    clib_binary_heap_t *heap, int32_t *old_key, int32_t key, void *data);

/**
 * @brief returns a stringified version of the heap in the format [ KEY1, KEY2,
 * ..., KEYN ]
 *
 * @param heap the heap
 * @return char* a pointer to the string (has to be free'd by the caller)
 */
char *clib_binary_heap_get_as_string (const clib_binary_heap_t *heap);

/**
 * @brief frees the given heap
 *
 * @param heap the heap
 */
void clib_binary_heap_free (clib_binary_heap_t *heap);

/**
 * @brief Makes a set for the given element
 *
 * @param elem
 * @return clib_union_find_t*
 */
clib_union_find_t *clib_set_make (void *elem);

/**
 * @brief finds the root of a given element
 *
 * @param elem
 * @return clib_union_find_t*
 */
clib_union_find_t *clib_set_find (clib_union_find_t *elem);

/**
 * @brief merges both given sets and returns the new set
 *
 * @param set_1
 * @param set_2
 * @return clib_union_find_t*
 */
clib_union_find_t *clib_set_merge (
    clib_union_find_t *set_1, clib_union_find_t *set_2);

#ifdef __cplusplus
}
#endif

#endif /* CLIB_DATA_STRUCTURES_H */
