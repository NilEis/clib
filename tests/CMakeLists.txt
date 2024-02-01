cmake_minimum_required(VERSION 3.12.0)

project(
  clib_tests
  VERSION 1.0.0
  HOMEPAGE_URL "https://github.com/NilEis/clib"
  LANGUAGES C
)

link_libraries(clib)

include(FetchContent)

FetchContent_Declare(
  cheat
  GIT_REPOSITORY https://github.com/Tuplanolla/cheat.git
)

if(NOT cheat_POPULATED)
  FetchContent_MakeAvailable(cheat)
endif()

include_directories(${cheat_SOURCE_DIR}/)

option(TEST_CPP "Test also on CPP" ON)

if(TEST_CPP)
  enable_language(CXX)
  FetchContent_Declare(
    catch2
    GIT_TAG Catch1.x
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  )
  
  FetchContent_GetProperties(catch2)
  if(NOT catch2_POPULATED)
    FetchContent_Populate(catch2)
  endif()
  
  include_directories(${catch2_SOURCE_DIR}/include/)

endif()

add_executable(test_clib_data_structures test_clib_data_structures.c)

add_executable(test_clib_math test_clib_math.c)

if(TEST_CPP)
  configure_file(test_clib_math.c ${CMAKE_CURRENT_BINARY_DIR}/test_clib_math.cpp COPYONLY)
  add_executable(test_clib_math_cpp ${CMAKE_CURRENT_BINARY_DIR}/test_clib_math.cpp)
endif()

target_compile_definitions(test_clib_math PRIVATE USE_BUILTINS=0)

add_executable(test_clib_math_inline test_clib_math.c)

target_compile_definitions(test_clib_math_inline PRIVATE CLIB_MATH_INLINE CLIB_MATH_INLINED_EXPECTED=1)

add_executable(test_clib_math_builtins test_clib_math.c)

add_executable(test_clib_memory test_clib_memory.c)

if(INCLUDE_SOCKETS)
  add_executable(test_clib_sockets test_clib_sockets.c)
endif()

add_executable(test_clib_string test_clib_string.c)

add_executable(test_clib_all main.c)

if(INCLUDE_SOCKETS)
  add_dependencies(test_clib_all test_clib_sockets)
endif()

add_dependencies(test_clib_all clib test_clib_data_structures test_clib_math test_clib_math_builtins test_clib_math_inline test_clib_memory test_clib_string)

add_test(NAME "main-test" COMMAND test_clib_all)

add_test(NAME "data_structures-test" COMMAND test_clib_data_structures)

add_test(NAME "math-test" COMMAND test_clib_math)

if(TEST_CPP)
  add_test(NAME "math-test-cpp" COMMAND test_clib_math_cpp)
endif()

add_test(NAME "math-test-inline" COMMAND test_clib_math_inline)

add_test(NAME "math-test-builtins" COMMAND test_clib_math_builtins)

add_test(NAME "memory-test" COMMAND test_clib_memory)

add_test(NAME "string-test" COMMAND test_clib_string)

