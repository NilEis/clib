option(CLIB_INCLUDE_TERMINAL "Include support for terminal functions" ON)
if(CLIB_INCLUDE_TERMINAL)
  include(FetchContent)
  set(EXTERNAL_INSTALL_LOCATION ${CMAKE_BINARY_DIR}/external)
  FetchContent_Declare(
    c_terminal_repo
    GIT_TAG master
    GIT_REPOSITORY https://github.com/NilEis/C-Terminal.git)
  FetchContent_MakeAvailable(c_terminal_repo)
  string(APPEND CLIB_SELECTED_MODULES " terminal")
  add_subdirectory(${c_terminal_repo_SOURCE_DIR})
  list(APPEND CLIB_LIBRARY_LIST c_terminal)
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
    list(APPEND CLIB_LIBRARY_LIST nfd)
    list(APPEND CLIB_COMPILE_DEFINITIONS_PUB CLIB_FILE_SELECTOR)
  endif()
  list(APPEND CLIB_COMPILE_DEFINITIONS_PUB CLIB_INCLUDE_FILE)
endif()

option(CLIB_INCLUDE_DATA_STRUCTURES "Include data structures" ON)
if(CLIB_INCLUDE_DATA_STRUCTURES)
  string(APPEND CLIB_SELECTED_MODULES " data_structures")
  list(APPEND CLIB_COMPILE_DEFINITIONS_PUB CLIB_INCLUDE_DATA_STRUCTURES)
endif()

option(CLIB_INCLUDE_IO "Include io functionality" ON)
if(CLIB_INCLUDE_IO)
  string(APPEND CLIB_SELECTED_MODULES " io")
  list(APPEND CLIB_COMPILE_DEFINITIONS_PUB CLIB_INCLUDE_IO)
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
endif()

option(CLIB_INCLUDE_MATH "Include math functionality" ON)
if(CLIB_INCLUDE_MATH)
  string(APPEND CLIB_SELECTED_MODULES " math")
  list(APPEND CLIB_COMPILE_DEFINITIONS_PUB CLIB_INCLUDE_MATH)
endif()

option(CLIB_INCLUDE_STRING "Include string functionality" ON)
if(CLIB_INCLUDE_STRING)
  string(APPEND CLIB_SELECTED_MODULES " string")
  list(APPEND CLIB_COMPILE_DEFINITIONS_PUB CLIB_INCLUDE_STRING)
endif()

option(CLIB_INCLUDE_MEMORY "Include memory functionality" ON)
if(CLIB_INCLUDE_MEMORY)
  string(APPEND CLIB_SELECTED_MODULES " memory")
  list(APPEND CLIB_COMPILE_DEFINITIONS_PUB CLIB_INCLUDE_MEMORY)
endif()
