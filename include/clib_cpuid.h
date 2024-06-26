/**
 * @file clib_cpuid.h
 * @author Nils Eisenach
 * @brief Functions for working with cpuid and querying the CPU
 * @date 2024-04-05
 */
#if !defined(CLIB_CPUID_H) && defined(CLIB_INCLUDE_CPUID)
#define CLIB_CPUID_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "clib_c90_support.h"
#include "cpuid/clib_checks.h"
#include "cpuid/clib_leafs.h"
#include <stdint.h>

/**
 * @brief fills the given parameters with the result of cpuid for the given
 * (sub-)leaf
 *
 * @param leaf
 * @param subleaf
 * @param eax
 * @param ebx
 * @param ecx
 * @param edx
 */
void clib_cpuid_raw (uint_least32_t leaf,
    uint_least32_t subleaf,
    uint_least32_t *eax,
    uint_least32_t *ebx,
    uint_least32_t *ecx,
    uint_least32_t *edx);

/**
 * @brief tests if cpuid is supported
 *
 * @return int 0 if not supported, !=0 if supported
 */
int clib_cpuid_is_supported (void);

/**
 * @brief Returns a pointer to the equivilant struct for the query
 * @see clib_cpuid_leafs.h
 *
 * @param leaf
 * @param subleaf
 * @return void*
 */
void *clib_cpuid_get (uint_least32_t leaf, uint_least32_t subleaf);

/**
 * @brief returns the vecndor ID string
 *
 * @return const char*
 */
const char *clib_cpuid_get_name (void);

/**
 * @brief returns the maximum supported standard level
 *
 * @return uint_least32_t
 */
uint_least32_t clib_cpuid_get_max_level (void);

/**
 * @brief returns the hypervisor string or NULL on error (sets errno)
 *
 * @return const char*
 */
const char *clib_cpuid_get_hypervisor (void);

/**
 * @brief gets the cache line size
 *
 * @return System coherency line size
 */
int clib_cpuid_get_cache_line_size (void);

#ifdef __cplusplus
}
#endif

#endif /* CLIB_CPUID_H */
