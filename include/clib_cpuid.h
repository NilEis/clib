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
#include "clib_cpuid_checks.h"
#include "clib_cpuid_leafs.h"
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
void clib_cpuid_raw (uint32_t leaf,
    uint32_t subleaf,
    uint32_t *eax,
    uint32_t *ebx,
    uint32_t *ecx,
    uint32_t *edx);

int clib_cpuid_is_supported (void);

/**
 * @brief Returns a pointer to the equivilant struct for the query
 * @see clib_cpuid_leafs.h
 *
 * @param leaf
 * @param subleaf
 * @return void*
 */
void *clib_cpuid_get (uint32_t leaf, uint32_t subleaf);

/**
 * @brief returns the vecndor ID string
 *
 * @return const char*
 */
const char *clib_cpuid_get_name (void);

/**
 * @brief returns the maximum supported standard level
 *
 * @return uint32_t
 */
uint32_t clib_cpuid_get_max_level (void);

/**
 * @brief returns the hypervisor string or NULL on error (sets errno)
 * 
 * @return const char* 
 */
const char* clib_cpuid_get_hypervisor(void);

#ifdef __cplusplus
}
#endif

#endif /* CLIB_CPUID_H */
