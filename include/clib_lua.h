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
#include <stddef.h>

typedef enum
{
    CLIB_LUA_OPEN_MATH = 1U << 0U,   /*!< make the lua math lib avaiable */
    CLIB_LUA_OPEN_STRING = 1U << 1U, /*!< make the lua string lib avaiable */
    CLIB_LUA_RESERVED_0 = 1U
                          << 2U, /*!< make the lua string_buffer lib avaiable*/
    CLIB_LUA_BASE = 1U << 3U, /*!< make the lua base lib avaiable*/
    CLIB_LUA_RESERVED_1 = 1U << 4U,     /*!< make the lua bit lib avaiable*/
    CLIB_LUA_DEBUG = 1U << 5U, /*!< make the lua debug lib avaiable*/
    CLIB_LUA_RESERVED_2 = 1U << 6U,     /*!< make the lua ffi lib avaiable*/
    CLIB_LUA_IO = 1U << 7U, /*!< make the lua io lib avaiable*/
    CLIB_LUA_RESERVED_3 = 1U << 8U,      /*!< make the lua jit lib avaiable*/
    CLIB_LUA_OS = 1U << 9U,       /*!< make the lua os lib avaiable*/
    CLIB_LUA_PACKAGE = 1U << 10U, /*!< make the lua package lib avaiable*/
    CLIB_LUA_TABLE = 1U << 11U,   /*!< make the lua table lib avaiable*/
    CLIB_LUA_OPEN_LIBS
    = (unsigned)CLIB_LUA_OPEN_MATH
    | (unsigned)CLIB_LUA_OPEN_STRING
    /*| (unsigned)CLIB_LUA_STRING_BUFFER*/
    | (unsigned)CLIB_LUA_BASE
    /*| (unsigned)CLIB_LUA_BIT*/
    | (unsigned)CLIB_LUA_DEBUG
    /*| (unsigned)CLIB_LUA_FFI*/
    | (unsigned)CLIB_LUA_IO /*| (unsigned)CLIB_LUA_JIT*/
    | (unsigned)CLIB_LUA_OS | (unsigned)CLIB_LUA_PACKAGE
    | (unsigned)CLIB_LUA_TABLE, /*!< make the lua std libs avaiable */
} clib_lua_options_t;

/**
 * @brief typedef for the values that can be get or set in lua
 */
typedef enum
{
    CLIB_LUA_BOOLEAN,        /*!< a boolean value */
    CLIB_LUA_INTEGER,        /*!< an integer value */
    CLIB_LUA_LIGHT_USERDATA, /*!< light userdata*/
    CLIB_LUA_LITERAL,        /*!< a literal string (const char*,
                                clib_lua_string_len_t) */
    CLIB_LUA_FSTRING,        /*!< a formatted string (const char*, ...) */
    CLIB_LUA_LSTRING,        /*!< a sized string */
    CLIB_LUA_NIL,            /*!< a nil value (PASS NO PARAM)*/
    CLIB_LUA_NUMBER,         /*!< a number value */
    CLIB_LUA_STRING,         /*!< a \0 string */
    CLIB_LUA_VALUE           /*!< an undef. value */
} clib_lua_value_t;

/**
 * @brief typedef for lua state
 */
typedef void clib_lua_t;

/**
 * @brief typedef for lua number
 */
typedef double clib_lua_number_t;

/**
 * @brief typedef for lua boolean
 */
typedef int clib_lua_boolean_t;

/**
 * @brief typedef for lua string length
 */
typedef size_t clib_lua_string_len_t;

/**
 * @brief typedef for lua integer
 */
typedef ptrdiff_t clib_lua_integer_t;

/**
 * @brief create a new lua state
 * @param options options for the lua state
 * @return a new lua state or NULL on error (check clib_error)
 */
clib_lua_t *clib_lua_new (clib_lua_options_t options);

/**
 * @brief run lua code from a string
 *
 * @param state
 * @param code
 * @return clib_error_code_t CLIB_ERRNO_NO_ERROR on success, error code on
 * failure (also sets clib_errno)
 */
clib_error_code_t clib_lua_run (clib_lua_t *state, const char *code);

/**
 * @brief run lua code from a file
 *
 * @param state
 * @param file path to the file
 * @return clib_error_code_t CLIB_ERRNO_NO_ERROR on success, error code on
 * failure (also sets clib_errno)
 */
clib_error_code_t clib_lua_run_file (clib_lua_t *state, const char *file);

/**
 * @brief set a global variable in lua
 *
 * @param state
 * @param name the name of the variable
 * @param type the type of the variable
 * @param ... the values for the initialisation of the variable
 */
void clib_lua_set_global (
    clib_lua_t *state, const char *name, clib_lua_value_t type, ...);

/**
 * @brief get a global variable from lua
 *
 * @param state
 * @param name the name of the variable
 * @param type the type of the variable
 * @param value a pointer that will be set to the value of the variable
 * @return clib_error_code_t CLIB_ERRNO_NO_ERROR on success, error code on
 * error
 */
clib_error_code_t clib_lua_get_global (
    clib_lua_t *state, const char *name, clib_lua_value_t type, void *value);

/**
 * @brief register a function in lua
 *
 * @param state
 * @param name the name of the function
 * @param function the function to register casted to int (*) (clib_lua_t *)
 */
void clib_lua_register_function (
    clib_lua_t *state, const char *name, int (*function) (clib_lua_t *));

/**
 * @brief call a lua function
 *
 * @param state
 * @param name the name of the function
 * @param nargs the number of arguments
 * @param res_type the type of the result
 * @param res a pointer to the result
 * @param ... the arguments in the following format: for n args -> type_0,
 * value_0, type_1, value_1, ..., type_n, value_n
 * @return clib_error_code_t
 */
clib_error_code_t clib_lua_call_function (clib_lua_t *state,
    const char *name,
    int nargs,
    clib_lua_value_t res_type,
    void *res,
    ...);

/**
 * @brief free a lua state
 * @param state the lua state to free
 */
void clib_lua_free (clib_lua_t *state);

#ifdef __cplusplus
}
#endif

#endif /* CLIB_LUA_H */
