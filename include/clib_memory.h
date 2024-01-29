/**
 * @file clib_memory.h
 * @brief functions for working with memory
 */
#ifndef CLIB_MEMORY_H
#define CLIB_MEMORY_H

#ifdef __cplusplus 
extern "C" {
#endif

#include "clib_c90_support.h"
#include <stddef.h>
#include <stdint.h>

/**
 * @brief Copys memory of size size from src to dest
 *
 * @param src the source pointer
 * @param dest the destination pointer
 * @param size the size of the memory in bytes
 * @return void* the destination pointer
 */
void *clib_memory_copy(const void *restrict src, void *restrict dest, size_t size);

/**
 * @brief Fill the given memory with the u8 value
 *
 * @param dest the destination pointer
 * @param value the value
 * @param size the size in elements of size sizeof(uint8_t)
 * @return void* the dest pointer
 */
void *clib_memory_set_u8(void *dest, uint8_t value, size_t size);

/**
 * @brief Fill the given memory with the u16 value
 *
 * @param dest the destination pointer
 * @param value the value
 * @param size the size in elements of size sizeof(uint16_t)
 * @return void* the dest pointer
 */
void *clib_memory_set_u16(void *dest, uint16_t value, size_t size);

/**
 * @brief Fill the given memory with the u32 value
 *
 * @param dest the destination pointer
 * @param value the value
 * @param size the size in elements of size sizeof(uint32_t)
 * @return void* the dest pointer
 */
void *clib_memory_set_u32(void *dest, uint32_t value, size_t size);

/**
 * @brief Fill the given memory with the u64 value
 *
 * @param dest the destination pointer
 * @param value the value
 * @param size the size in elements of size sizeof(uint64_t)
 * @return void* the dest pointer
 */
void *clib_memory_set_u64(void *dest, uint64_t value, size_t size);

#ifdef __cplusplus 
}
#endif

#endif /* CLIB_MEMORY_H */
