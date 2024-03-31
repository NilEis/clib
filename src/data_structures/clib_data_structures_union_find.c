#include "clib_data_structures.h"
#include <stdlib.h>
struct clib_internal_union_find
{
    struct clib_internal_union_find *parent;
    void *value;
    int height;
    int id;
};

clib_union_find_t *clib_set_make (void *elem)
{
    clib_union_find_t *ret
        = (clib_union_find_t *)malloc (sizeof (clib_union_find_t));
    ret->height = 1;
    ret->parent = ret;
    ret->value = elem;
    return ret;
}

clib_union_find_t *clib_set_find (clib_union_find_t *elem)
{
    clib_union_find_t *tmp = elem;
    if (tmp == NULL)
    {
        return NULL;
    }
    while (elem->parent != elem)
    {
        elem = elem->parent;
    }
    if (elem != tmp->parent && elem != tmp)
    {
        tmp->parent = elem;
    }
    return elem;
}

clib_union_find_t *clib_set_merge (
    clib_union_find_t *set_1, clib_union_find_t *set_2)
{
    clib_union_find_t *root_1 = NULL;
    clib_union_find_t *root_2 = NULL;
    clib_union_find_t *ret = NULL;
    if (set_1 == NULL || set_2 == NULL)
    {
        return NULL;
    }
    root_1 = clib_set_find (set_1);
    root_2 = clib_set_find (set_2);
    ret = set_1;
    if (root_1 != root_2)
    {
        if (root_1->height > root_2->height)
        {
            root_2->parent = root_1;
            root_1->height++;
        }
        else
        {
            root_1->parent = root_2;
            root_2->height++;
            ret = root_2;
        }
    }
    return ret;
}
