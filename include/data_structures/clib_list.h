/** @file
 * @brief provides types and functions for lists
 */
#if !defined(CLIB_LIST_H) && defined(CLIB_INCLUDE_DATA_STRUCTURES)
#define CLIB_LIST_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "../clib_c90_support.h"
#include <stddef.h>

/**
 * @brief typedef for linked list
 *
 */
typedef struct clib_internal_list clib_list_t;

/**
 * @brief typedef for list members
 *
 */
typedef struct clib_internal_list_node clib_list_node_t;

/**
 * @brief creates a new list
 *
 * @return clib_list_t*
 */
clib_list_t *clib_list_create (void);

/**
 * @brief tests if a list is empty
 *
 * @param list
 * @return int 0 if false, !=0 if true
 */
int clib_list_is_empty (clib_list_t *list);

/**
 * @brief steps to the next element
 *
 * @param list
 * @return int !=0 if success, 0 if no element is found
 */
int clib_list_next (clib_list_t *list);

/**
 * @brief returns the size of the list
 *
 * @param list
 * @return size_t
 */
size_t clib_list_size (clib_list_t *list);

/**
 * @brief prepend data to a given node
 *
 * @param list
 * @param data
 * @returns 0 on error != 0 on success
 */
int clib_list_prepend (clib_list_t *list, void *data);

/**
 * @brief inserts data to the given list
 *
 * @param list
 * @param data
 * @returns 0 on error != 0 on success
 */
int clib_list_insert (clib_list_t *list, void *data);

/**
 * @brief inserts data to the given list at the front
 *
 * @param list
 * @param data
 * @returns 0 on error != 0 on success
 */
int clib_list_insert_front (clib_list_t *list, void *data);

/**
 * @brief inserts data at the end of the given list
 *
 * @param list
 * @param data
 * @returns 0 on error != 0 on success
 */
int clib_list_insert_back (clib_list_t *list, void *data);

/**
 * @brief returns the data of the current list element
 *
 * @param list
 * @return void*
 */
void *clib_list_get (clib_list_t *list);

/**
 * @brief returns the current node
 *
 * @param list
 * @return clib_list_node_t*
 */
clib_list_node_t *clib_list_get_node (clib_list_t *list);

/**
 * @brief removes the given node from the given list
 *
 * @param list
 * @param node
 * @return void* the data associated with the node
 */
void *clib_list_remove (clib_list_t *list, clib_list_node_t *node);

/**
 * @brief frees all memory associated with the list
 *
 * @param list
 */
void clib_list_free (clib_list_t *list);

#ifdef __cplusplus
}
#endif

#endif /* CLIB_LIST_H */
