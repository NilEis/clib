#include "clib_cpuid.h"
#include <stddef.h>

#define ADD_CHECK(leaf, subleaf, name)                                        \
    int clib_cpuid_supports_##name (void)                                     \
    {                                                                         \
        const clib_cpuid_leaf_##leaf##_subleaf_##subleaf##_t *res             \
            = clib_cpuid_get (leaf, subleaf);                                 \
        return res->name;                                                     \
    }

ADD_CHECK (1, 0, cmov)
ADD_CHECK (1, 0, mmx)
ADD_CHECK (1, 0, popcnt)
ADD_CHECK (1, 0, sse)
ADD_CHECK (1, 0, sse2)
ADD_CHECK (1, 0, sse3)
ADD_CHECK (1, 0, ssse3)
ADD_CHECK (1, 0, sse4_1)
ADD_CHECK (1, 0, sse4_2)
ADD_CHECK (1, 0, avx)
ADD_CHECK (7, 0, avx2)
ADD_CHECK (0x80000001, 0, sse4a)
ADD_CHECK (1, 0, fma)
ADD_CHECK (0x80000001, 0, fma4)
ADD_CHECK (0x80000001, 0, xop)
ADD_CHECK (7, 0, avx512f)
ADD_CHECK (7, 0, bmi1)
ADD_CHECK (7, 0, bmi2)
ADD_CHECK (1, 0, aes)
ADD_CHECK (7, 0, avx512vl)
ADD_CHECK (7, 0, avx512bw)
ADD_CHECK (7, 0, avx512dq)
ADD_CHECK (7, 0, avx512cd)
ADD_CHECK (7, 0, avx512er)
ADD_CHECK (7, 0, avx512pf)
ADD_CHECK (7, 0, avx512vbmi)
ADD_CHECK (7, 0, avx512ifma)
ADD_CHECK (7, 0, gfni)
ADD_CHECK (7, 0, vpclmulqdq)
