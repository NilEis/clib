/** @file
 * @brief provides types and functions for stacks
 */
#if !defined(CLIB_STACK_H) && defined(CLIB_INCLUDE_DATA_STRUCTURES)
#define CLIB_STACK_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "../clib_c90_support.h"
#include <stddef.h>

/**
 * @brief typedef for the stack structure
 */
typedef struct clib_internal_stack clib_stack_t;

/**
 * @brief creates a new stack
 *
 * @param inital_size the inital amount of elements the stack can hold
 * @return clib_stack_t*
 */
clib_stack_t *clib_stack_create (size_t inital_size);

/**
 * @brief pushes an element to the stack
 *
 * @param stack
 * @param elem
 * @return clib_stack_t* the given stack or NULL if the push failed (sets
 * clib_errno)
 */
clib_stack_t *clib_stack_push (clib_stack_t *stack, void *elem);

/**
 * @brief pops an element from the stack
 *
 * @param stack
 * @return void* the popped element or NULL if the stack is empty (sets
 * clib_errno)
 */
void *clib_stack_pop (clib_stack_t *stack);

/**
 * @brief returns the size of the stack
 *
 * @param stack
 * @return size_t
 */
size_t clib_stack_size (clib_stack_t *stack);

/**
 * @brief frees the stack
 *
 * @param stack
 */
void clib_stack_free (clib_stack_t *stack);

#ifdef __cplusplus
}
#endif

#endif /* CLIB_STACK_H */
