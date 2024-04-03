#include "clib_cpuid.h"
#include "clib_cpuid_leafs.h"
#include <stddef.h>

static char internal_cpuid_name[13] = { 0 };
static uint32_t internal_cpuid_max_level = 0;

static void internal_cpuid (uint32_t leaf,
    uint32_t subleaf,
    uint32_t *eax,
    uint32_t *ebx,
    uint32_t *ecx,
    uint32_t *edx);

static void internal_cpuid (uint32_t leaf,
    uint32_t subleaf,
    uint32_t *eax,
    uint32_t *ebx,
    uint32_t *ecx,
    uint32_t *edx)
{
    uint32_t local_eax = 0;
    uint32_t local_ebx = 0;
    uint32_t local_ecx = 0;
    uint32_t local_edx = 0;

#ifdef _MSC_VER
    __asm volatile
    {
        mov eax, leaf;
        mov ecx, subleaf;
        cpuid;
        mov local_eax, eax;
        mov local_ebx, ebx;
        mov local_ecx, ecx;
        mov local_edx, edx;
    }
#else
    __asm__ __volatile__ (
        "cpuid\n\t"
        : "=a"(local_eax), "=b"(local_ebx), "=c"(local_ecx), "=d"(local_edx)
        : "0"(leaf), "2"(subleaf));
#endif

    if (eax != NULL)
    {
        *eax = local_eax;
    }
    if (ebx != NULL)
    {
        *ebx = local_ebx;
    }
    if (ecx != NULL)
    {
        *ecx = local_ecx;
    }
    if (edx != NULL)
    {
        *edx = local_edx;
    }
}

const char *clib_cpuid_get_name (void)
{
    if (internal_cpuid_name[0] == 0)
    {
        internal_cpuid (0x00,
            0x00,
            &internal_cpuid_max_level,
            (uint32_t *)(&internal_cpuid_name[0]),
            (uint32_t *)(&internal_cpuid_name[8]),
            (uint32_t *)(&internal_cpuid_name[4]));
    }
    return internal_cpuid_name;
}

uint32_t clib_cpuid_get_max_level (void)
{
    if (internal_cpuid_max_level == 0)
    {
        internal_cpuid (0x00,
            0x00,
            &internal_cpuid_max_level,
            (uint32_t *)(&internal_cpuid_name[0]),
            (uint32_t *)(&internal_cpuid_name[8]),
            (uint32_t *)(&internal_cpuid_name[4]));
    }
    return internal_cpuid_max_level;
}

void clib_cpuid_raw (uint32_t leaf,
    uint32_t subleaf,
    uint32_t *eax,
    uint32_t *ebx,
    uint32_t *ecx,
    uint32_t *edx)
{
    internal_cpuid (leaf, subleaf, eax, ebx, ecx, edx);
}

int clib_cpuid_supports_cmov (void)
{
    clib_cpuid_leaf_1_subleaf_0_t *res = clib_cpuid_get (1, 0);
    return res->edx.field.cmov;
}

int clib_cpuid_supports_mmx (void)
{
    clib_cpuid_leaf_1_subleaf_0_t *res = clib_cpuid_get (1, 0);
    return res->edx.field.mmx;
}

int clib_cpuid_supports_popcnt (void)
{
    clib_cpuid_leaf_1_subleaf_0_t *res = clib_cpuid_get (1, 0);
    return res->ecx.field.popcnt;
}

int clib_cpuid_supports_sse (void)
{
    clib_cpuid_leaf_1_subleaf_0_t *res = clib_cpuid_get (1, 0);
    return res->edx.field.sse;
}

int clib_cpuid_supports_sse2 (void)
{
    clib_cpuid_leaf_1_subleaf_0_t *res = clib_cpuid_get (1, 0);
    return res->edx.field.sse2;
}

int clib_cpuid_supports_sse3 (void)
{
    clib_cpuid_leaf_1_subleaf_0_t *res = clib_cpuid_get (1, 0);
    return res->ecx.field.sse3;
}

int clib_cpuid_supports_ssse3 (void)
{
    clib_cpuid_leaf_1_subleaf_0_t *res = clib_cpuid_get (1, 0);
    return res->ecx.field.ssse3;
}

int clib_cpuid_supports_sse4_1 (void)
{
    clib_cpuid_leaf_1_subleaf_0_t *res = clib_cpuid_get (1, 0);
    return res->ecx.field.sse4_1;
}

int clib_cpuid_supports_sse4_2 (void)
{
    clib_cpuid_leaf_1_subleaf_0_t *res = clib_cpuid_get (1, 0);
    return res->ecx.field.sse4_2;
}

int clib_cpuid_supports_avx (void)
{
    clib_cpuid_leaf_1_subleaf_0_t *res = clib_cpuid_get (1, 0);
    return res->ecx.field.avx;
}

int clib_cpuid_supports_avx2 (void)
{
    clib_cpuid_leaf_7_subleaf_0_t *res = clib_cpuid_get (7, 0);
    return res->ebx.field.avx2;
}

int clib_cpuid_supports_sse4a (void)
{
    clib_cpuid_leaf_0x80000001_subleaf_0_t *res = clib_cpuid_get (0x80000001, 0);
    return res->ecx.field.sse4a;
}

int clib_cpuid_supports_fma (void)
{
    clib_cpuid_leaf_1_subleaf_0_t *res = clib_cpuid_get (1, 0);
    return res->ecx.field.fma;
}

int clib_cpuid_supports_fma4 (void)
{
    clib_cpuid_leaf_0x80000001_subleaf_0_t *res = clib_cpuid_get (0x80000001, 0);
    return res->ecx.field.fma4;
}

int clib_cpuid_supports_xop (void)
{
    clib_cpuid_leaf_0x80000001_subleaf_0_t *res = clib_cpuid_get (0x80000001, 0);
    return res->ecx.field.xop;
}

int clib_cpuid_supports_avx512f (void)
{
    clib_cpuid_leaf_7_subleaf_0_t *res = clib_cpuid_get (7, 0);
    return res->ebx.field.avx512f;
}

int clib_cpuid_supports_bmi (void)
{
    clib_cpuid_leaf_7_subleaf_0_t *res = clib_cpuid_get (7, 0);
    return res->ebx.field.bmi1;
}

int clib_cpuid_supports_bmi2 (void)
{
    clib_cpuid_leaf_7_subleaf_0_t *res = clib_cpuid_get (7, 0);
    return res->ebx.field.bmi2;
}

int clib_cpuid_supports_aes (void)
{
    clib_cpuid_leaf_1_subleaf_0_t *res = clib_cpuid_get (1, 0);
    return res->ecx.field.aes;
}

int clib_cpuid_supports_avx512vl (void)
{
    clib_cpuid_leaf_7_subleaf_0_t *res = clib_cpuid_get (7, 0);
    return res->ebx.field.avx512vl;
}

int clib_cpuid_supports_avx512bw (void)
{
    clib_cpuid_leaf_7_subleaf_0_t *res = clib_cpuid_get (7, 0);
    return res->ebx.field.avx512bw;
}

int clib_cpuid_supports_avx512dq (void)
{
    clib_cpuid_leaf_7_subleaf_0_t *res = clib_cpuid_get (7, 0);
    return res->ebx.field.avx512dq;
}

int clib_cpuid_supports_avx512cd (void)
{
    clib_cpuid_leaf_7_subleaf_0_t *res = clib_cpuid_get (7, 0);
    return res->ebx.field.avx512cd;
}

int clib_cpuid_supports_avx512er (void)
{
    clib_cpuid_leaf_7_subleaf_0_t *res = clib_cpuid_get (7, 0);
    return res->ebx.field.avx512er;
}

int clib_cpuid_supports_avx512pf (void)
{
    clib_cpuid_leaf_7_subleaf_0_t *res = clib_cpuid_get (7, 0);
    return res->ebx.field.avx512pf;
}

int clib_cpuid_supports_avx512vbmi (void)
{
    clib_cpuid_leaf_7_subleaf_0_t *res = clib_cpuid_get (7, 0);
    return res->ecx.field.avx512vbmi;
}

int clib_cpuid_supports_avx512ifma (void)
{
    clib_cpuid_leaf_7_subleaf_0_t *res = clib_cpuid_get (7, 0);
    return res->ebx.field.avx512ifma;
}

int clib_cpuid_supports_gfni (void)
{
    clib_cpuid_leaf_7_subleaf_0_t *res = clib_cpuid_get (7, 0);
    return res->ecx.field.gfni;
}

int clib_cpuid_supports_vpclmulqdq (void)
{
    clib_cpuid_leaf_7_subleaf_0_t *res = clib_cpuid_get (7, 0);
    return res->ecx.field.vpclmulqdq;
}
