cmake_minimum_required(VERSION 3.12.0)
project(
    clib_tests
    VERSION 1.0.0
    HOMEPAGE_URL "https://github.com/NilEis/clib"
    LANGUAGES C
    )

add_executable(clib_tests main.c test_clib_string.c)

target_link_libraries(clib_tests clib)

target_include_directories(clib_tests PRIVATE include)
