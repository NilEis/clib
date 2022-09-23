/** @file
 * @brief Functions for interacting with strings
 */
#ifndef CLIB_STRING_H
#define CLIB_STRING_H

/** @fn size_t clib_strcpy(char* restrict dest, const char* restrict src, size_t size)
 * @brief copies size characters of src to dest
 * @param dest The address of the destination
 * @param src The address of the src string
 * @param size The amount of characters to be copied: \f$\text{size}\leq\text{sizeof}(\text{src})\land\text{size}\leq\text{sizeof}(\text{dest})\f$
 */
size_t clib_strcpy(char* restrict dest, const char* restrict src, size_t size);

#endif // CLIB_STRING_H
