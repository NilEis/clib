#include "clib_cpuid.h"
#include <stddef.h>

#define ADD_CHECK(leaf, subleaf, reg, name)                                   \
    int clib_cpuid_supports_##name (void)                                     \
    {                                                                         \
        clib_cpuid_leaf_##leaf##_subleaf_##subleaf##_t *res                   \
            = clib_cpuid_get (leaf, subleaf);                                 \
        return res->reg.field.name;                                           \
    }

ADD_CHECK (1, 0, edx, cmov)
ADD_CHECK (1, 0, edx, mmx)
ADD_CHECK (1, 0, ecx, popcnt)
ADD_CHECK (1, 0, edx, sse)
ADD_CHECK (1, 0, edx, sse2)
ADD_CHECK (1, 0, ecx, sse3)
ADD_CHECK (1, 0, ecx, ssse3)
ADD_CHECK (1, 0, ecx, sse4_1)
ADD_CHECK (1, 0, ecx, sse4_2)
ADD_CHECK (1, 0, ecx, avx)
ADD_CHECK (7, 0, ebx, avx2)
ADD_CHECK (0x80000001, 0, ecx, sse4a)
ADD_CHECK (1, 0, ecx, fma)
ADD_CHECK (0x80000001, 0, ecx, fma4)
ADD_CHECK (0x80000001, 0, ecx, xop)
ADD_CHECK (7, 0, ebx, avx512f)
ADD_CHECK (7, 0, ebx, bmi1)
ADD_CHECK (7, 0, ebx, bmi2)
ADD_CHECK (1, 0, ecx, aes)
ADD_CHECK (7, 0, ebx, avx512vl)
ADD_CHECK (7, 0, ebx, avx512bw)
ADD_CHECK (7, 0, ebx, avx512dq)
ADD_CHECK (7, 0, ebx, avx512cd)
ADD_CHECK (7, 0, ebx, avx512er)
ADD_CHECK (7, 0, ebx, avx512pf)
ADD_CHECK (7, 0, ecx, avx512vbmi)
ADD_CHECK (7, 0, ebx, avx512ifma)
ADD_CHECK (7, 0, ecx, gfni)
ADD_CHECK (7, 0, ecx, vpclmulqdq)
