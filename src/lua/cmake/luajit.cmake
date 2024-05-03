include(GNUInstallDirs)
include(FetchContent)
include(ExternalProject)
FetchContent_Declare(
  luajit
  GIT_REPOSITORY https://github.com/LuaJIT/LuaJIT.git
  GIT_TAG origin/v2.1)

FetchContent_GetProperties(luajit)

if(NOT luajit_POPULATED)
  FetchContent_Populate(luajit)
  file(GLOB luajit_headers ${luajit_SOURCE_DIR}/src/*.h)
  # if windows
  if(WIN32)
    if(MSVC)
      set(luajit_lib_name
          ${CMAKE_STATIC_LIBRARY_PREFIX}lua51${CMAKE_STATIC_LIBRARY_SUFFIX})
    else()
      set(luajit_lib_name
          ${CMAKE_STATIC_LIBRARY_PREFIX}luajit-5.1.dll${CMAKE_STATIC_LIBRARY_SUFFIX}
      )
    endif()
  else()
    set(luajit_lib_name
        ${CMAKE_STATIC_LIBRARY_PREFIX}luajit${CMAKE_STATIC_LIBRARY_SUFFIX})
  endif()
  find_program(
    MAKE_EXECUTABLE
    NAMES gmake mingw32-make make NAMES_PER_DIR
    DOC "GNU Make" REQUIRED)

  if(MSVC)
    ExternalProject_Add(
      luajit
      SOURCE_DIR ${luajit_SOURCE_DIR}
      CONFIGURE_COMMAND ""
      BUILD_COMMAND cd "${luajit_SOURCE_DIR}/src" && msvcbuild.bat
      INSTALL_COMMAND ""
      BUILD_BYPRODUCTS ${luajit_SOURCE_DIR}/src/${luajit_lib_name})
  else()
    ExternalProject_Add(
      luajit
      SOURCE_DIR ${luajit_SOURCE_DIR}
      CONFIGURE_COMMAND ""
      BUILD_COMMAND ${MAKE_EXECUTABLE} CC=${CMAKE_C_COMPILER} -C
                    ${luajit_SOURCE_DIR}/src -j 4
      INSTALL_COMMAND ""
      BUILD_BYPRODUCTS ${luajit_SOURCE_DIR}/src/${luajit_lib_name})
  endif()
  set(lualib ${luajit_SOURCE_DIR}/src/${luajit_lib_name})
  set(luaInclude ${luajit_SOURCE_DIR}/src)
  if(WIN32)
    add_custom_command(
      TARGET luajit
      POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy ${luajit_SOURCE_DIR}/src/lua51.dll
              ${CMAKE_BINARY_DIR}/lua51.dll)
  endif()
endif()
