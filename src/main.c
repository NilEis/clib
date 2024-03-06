#include "clib.h"
#include <stdlib.h>

#define DEFAULT_SIZE 8

int main (int argc, char const *argv[])
{
    clib_string_builder_t *builder = clib_string_builder_create (DEFAULT_SIZE);
    (void)argc;
    (void)argv;
    char *res = NULL;
    clib_string_builder_append (builder, "Hallo");
    res = clib_string_builder_get_string (builder);
    free (res);
    clib_string_builder_append (builder, ", Welt");
    res = clib_string_builder_get_string (builder);
    free (res);
    return 0;
}
