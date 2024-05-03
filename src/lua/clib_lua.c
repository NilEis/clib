#include "clib_lua.h"
#include "clib_error.h"
#include "lauxlib.h"
#include "lua.h"
#include "lualib.h"

void hello_world (void)
{
    lua_State *L = luaL_newstate ();
    luaL_openlibs (L);
    luaL_dostring (L, "print('Hello World!')");
}