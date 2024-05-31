/** @file
 * @brief Functions for interacting with vectors
 */
#if !defined(CLIB_VECTOR_H) && defined(CLIB_INCLUDE_VECTOR)
#define CLIB_VECTOR_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "clib_c90_support.h"
#include <stddef.h>
#include <stdint.h>

/**
 * @brief Type for vectors
 *
 */
typedef struct
{
    double x; /**< x value */
    double y; /**< y value */
    double z; /**< z value */
} clib_vector_t;

/**
 * @brief creates a new vector
 *
 * @param x initial x value
 * @param y initial y value
 * @param z initial z value
 * @param vector if null a new vector will be allocated
 * @return clib_vector_t*
 */
clib_vector_t *clib_vector_create (
    double x, double y, double z, clib_vector_t *vector);

/**
 * @brief adds two vectors
 *
 * @param a
 * @param b
 * @param result can be the same as a or b
 * @return clib_vector_t*
 */
#ifdef CLIB_USE_OPENMP
#pragma omp declare simd
#endif
clib_vector_t *clib_vector_add (
    clib_vector_t *a, clib_vector_t *b, clib_vector_t *result);

/**
 * @brief subtracts two vectors
 *
 * @param a
 * @param b
 * @param result can be the same as a or b
 * @return clib_vector_t*
 */
#ifdef CLIB_USE_OPENMP
#pragma omp declare simd
#endif
clib_vector_t *clib_vector_sub (
    clib_vector_t *a, clib_vector_t *b, clib_vector_t *result);

/**
 * @brief multiplies two vectors
 *
 * @param a
 * @param b
 * @param result can be the same as a or b
 * @return clib_vector_t*
 */
#ifdef CLIB_USE_OPENMP
#pragma omp declare simd
#endif
clib_vector_t *clib_vector_mul (
    clib_vector_t *a, clib_vector_t *b, clib_vector_t *result);

/**
 * @brief frees a vector
 *
 * @param vector
 */
void clib_vector_free (clib_vector_t *vector);

#ifdef __cplusplus
}
#endif

#endif /* CLIB_VECTOR_H */
