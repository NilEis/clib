#include "clib_data_structures.h"
#include "clib_error.h"
#include <stdlib.h>

struct clib_internal_list_node
{
    clib_list_node_t *prev;
    clib_list_node_t *next;
    void *value;
};

struct clib_internal_list
{
    clib_data_structure_header_t header;
    size_t size;
    clib_list_node_t *first;
    clib_list_node_t *current;
    clib_list_node_t *last;
};

static void internal_update_first_and_last (clib_list_t *list)
{
    if (list->first->prev != NULL)
    {
        list->first = list->first->prev;
    }
    if (list->last->next != NULL)
    {
        list->last = list->last->next;
    }
}

static clib_list_node_t *internal_create_node (void)
{
    clib_list_node_t *res = calloc (1, sizeof (clib_list_node_t));
    if (res == NULL)
    {
        clib_errno = CLIB_ERRNO_ALLOCATION_ZEROED_ERROR;
        return NULL;
    }
    return res;
}

clib_list_t *clib_list_create (void)
{
    clib_list_t *res = calloc (1, sizeof (clib_list_t));
    if (res == NULL)
    {
        clib_errno = CLIB_ERRNO_ALLOCATION_ZEROED_ERROR;
        return NULL;
    }
    res->header = CLIB_DATA_STRUCTURE_LIST;
    res->current = NULL;
    res->first = NULL;
    res->last = NULL;
    res->size = 0;
    return res;
}

int clib_list_is_empty (clib_list_t *list) { return list->size == 0; }

int clib_list_next (clib_list_t *list)
{
    if (list->current->next == NULL)
    {
        return 0;
    }
    list->current = list->current->next;
    return 1;
}

size_t clib_list_size (clib_list_t *list) { return list->size; }

int clib_list_prepend (clib_list_t *list, void *data)
{
    clib_list_node_t *node = internal_create_node ();
    clib_list_node_t *current = list->current;
    if (node == NULL)
    {
        return 0;
    }
    node->value = data;
    node->next = current;
    node->prev = current->prev;
    current->prev = node;
    internal_update_first_and_last (list);
    return 1;
}

int clib_list_insert (clib_list_t *list, void *data)
{
    clib_list_node_t *node = internal_create_node ();
    clib_list_node_t *current = list->current;
    if (node == NULL)
    {
        return 0;
    }
    node->value = data;
    node->next = current->next;
    node->prev = current;
    current->next = node;
    internal_update_first_and_last (list);
    return 1;
}

int clib_list_insert_front (clib_list_t *list, void *data)
{
    clib_list_node_t *node = internal_create_node ();
    clib_list_node_t *front = list->first;
    if (node == NULL)
    {
        return 0;
    }
    node->value = data;
    list->first = node;
    node->next = front;
    front->prev = node;
    return 1;
}

int clib_list_insert_back (clib_list_t *list, void *data)
{
    clib_list_node_t *node = internal_create_node ();
    clib_list_node_t *back = list->last;
    if (node == NULL)
    {
        return 0;
    }
    node->value = data;
    list->last = node;
    node->prev = back;
    back->next = node;
    return 1;
}

void *clib_list_get (clib_list_t *list) { return list->current->value; }

clib_list_node_t *clib_list_get_node (clib_list_t *list)
{
    return list->current;
}

void *clib_list_remove (clib_list_t *list, clib_list_node_t *node)
{
    void *data = node->value;
    node->value = NULL;
    if (list->first == node)
    {
        list->first = list->first->next;
    }
    if (list->first == node)
    {
        list->last = list->last->prev;
    }
    if (node->prev != NULL)
    {
        node->prev->next = node->next;
    }
    if (node->next != NULL)
    {
        node->next->prev = node->prev;
    }
    free (node);
    return data;
}

void clib_list_free (clib_list_t *list)
{
    clib_list_node_t *elem = list->first;
    while (elem != NULL)
    {
        clib_list_node_t *tmp = elem->next;
        free (elem);
    }
    free (list);
}
