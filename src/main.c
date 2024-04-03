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
    printf ("FPU on chip: %d\n", res->edx.field.fpu);
    return 0;
}
