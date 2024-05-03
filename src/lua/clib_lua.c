#include "clib_lua.h"
#include "clib_error.h"
#include "lauxlib.h"
#include "lua.h"
#include "lualib.h"

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
        if (options & (unsigned)CLIB_LUA_OPEN_MATH)
        {
            luaopen_math (state);
        }
        if (options & (unsigned)CLIB_LUA_OPEN_STRING)
        {
            luaopen_string (state);
        }
        if (options & (unsigned)CLIB_LUA_STRING_BUFFER)
        {
            luaopen_string_buffer (state);
        }
        if (options & (unsigned)CLIB_LUA_BASE)
        {
            luaopen_base (state);
        }
        if (options & (unsigned)CLIB_LUA_BIT)
        {
            luaopen_bit (state);
        }
        if (options & (unsigned)CLIB_LUA_DEBUG)
        {
            luaopen_debug (state);
        }
        if (options & (unsigned)CLIB_LUA_FFI)
        {
            luaopen_ffi (state);
        }
        if (options & (unsigned)CLIB_LUA_IO)
        {
            luaopen_io (state);
        }
        if (options & (unsigned)CLIB_LUA_JIT)
        {
            luaopen_jit (state);
        }
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
    return (clib_lua_t *)state;
}

void clib_lua_free (clib_lua_t *state) { lua_close ((lua_State *)state); }
