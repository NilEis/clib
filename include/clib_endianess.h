/**
 * @file clib_endianess.h
 * @brief functions for working with the CPUs endianess
 */
#if !defined(CLIB_ENDIANESS_H) && defined(CLIB_INCLUDE_ENDIANESS)
#define CLIB_ENDIANESS_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "clib_c90_support.h"

/**
 * @brief typedef for the 4 endian types
 * 
 */
typedef enum
{
    CLIB_ENDIAN_UNKNOWN,
    CLIB_ENDIAN_BIG,
    CLIB_ENDIAN_LITTLE,
    CLIB_ENDIAN_BIG_WORD,
    CLIB_ENDIAN_LITTLE_WORD,
} clib_endianess_t;

/**
 * @brief Detects the endianess of the cpu
 * 
 * @return clib_endianess_t 
 */
clib_endianess_t clib_endianess_detect(void);

#ifdef __cplusplus
}
#endif

#endif /* CLIB_ENDIANESS_H */
