/** @file
 * @brief Functions for interacting with strings
 */
#ifndef CLIB_STRING_H
#define CLIB_STRING_H

/** @fn size_t clib_strcpy(char* restrict dest, const char* restrict src, size_t size)
 * @brief copies \f$size\f$ characters of src to dest
 * @param dest The address of the destination
 * @param src The address of the src string
 * @param size The amount of characters to be copied: \f$\text{size}\leq\text{sizeof}(\text{src})\land\text{size}\leq\text{sizeof}(\text{dest})\f$
 * @return the amount of copied characters
 */
size_t clib_strcpy(char* restrict dest, const char* restrict src, size_t size);

/** @fn int clib_replace_char(char *src, char a, char b)
 * @brief replaces the first instance of \f$a\f$ with \f$b\f$
 * @param src the string
 * @param a the char to be replaced
 * @param b the replacing char
 * @return returns 1 if an instance was replaced, otherwise 0
 */
int clib_replace_char(char *src, char a, char b);

/** @fn size_t clib_replace_char_all(char *src, char a, char b)
 * @brief replaces all instances of \f$a\f$ with \f$b\f$
 * @param src the string
 * @param a the char to be replaced
 * @param b the replacing char
 * @return returns the number of replaced characters
 */
size_t clib_replace_char_all(char *src, char a, char b);

#endif // CLIB_STRING_H
