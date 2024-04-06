/**
 * @file clib_array.h
 * @author Nils Eisenach
 * @brief Functions for working with dynamic arrays
 * @version 0.1
 * @date 2024-04-05
 */
#if !defined(CLIB_ARRAY_H) && defined(CLIB_INCLUDE_ARRAY)
#define CLIB_ARRAY_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "clib_c90_support.h"
#include <stddef.h>

typedef struct clib_internal_array clib_array_t;

/**
 * @brief creates a new array
 *
 * @param type_size the size of the type that the array will hold
 * @param initial_size the initial size of the array
 * @return clib_array_t* a pointer to the array
 */
clib_array_t *clib_array_create (size_t type_size, size_t initial_size);

/**
 * @brief copies the data from src pushes/appends to the array
 *
 * @param array
 * @param src
 * @return clib_array_t* the array
 */
clib_array_t *clib_array_push (clib_array_t *array, const void *src);

/**
 * @brief gets the element at the given index and copies it to dest
 *
 * @param array
 * @param index
 * @param dest
 * @return clib_array_t* the array
 */
clib_array_t *clib_array_get (clib_array_t *array, size_t index, void *dest);

/**
 * @brief pops the last element from the array and copies it to dest
 *
 * @param array
 * @param dest
 * @return clib_array_t* the array
 */
clib_array_t *clib_array_pop (clib_array_t *array, void *dest);

/**
 * @brief returns a pointer to a copy of the array
 *
 * @param array
 * @return void* a pointer to the array
 */
void *clib_array_get_array (clib_array_t *array);

/**
 * @brief frees the array
 *
 * @param array
 */
void clib_array_free (clib_array_t *array);

/**
 * @brief returns the length of the array
 *
 * @param array
 * @return size_t the length of the array
 */
size_t clib_array_length (clib_array_t *array);

#ifdef __cplusplus
}
#endif

#endif /* CLIB_ARRAY_H */
