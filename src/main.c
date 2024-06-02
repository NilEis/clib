#include "clib.h"
#include "clib_error.h"
#include <stdio.h>

#define DEFAULT_SIZE 8

extern void free (void *);

int main (int argc, char const *argv[])
{
    (void)argc;
    (void)argv;
    clib_lua_t *lua = clib_lua_new (CLIB_LUA_OPEN_LIBS);
    clib_lua_run (lua, "print(\"Hello World from lua\")");
    clib_lua_set_global (
        lua, "testVar", CLIB_LUA_NUMBER, (clib_lua_number_t)DEFAULT_SIZE);
    clib_lua_run (lua, "print(testVar)");
    clib_lua_run (lua, "testVar = 3.1415");
    clib_lua_number_t testVar = 0;
    clib_lua_get_global (lua, "testVar", CLIB_LUA_NUMBER, &testVar);
    printf ("testVar: %f\n", testVar);
    if (clib_cpuid_is_supported ())
    {
        printf ("Name: %s\n", clib_cpuid_get_name ());
        printf ("Hypervisor: %s\n", clib_cpuid_get_hypervisor ());
        printf ("Max level: %d\n", clib_cpuid_get_max_level ());
        printf ("Supported:\n");
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
        printf ("    bmi1: %d\n", clib_cpuid_supports_bmi1 ());
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
        printf (
            "    cache line size: %d\n", clib_cpuid_get_cache_line_size ());
    }
    printf ("endianess: ");
    switch (clib_endianess_detect ())
    {
    case CLIB_ENDIAN_UNKNOWN:
        printf ("ENDIAN_UNKNOWN\n");
        break;
    case CLIB_ENDIAN_BIG:
        printf ("ENDIAN_BIG\n");
        break;
    case CLIB_ENDIAN_LITTLE:
        printf ("ENDIAN_LITTLE\n");
        break;
    case CLIB_ENDIAN_BIG_WORD:
        printf ("ENDIAN_BIG_WORD\n");
        break;
    case CLIB_ENDIAN_LITTLE_WORD:
        printf ("ENDIAN_LITTLE_WORD\n");
        break;
    }
    if (clib_lua_run (lua, "print(wird nicht klappen)") != CLIB_ERRNO_NO_ERROR)
    {
        printf ("Error: %s\n", clib_error_get_string (clib_errno));
    }
    clib_lua_free (lua);
    return 0;
}
