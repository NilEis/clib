/** @file
 * @brief provides types and functions for sets
 */
#if !defined(CLIB_SET_H) && defined(CLIB_INCLUDE_DATA_STRUCTURES)
#define CLIB_SET_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "../clib_c90_support.h"
#include <stddef.h>

/**
 * @brief The structure is an element of the union_find
 */
typedef struct clib_internal_union_find clib_union_find_t;

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

#endif /* CLIB_SET_H */
