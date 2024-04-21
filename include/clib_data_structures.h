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
#include "data_structures/clib_binary_heap.h"
#include "data_structures/clib_list.h"
#include "data_structures/clib_set.h"
#include <stddef.h>
#include <stdint.h>

/**
 * @brief typedef for a clib_tree type
 *
 */
typedef struct clib_internal_tree clib_tree_t;

#ifdef __cplusplus
}
#endif

#endif /* CLIB_DATA_STRUCTURES_H */
