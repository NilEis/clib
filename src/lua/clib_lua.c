#include "clib_lua.h"
#include "clib_error.h"
#include "lauxlib.h"
#include "lua.h"
#include "lualib.h"
#include <stdarg.h>

extern const char *clib_errmsg;

#define INTERNAL_LUA_PROCESS(state, buffer, func)                             \
    do                                                                        \
    {                                                                         \
        if (func (state, buffer) != LUA_OK)                                   \
        {                                                                     \
            clib_errno = CLIB_ERROR_LUA_RUN;                                  \
            clib_errmsg = lua_tostring (state, lua_gettop (state));           \
            lua_pop (state, lua_gettop (state));                              \
            return CLIB_ERROR_LUA_RUN;                                        \
        }                                                                     \
        return CLIB_ERRNO_NO_ERROR;                                           \
    }                                                                         \
    while (0)

#define INTERNAL_LUA_GET_GLOBAL_SPECIAL(                                      \
    state, name, type_name, get_name, type, value)                            \
    do                                                                        \
    {                                                                         \
        if (!lua_is##type_name (state, -1))                                   \
        {                                                                     \
            clib_errno = CLIB_ERROR_LUA_INVALID_TYPE;                         \
            clib_errmsg = lua_tostring (state, -1);                           \
            lua_pop (state, 1);                                               \
            return CLIB_ERROR_LUA_INVALID_TYPE;                               \
        }                                                                     \
        *(type *)(value) = lua_to##get_name (state, -1);                      \
        break;                                                                \
    }                                                                         \
    while (0)

#define INTERNAL_LUA_GET_GLOBAL(state, name, type_name, type, value)          \
    INTERNAL_LUA_GET_GLOBAL_SPECIAL (                                         \
        state, name, type_name, type_name, type, value)

#define INTERNAL_LUA_GET_RET_SPECIAL(state, type_name, get_name, type, value) \
    do                                                                        \
    {                                                                         \
        if (!lua_is##type_name (state, -1))                                   \
        {                                                                     \
            clib_errno = CLIB_ERROR_LUA_INVALID_TYPE;                         \
            clib_errmsg = "Invalid return type";                              \
            return CLIB_ERROR_LUA_INVALID_TYPE;                               \
        }                                                                     \
        *(type *)(value) = lua_to##get_name (state, -1);                      \
    }                                                                         \
    while (0)

#define INTERNAL_LUA_GET_RET(state, type_name, type, value)                   \
    INTERNAL_LUA_GET_RET_SPECIAL (state, type_name, type_name, type, value)

static void internal_openlibs (lua_State *state, clib_lua_options_t options);

clib_lua_t *clib_lua_new (clib_lua_options_t options)
{
    lua_State *state = luaL_newstate ();
    if (state == NULL)
    {
        clib_errno = CLIB_ERROR_LUA_NEW;
        return NULL;
    }
    if (options == CLIB_LUA_OPEN_LIBS)
    {
        luaL_openlibs (state);
    }
    else
    {
        internal_openlibs (state, options);
    }
    return (clib_lua_t *)state;
}

clib_error_code_t clib_lua_run (clib_lua_t *state, const char *code)
{
    INTERNAL_LUA_PROCESS (state, code, luaL_dostring);
}

clib_error_code_t clib_lua_run_file (clib_lua_t *state, const char *file)
{
    INTERNAL_LUA_PROCESS (state, file, luaL_dofile);
}

void clib_lua_set_global (
    clib_lua_t *state, const char *name, clib_lua_value_t type, ...)
{
    va_list args;
    va_start (args, type);
    switch (type)
    {
    case CLIB_LUA_BOOLEAN:
        lua_pushboolean (state, va_arg (args, clib_lua_boolean_t));
        break;
    case CLIB_LUA_INTEGER:
        lua_pushinteger (state, va_arg (args, clib_lua_integer_t));
        break;
    case CLIB_LUA_LIGHT_USERDATA:
        lua_pushlightuserdata (state, va_arg (args, void *));
        break;
    case CLIB_LUA_LITERAL:
        lua_pushlstring (state,
            va_arg (args, const char *),
            va_arg (args, clib_lua_string_len_t));
        break;
    case CLIB_LUA_FSTRING:
        lua_pushvfstring (state, va_arg (args, const char *), args);
        break;
    case CLIB_LUA_LSTRING:
        lua_pushlstring (state,
            va_arg (args, const char *),
            va_arg (args, clib_lua_string_len_t));
        break;
    case CLIB_LUA_NIL:
        lua_pushnil (state);
        break;
    case CLIB_LUA_NUMBER:
        lua_pushnumber (state, va_arg (args, clib_lua_number_t));
        break;
    case CLIB_LUA_STRING:
        lua_pushstring (state, va_arg (args, const char *));
        break;
    case CLIB_LUA_VALUE:
        lua_pushvalue (state, va_arg (args, int));
        break;
    default:
        clib_errno = CLIB_ERROR_LUA_INVALID_TYPE;
        clib_errmsg = "Invalid type";
        va_end (args);
        return;
    }
    va_end (args);
    lua_setglobal (state, name);
}

clib_error_code_t clib_lua_get_global (
    clib_lua_t *state, const char *name, clib_lua_value_t type, void *value)
{
    lua_getglobal (state, name);
    switch (type)
    {
    case CLIB_LUA_BOOLEAN:
        INTERNAL_LUA_GET_GLOBAL (
            state, name, boolean, clib_lua_boolean_t, value);
        break;
    case CLIB_LUA_INTEGER:
        INTERNAL_LUA_GET_GLOBAL (
            state, name, integer, clib_lua_integer_t, value);
        break;
    case CLIB_LUA_LIGHT_USERDATA:
        INTERNAL_LUA_GET_GLOBAL_SPECIAL (
            state, name, lightuserdata, userdata, void *, value);
        break;
    case CLIB_LUA_LITERAL:
        INTERNAL_LUA_GET_GLOBAL (state, name, string, const char *, value);
        break;
    case CLIB_LUA_NUMBER:
        INTERNAL_LUA_GET_GLOBAL (
            state, name, number, clib_lua_number_t, value);
        break;
    case CLIB_LUA_FSTRING:
    case CLIB_LUA_LSTRING:
    case CLIB_LUA_STRING:
        INTERNAL_LUA_GET_GLOBAL (state, name, string, const char *, value);
        break;
    default:
        clib_errno = CLIB_ERROR_LUA_INVALID_TYPE;
        clib_errmsg = "Invalid type";
        return CLIB_ERROR_LUA_INVALID_TYPE;
    }
    return CLIB_ERRNO_NO_ERROR;
}

void clib_lua_register_function (
    clib_lua_t *state, const char *name, int (*function) (clib_lua_t *))
{
    lua_register (state, name, (lua_CFunction)function);
}

clib_error_code_t clib_lua_call_function (clib_lua_t *state,
    const char *name,
    int nargs,
    clib_lua_value_t res_type,
    void *res,
    ...)
{
    int count = 0;
    lua_getglobal (state, name);
    va_list args;
    va_start (args, res);
    for (count = 0; count < nargs; count++)
    {
        switch (va_arg (args, clib_lua_value_t))
        {
        case CLIB_LUA_BOOLEAN:
            lua_pushboolean (state, va_arg (args, clib_lua_boolean_t));
            break;
        case CLIB_LUA_INTEGER:
            lua_pushinteger (state, va_arg (args, clib_lua_integer_t));
            break;
        case CLIB_LUA_LIGHT_USERDATA:
            lua_pushlightuserdata (state, va_arg (args, void *));
            break;
        case CLIB_LUA_LITERAL:
            lua_pushlstring (state,
                va_arg (args, const char *),
                va_arg (args, clib_lua_string_len_t));
            break;
        case CLIB_LUA_FSTRING:
            lua_pushvfstring (state, va_arg (args, const char *), args);
            break;
        case CLIB_LUA_LSTRING:
            lua_pushlstring (state,
                va_arg (args, const char *),
                va_arg (args, clib_lua_string_len_t));
            break;
        case CLIB_LUA_NIL:
            lua_pushnil (state);
            break;
        case CLIB_LUA_NUMBER:
            lua_pushnumber (state, va_arg (args, clib_lua_number_t));
            break;
        case CLIB_LUA_STRING:
            lua_pushstring (state, va_arg (args, const char *));
            break;
        case CLIB_LUA_VALUE:
            lua_pushvalue (state, va_arg (args, int));
            break;
        default:
            clib_errno = CLIB_ERROR_LUA_INVALID_TYPE;
            clib_errmsg = "Invalid type";
            va_end (args);
            return CLIB_ERROR_LUA_INVALID_TYPE;
        }
    }
    va_end (args);
    if (lua_pcall (state, nargs, 1, 0) != LUA_OK)
    {
        clib_errno = CLIB_ERROR_LUA_RUN;
        clib_errmsg = lua_tostring (state, lua_gettop (state));
        lua_pop (state, lua_gettop (state));
        return CLIB_ERROR_LUA_RUN;
    }
    switch (res_type)
    {
    case CLIB_LUA_BOOLEAN:
        INTERNAL_LUA_GET_RET (state, boolean, clib_lua_boolean_t, res);
        break;
    case CLIB_LUA_INTEGER:
        INTERNAL_LUA_GET_RET (state, integer, clib_lua_integer_t, res);
        break;
    case CLIB_LUA_LIGHT_USERDATA:
        INTERNAL_LUA_GET_RET_SPECIAL (
            state, lightuserdata, userdata, void *, res);
        break;
    case CLIB_LUA_STRING:
        INTERNAL_LUA_GET_RET (state, string, const char *, res);
        break;
    case CLIB_LUA_NIL:
        break;
    case CLIB_LUA_NUMBER:
        INTERNAL_LUA_GET_RET (state, number, clib_lua_number_t, res);
        break;
    default:
        clib_errno = CLIB_ERROR_LUA_INVALID_TYPE;
        clib_errmsg = "Invalid type";
        return CLIB_ERROR_LUA_INVALID_TYPE;
    }
    return CLIB_ERRNO_NO_ERROR;
}

void clib_lua_free (clib_lua_t *state) { lua_close ((lua_State *)state); }

static void internal_openlibs (lua_State *state, clib_lua_options_t options)
{
    if (options & (unsigned)CLIB_LUA_OPEN_MATH)
    {
        luaopen_math (state);
    }
    if (options & (unsigned)CLIB_LUA_OPEN_STRING)
    {
        luaopen_string (state);
    }
    /*if (options & (unsigned)CLIB_LUA_STRING_BUFFER)
    {
        luaopen_string_buffer (state);
    }*/
    if (options & (unsigned)CLIB_LUA_BASE)
    {
        luaopen_base (state);
    }
    /*if (options & (unsigned)CLIB_LUA_BIT)
    {
        luaopen_bit (state);
    }*/
    if (options & (unsigned)CLIB_LUA_DEBUG)
    {
        luaopen_debug (state);
    }
    /*if (options & (unsigned)CLIB_LUA_FFI)
    {
        luaopen_ffi (state);
    }*/
    if (options & (unsigned)CLIB_LUA_IO)
    {
        luaopen_io (state);
    }
    /*if (options & (unsigned)CLIB_LUA_JIT)
    {
        luaopen_jit (state);
    }*/
    if (options & (unsigned)CLIB_LUA_OS)
    {
        luaopen_os (state);
    }
    if (options & (unsigned)CLIB_LUA_PACKAGE)
    {
        luaopen_package (state);
    }
    if (options & (unsigned)CLIB_LUA_TABLE)
    {
        luaopen_table (state);
    }
}
