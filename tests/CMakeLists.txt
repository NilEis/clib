cmake_minimum_required(VERSION 3.12.0)

project(
  clib_tests
  VERSION 1.0.0
  HOMEPAGE_URL "https://github.com/NilEis/clib"
  LANGUAGES C)

link_libraries(clib)

include(FetchContent)

FetchContent_Declare(cheat
                     GIT_REPOSITORY https://github.com/Tuplanolla/cheat.git)

macro(add_cpp_test test_name test_string_name test_file)
  if(TEST_CPP)
    configure_file(${test_file}.c ${CMAKE_CURRENT_BINARY_DIR}/${test_name}.cpp
                   COPYONLY)
    add_executable(${test_name}_cpp
                   ${CMAKE_CURRENT_BINARY_DIR}/${test_name}.cpp)
    target_compile_definitions(${test_name}_cpp PRIVATE ${ARGN})
    add_test(NAME "${test_string_name}-cpp" COMMAND test_clib_math_cpp)
    message(STATUS "Adding CPP test ${test_name}_cpp with options: ${ARGN}")
  endif()
endmacro()

macro(add_c_and_cpp_test test_name test_string_name test_file)
  add_executable(${test_name} ${test_file}.c)
  target_compile_definitions(${test_name} PRIVATE ${ARGN})
  add_test(NAME ${test_string_name} COMMAND ${test_name})
  message(STATUS "Adding C test ${test_name}_cpp with options: ${ARGN}")
  add_cpp_test(${test_name} ${test_string_name} ${test_file} ${ARGN})
endmacro()

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
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git)

  FetchContent_GetProperties(catch2)
  if(NOT catch2_POPULATED)
    FetchContent_Populate(catch2)
  endif()

  include_directories(${catch2_SOURCE_DIR}/include/)

endif()

if(CLIB_INCLUDE_CPUID)
  add_c_and_cpp_test(test_clib_cpuid "cpuid-test"
                     test_clib_cpuid)
endif(CLIB_INCLUDE_CPUID)

if(CLIB_INCLUDE_DATA_STRUCTURES)
  add_c_and_cpp_test(test_clib_data_structures "data_structures-test"
                     test_clib_data_structures)
endif(CLIB_INCLUDE_DATA_STRUCTURES)

if(CLIB_INCLUDE_MATH)
  add_c_and_cpp_test(test_clib_math "math-test" test_clib_math USE_BUILTINS=0)

  add_c_and_cpp_test(test_clib_math_inline "math-test-inline" test_clib_math
                     CLIB_MATH_INLINE CLIB_MATH_INLINED_EXPECTED=1)

  add_c_and_cpp_test(test_clib_math_builtins "math-test-builtins"
                     test_clib_math)
endif(CLIB_INCLUDE_MATH)

if(CLIB_INCLUDE_MEMORY)
  add_c_and_cpp_test(test_clib_memory "memory-test" test_clib_memory)
endif(CLIB_INCLUDE_MEMORY)

if(CLIB_INCLUDE_SOCKETS)
  add_c_and_cpp_test(test_clib_sockets "socket-test" test_clib_sockets)
endif(CLIB_INCLUDE_SOCKETS)

if(CLIB_INCLUDE_STRING)
  add_c_and_cpp_test(test_clib_string "string-test" test_clib_string)
endif(CLIB_INCLUDE_STRING)
