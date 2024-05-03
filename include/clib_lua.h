/** @file
 * @brief functions for working with lua
 */
#if !defined(CLIB_LUA_H) && defined(CLIB_INCLUDE_LUA)
#define CLIB_LUA_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "clib_error.h"

typedef enum
{
    CLIB_LUA_OPEN_MATH = 1U << 0U,   /*!< make the lua math lib avaiable */
    CLIB_LUA_OPEN_STRING = 1U << 1U, /*!< make the lua string lib avaiable */
    CLIB_LUA_STRING_BUFFER = 1U
                          << 2U, /*!< make the lua string_buffer lib avaiable*/
    CLIB_LUA_BASE = 1U << 3U,    /*!< make the lua base lib avaiable*/
    CLIB_LUA_BIT = 1U << 4U,     /*!< make the lua bit lib avaiable*/
    CLIB_LUA_DEBUG = 1U << 5U,   /*!< make the lua debug lib avaiable*/
    CLIB_LUA_FFI = 1U << 6U,     /*!< make the lua ffi lib avaiable*/
    CLIB_LUA_IO = 1U << 7U,      /*!< make the lua io lib avaiable*/
    CLIB_LUA_JIT = 1U << 8U,     /*!< make the lua jit lib avaiable*/
    CLIB_LUA_OS = 1U << 9U,      /*!< make the lua os lib avaiable*/
    CLIB_LUA_PACKAGE = 1U << 10U, /*!< make the lua package lib avaiable*/
    CLIB_LUA_TABLE = 1U << 11U,   /*!< make the lua table lib avaiable*/
    CLIB_LUA_OPEN_LIBS
    = (unsigned)CLIB_LUA_OPEN_MATH | (unsigned)CLIB_LUA_OPEN_STRING
    | (unsigned)CLIB_LUA_STRING_BUFFER | (unsigned)CLIB_LUA_BASE
    | (unsigned)CLIB_LUA_BIT | (unsigned)CLIB_LUA_DEBUG
    | (unsigned)CLIB_LUA_FFI | (unsigned)CLIB_LUA_IO | (unsigned)CLIB_LUA_JIT
    | (unsigned)CLIB_LUA_OS | (unsigned)CLIB_LUA_PACKAGE
    | (unsigned)CLIB_LUA_TABLE, /*!< make the lua std libs avaiable */
} clib_lua_options_t;

/**
 * @brief typedef for lua state
 */
typedef void clib_lua_t;

/**
 * @brief create a new lua state
 * @param options options for the lua state
 * @return a new lua state or NULL on error (check clib_error)
 */
clib_lua_t *clib_lua_new (clib_lua_options_t options);

/**
 * @brief free a lua state
 * @param state the lua state to free
 */
void clib_lua_free (clib_lua_t *state);

#ifdef __cplusplus
}
#endif

#endif /* CLIB_LUA_H */
