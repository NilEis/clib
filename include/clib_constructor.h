/**
 * @file clib_constructor.h
 * @author NilEis
 * @brief Provides a constructor wrapper for GCC/Clang and MSVC
 * @date 2023-04-15
 * 
 * @copyright Initializer/finalizer sample for MSVC and GCC/Clang.
 * 2010-2016 Joe Lowe. Released into the public domain.
 * @see https://stackoverflow.com/a/2390626
 */
#ifndef CLIB_CONSTRUCTOR_H
#define CLIB_CONSTRUCTOR_H
#include "clib_c90_support.h"
/**
 * @brief a function specified in the macro will be run before main
 */
#ifdef __cplusplus
#define INITIALIZER(f)   \
    static void f(void); \
    struct f##_t_        \
    {                    \
        f##_t_(void)     \
        {                \
            f();         \
        }                \
    };                   \
    static f##_t_ f##_;  \
    static void f(void)
#elif defined(_MSC_VER)
#pragma section(".CRT$XCU", read)
#define INITIALIZER2_(f, p)                                  \
    static void f(void);                                     \
    __declspec(allocate(".CRT$XCU")) void (*f##_)(void) = f; \
    __pragma(comment(linker, "/include:" p #f "_")) static void f(void)
#ifdef _WIN64
#define INITIALIZER(f) INITIALIZER2_(f, "")
#else
#define INITIALIZER(f) INITIALIZER2_(f, "_")
#endif
#else
#define INITIALIZER(f)                                \
    static void f(void) __attribute__((constructor)); \
    static void f(void)
#endif

#endif /* CLIB_CONSTRUCTOR_H */
