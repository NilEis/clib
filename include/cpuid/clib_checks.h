/**
 * @file clib_checks.h
 * @author Nils Eisenach
 * @brief Functions for checking if the CPU supports certain instructions
 * @date 2024-04-05
 */
#if !defined(CLIB_CPUID_CHECKS_H) && defined(CLIB_INCLUDE_CPUID)
#define CLIB_CPUID_CHECKS_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "../clib_c90_support.h"

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
int clib_cpuid_supports_bmi1 (void);

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

#endif /* CLIB_CPUID_CHECKS_H */
