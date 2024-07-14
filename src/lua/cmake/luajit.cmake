include(FetchContent)
set(LUA_USE_C89 ON CACHE BOOL "" FORCE)
FetchContent_Declare(
  lua
  GIT_REPOSITORY https://gitlab.com/codelibre/lua/lua-cmake.git
  GIT_TAG origin/lua-cmake-5.4)
FetchContent_MakeAvailable(lua)
