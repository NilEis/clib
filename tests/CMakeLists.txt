cmake_minimum_required(VERSION 3.12.0)
include(FetchContent)

FetchContent_Declare(
  cheat
  GIT_REPOSITORY https://github.com/Tuplanolla/cheat.git
)

if(NOT cheat_POPULATED)
    FetchContent_MakeAvailable(cheat)
endif()

project(
    clib_tests
    VERSION 1.0.0
    HOMEPAGE_URL "https://github.com/NilEis/clib"
    LANGUAGES C
)

link_libraries(clib)

include_directories(include/ ${cheat_SOURCE_DIR}/)

add_executable(test_clib_string test_clib_string.c)