#if !defined(CLIB_CPUID_H) && defined(CLIB_INCLUDE_CPUID)
#define CLIB_CPUID_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "clib_c90_support.h"
#include "clib_cpuid_leafs.h"
#include <stdint.h>


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
 * @brief checks if cmov is supported
 *
 * @returns 1 on true 0 on false
 */
int clib_cpuid_supports_cmov (void);

/**
 * @brief checks if mmx is supported
 *
 * @returns 1 on true 0 on false
 */
int clib_cpuid_supports_mmx (void);

/**
 * @brief checks if popcnt is supported
 *
 * @returns 1 on true 0 on false
 */
int clib_cpuid_supports_popcnt (void);

/**
 * @brief checks if sse is supported
 *
 * @returns 1 on true 0 on false
 */
int clib_cpuid_supports_sse (void);

/**
 * @brief checks if sse2 is supported
 *
 * @returns 1 on true 0 on false
 */
int clib_cpuid_supports_sse2 (void);

/**
 * @brief checks if sse3 is supported
 *
 * @returns 1 on true 0 on false
 */
int clib_cpuid_supports_sse3 (void);

/**
 * @brief checks if ssse3 is supported
 *
 * @returns 1 on true 0 on false
 */
int clib_cpuid_supports_ssse3 (void);

/**
 * @brief checks if sse4_1 is supported
 *
 * @returns 1 on true 0 on false
 */
int clib_cpuid_supports_sse4_1 (void);

/**
 * @brief checks if sse4_2 is supported
 *
 * @returns 1 on true 0 on false
 */
int clib_cpuid_supports_sse4_2 (void);

/**
 * @brief checks if avx is supported
 *
 * @returns 1 on true 0 on false
 */
int clib_cpuid_supports_avx (void);

/**
 * @brief checks if avx2 is supported
 *
 * @returns 1 on true 0 on false
 */
int clib_cpuid_supports_avx2 (void);

/**
 * @brief checks if sse4a is supported
 *
 * @returns 1 on true 0 on false
 */
int clib_cpuid_supports_sse4a (void);

/**
 * @brief checks if fma is supported
 *
 * @returns 1 on true 0 on false
 */
int clib_cpuid_supports_fma (void);

/**
 * @brief checks if fma4 is supported
 *
 * @returns 1 on true 0 on false
 */
int clib_cpuid_supports_fma4 (void);

/**
 * @brief checks if xop is supported
 *
 * @returns 1 on true 0 on false
 */
int clib_cpuid_supports_xop (void);

/**
 * @brief checks if avx512f is supported
 *
 * @returns 1 on true 0 on false
 */
int clib_cpuid_supports_avx512f (void);

/**
 * @brief checks if bmi is supported
 *
 * @returns 1 on true 0 on false
 */
int clib_cpuid_supports_bmi (void);

/**
 * @brief checks if bmi2 is supported
 *
 * @returns 1 on true 0 on false
 */
int clib_cpuid_supports_bmi2 (void);

/**
 * @brief checks if aes is supported
 *
 * @returns 1 on true 0 on false
 */
int clib_cpuid_supports_aes (void);

/**
 * @brief checks if avx512vl is supported
 *
 * @returns 1 on true 0 on false
 */
int clib_cpuid_supports_avx512vl (void);

/**
 * @brief checks if avx512bw is supported
 *
 * @returns 1 on true 0 on false
 */
int clib_cpuid_supports_avx512bw (void);

/**
 * @brief checks if avx512dq is supported
 *
 * @returns 1 on true 0 on false
 */
int clib_cpuid_supports_avx512dq (void);

/**
 * @brief checks if avx512cd is supported
 *
 * @returns 1 on true 0 on false
 */
int clib_cpuid_supports_avx512cd (void);

/**
 * @brief checks if avx512er is supported
 *
 * @returns 1 on true 0 on false
 */
int clib_cpuid_supports_avx512er (void);

/**
 * @brief checks if avx512pf is supported
 *
 * @returns 1 on true 0 on false
 */
int clib_cpuid_supports_avx512pf (void);

/**
 * @brief checks if avx512vbmi is supported
 *
 * @returns 1 on true 0 on false
 */
int clib_cpuid_supports_avx512vbmi (void);

/**
 * @brief checks if avx512ifma is supported
 *
 * @returns 1 on true 0 on false
 */
int clib_cpuid_supports_avx512ifma (void);

/**
 * @brief checks if gfni is supported
 *
 * @returns 1 on true 0 on false
 */
int clib_cpuid_supports_gfni (void);

/**
 * @brief checks if vpclmulqdq is supported
 *
 * @returns 1 on true 0 on false
 */
int clib_cpuid_supports_vpclmulqdq (void);

#ifdef __cplusplus
}
#endif

#endif /* CLIB_CPUID_H */
