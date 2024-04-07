#include <stdio.h>
#include <stdint.h>

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

int main(int argc, char**argv)
{
    char name[13] = { 0 };
    internal_cpuid (0x00,
            0x00,
            NULL,
            (uint32_t *)(&name[0]),
            (uint32_t *)(&name[8]),
            (uint32_t *)(&name[4]));
    printf("Name: %s\n", name);
    return 1;
}