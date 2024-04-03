/** @file
 * @brief redefines keywords if they are not in C90
 */
#ifndef CLIB_C90_SUPPORT_H
#define CLIB_C90_SUPPORT_H

#ifdef __cplusplus
extern "C"
{
#endif

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

#ifndef false
#define false 0
#endif

#ifndef true
#define true 1
#endif

#ifndef bool
#define bool int
#endif

#endif

#ifdef __cplusplus
}
#endif

#endif /* CLIB_C90_SUPPORT_H */
