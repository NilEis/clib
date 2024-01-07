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

include_directories(${cheat_SOURCE_DIR}/)

add_executable(test_clib_data_structures test_clib_data_structures.c)

add_executable(test_clib_math test_clib_math.c)

add_executable(test_clib_math_inline test_clib_math.c)

target_compile_definitions(test_clib_math_inline PRIVATE CLIB_MATH_INLINE CLIB_MATH_INLINED_EXPECTED=1)

add_executable(test_clib_memory test_clib_memory.c)

add_executable(test_clib_string test_clib_string.c)

add_executable(test_clib_all main.c)

add_dependencies(test_clib_all test_clib_data_structures test_clib_math test_clib_memory test_clib_string)

add_test(NAME "main-test" COMMAND test_clib_all)

add_test(NAME "data_structures-test" COMMAND test_clib_data_structures)

add_test(NAME "math-test" COMMAND test_clib_math)

add_test(NAME "math-test-inline" COMMAND test_clib_math_inline)

add_test(NAME "memory-test" COMMAND test_clib_memory)

add_test(NAME "string-test" COMMAND test_clib_string)

