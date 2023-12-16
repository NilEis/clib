/** @file
 * @brief Functions for interacting with strings
 */
#ifndef CLIB_STRING_H
#define CLIB_STRING_H
#include "clib_c90_support.h"
#include <stddef.h>

/**
 * @fn size_t clib_string_length(const char *str)
 * @brief computes the size of str
 * 
 * @param str the string
 * @return length as size_t
 */
size_t clib_string_length(const char *str);

/** @fn size_t clib_string_copy(char* restrict dest, const char* restrict src, size_t size)
 * @brief copies \f$size\f$ characters of src to dest
 * @param dest The address of the destination
 * @param src The address of the src string
 * @param size The amount of characters to be copied: \f$\text{size}\leq\text{sizeof}(\text{src})\land\text{size}\leq\text{sizeof}(\text{dest})\f$
 * @return the amount of copied characters
 */
size_t clib_string_copy(char *restrict dest, const char *restrict src, size_t size);

/** @fn int clib_string_replace_char(char *src, char a, char b)
 * @brief replaces the first instance of \f$a\f$ with \f$b\f$
 * @param src the string
 * @param a the char to be replaced
 * @param b the replacing char
 * @return returns 1 if an instance was replaced, otherwise 0
 */
int clib_string_replace_char(char *src, char a, char b);

/** @fn size_t clib_string_replace_char_all(char *src, char a, char b)
 * @brief replaces all instances of \f$a\f$ with \f$b\f$
 * @param src the string
 * @param a the char to be replaced
 * @param b the replacing char
 * @return returns the number of replaced characters
 */
size_t clib_string_replace_char_all(char *src, char a, char b);

/**
 * @fn int clib_string_dist_lev(const char*a, const char*b)
 * @brief Computes the levenshtein distance of a and b
 *
 * @param a string a
 * @param b string b
 * @returns returns the edit distance between a and b
 */
int clib_string_dist_lev(const char *a, const char *b);

#endif /* CLIB_STRING_H */
