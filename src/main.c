#include "clib.h"
#include "clib_cpuid.h"
#include <stdio.h>

#define DEFAULT_SIZE 8

int main (int argc, char const *argv[])
{
    clib_string_builder_t *builder = clib_string_builder_create (DEFAULT_SIZE);
    (void)argc;
    (void)argv;
    printf ("Name: %s\n", clib_cpuid_get_name ());
    clib_cpuid_leaf_1_subleaf_0_t *res = clib_cpuid_get (1, 0);
    printf("Supported:\n");
    printf ("    cmov: %d\n", clib_cpuid_supports_cmov ());
    printf ("    mmx: %d\n", clib_cpuid_supports_mmx ());
    printf ("    popcnt: %d\n", clib_cpuid_supports_popcnt ());
    printf ("    sse: %d\n", clib_cpuid_supports_sse ());
    printf ("    sse2: %d\n", clib_cpuid_supports_sse2 ());
    printf ("    sse3: %d\n", clib_cpuid_supports_sse3 ());
    printf ("    ssse3: %d\n", clib_cpuid_supports_ssse3 ());
    printf ("    sse4_1: %d\n", clib_cpuid_supports_sse4_1 ());
    printf ("    sse4_2: %d\n", clib_cpuid_supports_sse4_2 ());
    printf ("    avx: %d\n", clib_cpuid_supports_avx ());
    printf ("    avx2: %d\n", clib_cpuid_supports_avx2 ());
    printf ("    sse4a: %d\n", clib_cpuid_supports_sse4a ());
    printf ("    fma: %d\n", clib_cpuid_supports_fma ());
    printf ("    fma4: %d\n", clib_cpuid_supports_fma4 ());
    printf ("    xop: %d\n", clib_cpuid_supports_xop ());
    printf ("    avx512f: %d\n", clib_cpuid_supports_avx512f ());
    printf ("    bmi: %d\n", clib_cpuid_supports_bmi ());
    printf ("    bmi2: %d\n", clib_cpuid_supports_bmi2 ());
    printf ("    aes: %d\n", clib_cpuid_supports_aes ());
    printf ("    avx512vl: %d\n", clib_cpuid_supports_avx512vl ());
    printf ("    avx512bw: %d\n", clib_cpuid_supports_avx512bw ());
    printf ("    avx512dq: %d\n", clib_cpuid_supports_avx512dq ());
    printf ("    avx512cd: %d\n", clib_cpuid_supports_avx512cd ());
    printf ("    avx512er: %d\n", clib_cpuid_supports_avx512er ());
    printf ("    avx512pf: %d\n", clib_cpuid_supports_avx512pf ());
    printf ("    avx512vbmi: %d\n", clib_cpuid_supports_avx512vbmi ());
    printf ("    avx512ifma: %d\n", clib_cpuid_supports_avx512ifma ());
    printf ("    gfni: %d\n", clib_cpuid_supports_gfni ());
    printf ("    vpclmulqdq: %d\n", clib_cpuid_supports_vpclmulqdq ());
    return 0;
}
