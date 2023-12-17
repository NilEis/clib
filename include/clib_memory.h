/**
 * @file clib_memory.h
 * @brief functions for working with memory
 */
#ifndef CLIB_MEMORY_H
#define CLIB_MEMORY_H
#include "clib_c90_support.h"
#include <stddef.h>

/**
 * @brief Copys memory of size size from src to dest
 * 
 * @param src the source pointer
 * @param dest the destination pointer
 * @param size the size of the memory in bytes
 * @return void* the destination pointer
 */
void* clib_memory_copy(const void*restrict src, void*restrict dest, size_t size);

#endif /* CLIB_MEMORY_H */
