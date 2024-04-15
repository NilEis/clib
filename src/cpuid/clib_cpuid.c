#include "clib_cpuid.h"
#include "clib_error.h"
#include "clib_string.h"
#include <stddef.h>

static char internal_cpuid_name[13] = { 0 };
static char internal_cpuid_hypervisor[13] = { 0 };
static uint_least32_t internal_cpuid_max_level = 0;

static void internal_cpuid (uint_least32_t leaf,
    uint_least32_t subleaf,
    uint_least32_t *eax,
    uint_least32_t *ebx,
    uint_least32_t *ecx,
    uint_least32_t *edx);

static void internal_cpuid (uint_least32_t leaf,
    uint_least32_t subleaf,
    uint_least32_t *eax,
    uint_least32_t *ebx,
    uint_least32_t *ecx,
    uint_least32_t *edx)
{
    uint_least32_t local_eax = 0;
    uint_least32_t local_ebx = 0;
    uint_least32_t local_ecx = 0;
    uint_least32_t local_edx = 0;

#ifndef CLIB_CPUID_UNSUPPORTED
#if __GNUC__
    __asm__ __volatile__ (
        "cpuid\n\t"
        : "=a"(local_eax), "=b"(local_ebx), "=c"(local_ecx), "=d"(local_edx)
        : "0"(leaf), "2"(subleaf));
#elif defined(_MSC_VER)
    __asm
        {
        mov eax, leaf
        mov ecx, subleaf
        cpuid
        mov local_eax, eax
        mov local_ebx, ebx
        mov local_ecx, ecx
        mov local_edx, edx
        }
#else
#warning "Unknown compiler"
#endif
#else
    clib_errno = CLIB_ERRNO_CPUID_NOT_SUPPORTED;
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

int clib_cpuid_is_supported (void)
{
    clib_error_code_t tmp_err = clib_errno;
    int ret = 0;
    internal_cpuid (0, 0, NULL, NULL, NULL, NULL);
    ret = clib_errno != CLIB_ERRNO_CPUID_NOT_SUPPORTED;
    clib_errno = tmp_err;
    return ret;
}

const char *clib_cpuid_get_name (void)
{
    if (internal_cpuid_name[0] == 0)
    {
        internal_cpuid (0x00,
            0x00,
            &internal_cpuid_max_level,
            (uint_least32_t *)(&internal_cpuid_name[0]),
            (uint_least32_t *)(&internal_cpuid_name[8]),
            (uint_least32_t *)(&internal_cpuid_name[4]));
    }
    return internal_cpuid_name;
}

uint_least32_t clib_cpuid_get_max_level (void)
{
    if (internal_cpuid_max_level == 0)
    {
        internal_cpuid (0x00,
            0x00,
            &internal_cpuid_max_level,
            (uint_least32_t *)(&internal_cpuid_name[0]),
            (uint_least32_t *)(&internal_cpuid_name[8]),
            (uint_least32_t *)(&internal_cpuid_name[4]));
    }
    return internal_cpuid_max_level;
}

const char *clib_cpuid_get_hypervisor (void)
{
    if (internal_cpuid_hypervisor[0] == 0)
    {
        internal_cpuid (0x40000000,
            0,
            NULL,
            (uint_least32_t *)(&internal_cpuid_hypervisor[0]),
            (uint_least32_t *)(&internal_cpuid_hypervisor[4]),
            (uint_least32_t *)(&internal_cpuid_hypervisor[8]));
    }
    return internal_cpuid_hypervisor;
}

void clib_cpuid_raw (uint_least32_t leaf,
    uint_least32_t subleaf,
    uint_least32_t *eax,
    uint_least32_t *ebx,
    uint_least32_t *ecx,
    uint_least32_t *edx)
{
    internal_cpuid (leaf, subleaf, eax, ebx, ecx, edx);
}

int clib_cpuid_get_cache_line_size (void)
{
    const char *name = clib_cpuid_get_name ();
    if ((clib_string_cmp (name, "AMDisbetter!") == 0)
        || (clib_string_cmp (name, "AuthenticAMD") == 0))
    {
        const clib_cpuid_leaf_0x80000006_subleaf_0_t *res
            = clib_cpuid_get (0x80000006, 0);
        return res->l2_line_size;
    }

    const clib_cpuid_leaf_4_subleaf_0_t *res = clib_cpuid_get (4, 0);
    return res->cache_linesize + 1;
}
