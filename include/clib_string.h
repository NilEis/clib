/** @file
 * @brief Functions for interacting with strings
 */
#ifndef CLIB_STRING_H
#define CLIB_STRING_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "clib_c90_support.h"
#include "clib_math.h"
#include <stddef.h>
#include <stdint.h>

    /**
     * @brief Type for strings
     *
     */
    typedef struct __clib_string_builder clib_string_builder_t;

    /**
     * @brief creates a string_builder
     *
     * @param initial_size the inital size of the string builder
     * @return clib_string_t* a pointer to the string builder
     */
    clib_string_builder_t *clib_string_builder_create(size_t initial_size);

    /**
     * @brief Appends the given string to the string builder
     *
     * @param builder
     * @param str the string to append
     * @return clib_string_builder_t*
     */
    clib_string_builder_t *clib_string_builder_append(clib_string_builder_t *builder, const char *str);

    /**
     * @brief returns the string that was build by the builder (the string has to be freed separate of the builder)
     *
     * @param builder
     * @return char*
     */
    char *clib_string_builder_get_string(clib_string_builder_t *builder);

    /**
     * @brief frees the string builder
     *
     * @param builder
     */
    void clib_string_builder_free(clib_string_builder_t *builder);

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

    /**
     * @brief converts a number of the given base to a string (without sign)
     *
     * @param dest the destination buffer
     * @param i the number to be converted
     * @param radix the base of the number
     * @return char* dest or NULL on error
     */
    char *clib_string_from_int(char *dest, intmax_t i, clib_radix_t radix);

    /**
     * @fn char *clib_string_reverse(const char *restrict src, char *restrict dest, size_t length)
     * @brief reverses a string
     *
     * @param src the source pointer
     * @param dest the destination for the reversed string
     * @param length the length of src
     * @return char* dest
     */
    char *clib_string_reverse(const char *restrict src, char *restrict dest, size_t length);

    /**
     * @fn char *clib_string_reverse_in_place(char *src, size_t length)
     * @brief reverses a string
     *
     * @param src the source pointer
     * @param length the length of src
     * @return char* dest
     */
    char *clib_string_reverse_in_place(char *src, size_t length);

#ifdef __cplusplus
}
#endif

#endif /* CLIB_STRING_H */
