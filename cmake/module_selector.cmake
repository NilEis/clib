include(CMakeDependentOption)

option(CLIB_INCLUDE_ARRAY "Include dynamic arrays" ON)
if(CLIB_INCLUDE_ARRAY)
  string(APPEND CLIB_SELECTED_MODULES " array")
  list(APPEND CLIB_COMPILE_DEFINITIONS_PUB CLIB_INCLUDE_ARRAY)
  list(APPEND CLIB_SOURCE_FILES_LIST
       ${CMAKE_CURRENT_SOURCE_DIR}/src/clib_array.c)
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

if(NOT MSVC)
  clib_test_if_any_x86(cpuid_supported)
else()
  set(cpuid_supported false)
  message(WARNING "CPUID is not supported on msvc due to msvc asm")
endif()

cmake_dependent_option(CLIB_INCLUDE_CPUID "Include the cpuid module" ON
                       "cpuid_supported" OFF)
if(CLIB_INCLUDE_CPUID)
  string(APPEND CLIB_SELECTED_MODULES " cpuid")
  list(APPEND CLIB_COMPILE_DEFINITIONS_PUB CLIB_INCLUDE_CPUID)
  list(APPEND CLIB_SOURCE_FILES_LIST
       ${CMAKE_CURRENT_SOURCE_DIR}/src/cpuid/clib_cpuid.c)
  list(APPEND CLIB_SOURCE_FILES_LIST
       ${CMAKE_CURRENT_SOURCE_DIR}/src/cpuid/clib_cpuid_leafs.c)
  include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/cpuid/generate_header.cmake)
endif()

option(CLIB_INCLUDE_DATA_STRUCTURES "Include data structures" ON)
if(CLIB_INCLUDE_DATA_STRUCTURES)
  string(APPEND CLIB_SELECTED_MODULES " data_structures")
  list(APPEND CLIB_COMPILE_DEFINITIONS_PUB CLIB_INCLUDE_DATA_STRUCTURES)
  file(GLOB data_structures_files
       ${CMAKE_CURRENT_SOURCE_DIR}/src/data_structures/*.c)
  list(APPEND CLIB_SOURCE_FILES_LIST ${data_structures_files})
endif()

option(CLIB_INCLUDE_FILE "Include support for file functions" ON)
if(CLIB_INCLUDE_FILE)
  string(APPEND CLIB_SELECTED_MODULES " file")
  option(CLIB_FILE_SELECTOR " file selector" ON)
  if(CLIB_FILE_SELECTOR AND NOT EMSCRIPTEN)
    include(FetchContent)
    FetchContent_Declare(
      nfd
      GIT_REPOSITORY https://github.com/btzy/nativefiledialog-extended.git
      GIT_TAG origin/master)
    FetchContent_MakeAvailable(nfd)
    string(APPEND CLIB_SELECTED_MODULES " file_selector")
    list(APPEND CLIB_COMPILE_DEFINITIONS_PUB CLIB_FILE_SELECTOR)
  endif()
  list(APPEND CLIB_COMPILE_DEFINITIONS_PUB CLIB_INCLUDE_FILE)
  list(APPEND CLIB_SOURCE_FILES_LIST
       ${CMAKE_CURRENT_SOURCE_DIR}/src/clib_file.c)
endif()

option(CLIB_INCLUDE_IO "Include io functionality" ON)
if(CLIB_INCLUDE_IO)
  string(APPEND CLIB_SELECTED_MODULES " io")
  list(APPEND CLIB_COMPILE_DEFINITIONS_PUB CLIB_INCLUDE_IO)
  list(APPEND CLIB_SOURCE_FILES_LIST ${CMAKE_CURRENT_SOURCE_DIR}/src/clib_io.c)
endif()

option(CLIB_INCLUDE_SOCKETS "Include functionality for sockets" ON)
if(CLIB_INCLUDE_SOCKETS)
  string(APPEND CLIB_SELECTED_MODULES " sockets")
  if(WIN32)
    list(APPEND CLIB_LIBRARY_LIST Ws2_32)
    list(APPEND CLIB_COMPILE_DEFINITIONS CLIB_SOCKETS_WIN)
  else()
    list(APPEND CLIB_COMPILE_DEFINITIONS CLIB_SOCKETS_UNIX)
  endif()
  list(APPEND CLIB_COMPILE_DEFINITIONS_PUB CLIB_INCLUDE_SOCKETS)
  list(APPEND CLIB_SOURCE_FILES_LIST
       ${CMAKE_CURRENT_SOURCE_DIR}/src/clib_sockets.c)
endif()

option(CLIB_INCLUDE_MATH "Include math functionality" ON)
if(CLIB_INCLUDE_MATH)
  string(APPEND CLIB_SELECTED_MODULES " math")
  list(APPEND CLIB_COMPILE_DEFINITIONS_PUB CLIB_INCLUDE_MATH)
  list(APPEND CLIB_SOURCE_FILES_LIST
       ${CMAKE_CURRENT_SOURCE_DIR}/src/clib_math.c)
endif()

option(CLIB_INCLUDE_STRING "Include string functionality" ON)
if(CLIB_INCLUDE_STRING)
  string(APPEND CLIB_SELECTED_MODULES " string")
  list(APPEND CLIB_COMPILE_DEFINITIONS_PUB CLIB_INCLUDE_STRING)
  list(APPEND CLIB_SOURCE_FILES_LIST
       ${CMAKE_CURRENT_SOURCE_DIR}/src/clib_string.c)
endif()

option(CLIB_INCLUDE_MEMORY "Include memory functionality" ON)
if(CLIB_INCLUDE_MEMORY)
  string(APPEND CLIB_SELECTED_MODULES " memory")
  list(APPEND CLIB_COMPILE_DEFINITIONS_PUB CLIB_INCLUDE_MEMORY)
  list(APPEND CLIB_SOURCE_FILES_LIST
       ${CMAKE_CURRENT_SOURCE_DIR}/src/clib_memory.c)
endif()
