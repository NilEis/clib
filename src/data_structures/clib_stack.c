#include "clib_data_structures.h"
#include "clib_error.h"
#include <stdlib.h>

struct clib_internal_stack
{
    clib_data_structure_header_t header;
    size_t size;
    size_t capacity;
    void **data;
};

clib_stack_t *clib_stack_create (size_t inital_size)
{
    clib_stack_t *res = NULL;
    res = calloc (1, sizeof (clib_stack_t));
    if (res == NULL)
    {
        clib_errno = CLIB_ERRNO_ALLOCATION_ZEROED_ERROR;
        return NULL;
    }
    if (inital_size <= 2)
    {
        inital_size = 2;
    }
    res->header = CLIB_DATA_STRUCTURE_STACK;
    res->data = calloc (inital_size, sizeof (void *));
    if (res->data == NULL)
    {
        clib_errno = CLIB_ERRNO_ALLOCATION_ZEROED_ERROR;
        free (res);
        return NULL;
    }
    res->capacity = inital_size;
    res->size = 0;
    return res;
}

clib_stack_t *clib_stack_push (clib_stack_t *stack, void *elem)
{
    if (stack->size == stack->capacity)
    {
        size_t new_capacity = stack->capacity * 2;
        void **new_data
            = realloc (stack->data, new_capacity * sizeof (void *));
        if (new_data == NULL)
        {
            clib_errno = CLIB_ERRNO_REALLOCATION_ERROR;
            return NULL;
        }
        stack->data = new_data;
        stack->capacity = new_capacity;
    }
    stack->data[stack->size] = elem;
    stack->size++;
    return stack;
}

void *clib_stack_pop (clib_stack_t *stack)
{
    if (stack->size == 0)
    {
        clib_errno = CLIB_ERRNO_STACK_EMPTY;
        return NULL;
    }
    stack->size--;
    return stack->data[stack->size];
}

size_t clib_stack_size (clib_stack_t *stack) { return stack->size; }

void clib_stack_free (clib_stack_t *stack)
{
    stack->capacity = 0;
    stack->size = 0;
    free (stack->data);
    stack->data = NULL;
    free (stack);
}
