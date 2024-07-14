cmake_minimum_required(VERSION 3.12.0)

project(
  clib_tests
  VERSION 1.0.0
  HOMEPAGE_URL "https://github.com/NilEis/clib"
  LANGUAGES C)

link_libraries(clib)

include(FetchContent)

include(CheckIPOSupported)
check_ipo_supported(RESULT supported OUTPUT error)
if(supported)
  message(STATUS "IPO / LTO enabled")
else()
  message(STATUS "IPO / LTO not supported: <${error}>")
endif()

FetchContent_Declare(cheat
                     GIT_REPOSITORY https://github.com/Tuplanolla/cheat.git)

macro(add_c_test test_name test_string_name test_file)
  add_executable(${test_name} ${test_file}.c)
  target_compile_definitions(${test_name} PRIVATE ${ARGN})
  if(supported)
    set_property(TARGET ${test_name} PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
  endif()
  add_test(NAME ${test_string_name} COMMAND ${test_name})
  message(STATUS "Adding C test ${test_name} with options: ${ARGN}")
endmacro()

if(NOT cheat_POPULATED)
  FetchContent_MakeAvailable(cheat)
endif()

include_directories(${cheat_SOURCE_DIR}/)
message(STATUS "CLIB_INCLUDE_CPUID: ${CLIB_INCLUDE_CPUID}")
if(CLIB_INCLUDE_CPUID AND NOT CLIB_CPUID_UNSUPPORTED)
  add_c_test(test_clib_cpuid "cpuid-test" test_clib_cpuid)
endif(CLIB_INCLUDE_CPUID  AND NOT CLIB_CPUID_UNSUPPORTED)

if(CLIB_INCLUDE_DATA_STRUCTURES)
  add_c_test(test_clib_data_structures "data_structures-test"
             test_clib_data_structures)
endif(CLIB_INCLUDE_DATA_STRUCTURES)

if(CLIB_INCLUDE_LUA)
  add_c_test(test_clib_lua "lua-test" test_clib_lua)
endif(CLIB_INCLUDE_LUA)

if(CLIB_INCLUDE_MATH)
  add_c_test(test_clib_math "math-test" test_clib_math)
endif(CLIB_INCLUDE_MATH)

if(CLIB_INCLUDE_MEMORY)
  add_c_test(test_clib_memory "memory-test" test_clib_memory)
endif(CLIB_INCLUDE_MEMORY)

if(CLIB_INCLUDE_SOCKETS)
  add_c_test(test_clib_sockets "socket-test" test_clib_sockets)
endif(CLIB_INCLUDE_SOCKETS)

if(CLIB_INCLUDE_STRING)
  add_c_test(test_clib_string "string-test" test_clib_string)
endif(CLIB_INCLUDE_STRING)
