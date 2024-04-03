#include "clib_cpuid.h"
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
