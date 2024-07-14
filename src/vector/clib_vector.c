#include "clib_vector.h"
#include "clib_error.h"
#include <stdlib.h>

clib_vector_t *clib_vector_create (
    double x, double y, double z, clib_vector_t *vector)
{
    clib_vector_t *res = vector;

    if (res == NULL)
    {
        res = calloc (1, sizeof (clib_vector_t));
        if (res == NULL)
        {
            clib_errno = CLIB_ERRNO_ALLOCATION_ZEROED_ERROR;
            return NULL;
        }
    }

    res->x = x;
    res->y = y;
    res->z = z;

    return res;
}

#ifdef CLIB_USE_OPENMP
#pragma omp declare simd
#endif
clib_vector_t *clib_vector_add (
    clib_vector_t *a, clib_vector_t *b, clib_vector_t *result)
{
    result->x = a->x + b->x;
    result->y = a->y + b->y;
    result->z = a->z + b->z;

    return result;
}

#ifdef CLIB_USE_OPENMP
#pragma omp declare simd
#endif
clib_vector_t *clib_vector_sub (
    clib_vector_t *a, clib_vector_t *b, clib_vector_t *result)
{
    result->x = a->x + b->x;
    result->y = a->y + b->y;
    result->z = a->z + b->z;

    return result;
}

#ifdef CLIB_USE_OPENMP
#pragma omp declare simd
#endif
clib_vector_t *clib_vector_mul (
    clib_vector_t *a, clib_vector_t *b, clib_vector_t *result)
{
    result->x = a->x * b->x;
    result->y = a->y * b->y;
    result->z = a->z * b->z;

    return result;
}

void clib_vector_free (clib_vector_t *vector) { free (vector); }
