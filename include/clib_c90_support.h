/** @file
 * @brief redefines keywords if they are not in C90
 */
#ifndef CLIB_C90_SUPPORT_H
#define CLIB_C90_SUPPORT_H

#if __STDC_VERSION__ >= 199901L
/* "inline" is a keyword */
/* "restrict" is a keyword */
#else
/**
 * @brief redefine inline as static
 */
#define inline static
/**
 * @brief remove restrict
 */
#define restrict
#endif

#endif /* CLIB_C90_SUPPORT_H */
