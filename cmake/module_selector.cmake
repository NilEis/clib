include(CMakeDependentOption)
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/src/error")

option(CLIB_INCLUDE_ARRAY "Include dynamic arrays" ON)
if(CLIB_INCLUDE_ARRAY)
  add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/src/array")
endif()

option(CLIB_INCLUDE_TERMINAL "Include support for terminal functions" ON)
if(CLIB_INCLUDE_TERMINAL)
  include(FetchContent)
  FetchContent_Declare(
    c_terminal_repo
    GIT_TAG master
    GIT_REPOSITORY https://github.com/NilEis/C-Terminal.git)
  FetchContent_MakeAvailable(c_terminal_repo)
  string(APPEND CLIB_SELECTED_MODULES " terminal")
  list(APPEND CLIB_LIBRARY_LIST c_terminal)
endif()

clib_test_if_any_x86(cpuid_supported)

cmake_dependent_option(CLIB_INCLUDE_CPUID "Include the cpuid module" ON
                       "cpuid_supported" OFF)
if(CLIB_INCLUDE_CPUID)
  include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/cpuid/generate_header.cmake)
  add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/src/cpuid")
endif()

option(CLIB_INCLUDE_DATA_STRUCTURES "Include data structures" ON)
if(CLIB_INCLUDE_DATA_STRUCTURES)
  add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/src/data_structures")
endif()

option(CLIB_INCLUDE_FILE "Include support for file functions" ON)
if(CLIB_INCLUDE_FILE)
  option(CLIB_FILE_SELECTOR " file selector" OFF)
  if(CLIB_FILE_SELECTOR AND NOT EMSCRIPTEN)
    add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/src/file_selector")
  endif()
  add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/src/file")
endif()

option(CLIB_INCLUDE_IO "Include io functionality" ON)
if(CLIB_INCLUDE_IO)
  add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/src/io")
endif()

option(CLIB_INCLUDE_SOCKETS "Include functionality for sockets" ON)
if(CLIB_INCLUDE_SOCKETS)
  add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/src/sockets")
endif()

option(CLIB_INCLUDE_MATH "Include math functionality" ON)
if(CLIB_INCLUDE_MATH)
  add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/src/math")
endif()

option(CLIB_INCLUDE_STRING "Include string functionality" ON)
if(CLIB_INCLUDE_STRING)
  add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/src/string")
endif()

option(CLIB_INCLUDE_MEMORY "Include memory functionality" ON)
if(CLIB_INCLUDE_MEMORY)
  add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/src/memory")
endif()
