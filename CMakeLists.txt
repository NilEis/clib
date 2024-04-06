cmake_minimum_required(VERSION 3.12.0)
project(
  clib
  VERSION 1.0.0
  HOMEPAGE_URL "https://github.com/NilEis/clib"
  LANGUAGES C)

set(CLIB_SOURCE_FILES_LIST ${CMAKE_CURRENT_SOURCE_DIR}/src/clib_error.c)

set(CLIB_MODULES_LIST)
set(CLIB_LIBRARY_LIST)
set(CLIB_DEP_FILES)
set(CLIB_COMPILE_DEFINITIONS)
set(CLIB_COMPILE_DEFINITIONS_PUB)

set(CLIB_SELECTED_MODULES "")

set(CLIB_HEADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
file(GLOB_RECURSE CLIB_HEADERS ${CLIB_HEADER_DIR}/*.h)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/utils.cmake)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/options.cmake)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/module_selector.cmake)

set(CLIB_COMPILE_OPTIONS)

if(CMAKE_C_COMPILER_ID MATCHES "Clang|GNU")
  list(
    APPEND
    CLIB_COMPILE_OPTIONS
    -Werror
    -Wall
    -Wextra
    -Wconversion
    -Wpedantic
    -pedantic
    -Werror=sign-conversion)
  list(APPEND CLIB_LIBRARY_LIST m)
  if(CMAKE_C_COMPILER_ID STREQUAL "Clang")
    list(APPEND CLIB_COMPILE_OPTIONS -Werror=uninitialized)
  else()
    list(APPEND CLIB_COMPILE_OPTIONS -Werror=maybe-uninitialized)
  endif()
elseif(CMAKE_C_COMPILER_ID STREQUAL "Intel")
  list(APPEND CLIB_COMPILE_OPTIONS -w3)
elseif(CMAKE_C_COMPILER_ID STREQUAL "MSVC")
  list(APPEND CLIB_COMPILE_OPTIONS /W4 /WX /permissive-)
endif()

if(NOT TARGET clib)
  if(CLIB_FILE_SELECTOR AND NOT EMSCRIPTEN)
    include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/file_selector.cmake)
  endif()
  if(CLIB_OBJECT_LIB)
    add_library(clib OBJECT ${CLIB_SOURCE_FILES_LIST} ${CLIB_HEADERS})
  else()
    add_library(clib ${CLIB_SOURCE_FILES_LIST} ${CLIB_HEADERS})
  endif()
  target_link_libraries(clib ${CLIB_LIBRARY_LIST})
  target_compile_definitions(clib PRIVATE ${CLIB_COMPILE_DEFINITIONS})
  target_compile_definitions(clib PUBLIC ${CLIB_COMPILE_DEFINITIONS_PUB})
  message(STATUS "clib library created with:${CLIB_SELECTED_MODULES}")
endif()

if(PROJECT_IS_TOP_LEVEL)
  set_target_properties(
    clib
    PROPERTIES C_STANDARD 90
               C_STANDARD_REQUIRED True
               C_EXTENSIONS Off)
  target_compile_definitions(clib PRIVATE USE_BUILTINS=0 CLIB_ANSI=1)
  get_target_property(clib_std clib C_STANDARD)

  if(clib_std EQUAL 90 AND CMAKE_C_COMPILER_ID MATCHES "Clang|GNU")
    list(APPEND CLIB_COMPILE_OPTIONS -ansi)
  endif()

  if(CLIB_OBJECT_LIB)
    add_executable(test_exe src/main.c $<TARGET_OBJECTS:clib>)
  else()
    add_executable(test_exe src/main.c)
  endif()
  target_link_libraries(test_exe clib)
  target_include_directories(test_exe PRIVATE include/)
endif()

target_compile_options(clib PRIVATE ${CLIB_COMPILE_OPTIONS})

target_include_directories(clib PUBLIC ${CLIB_HEADER_DIR})

if(BUILD_WITH_DOCS)
  find_package(Doxygen)
  if(DOXYGEN_FOUND)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/doxygen/Doxyfile.in
                   ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
    doxygen_add_docs(
      clib_doc ${CLIB_HEADERS} ALL
      WORKING_DIRECTORY
        ${CMAKE_CURRENT_BINARY_DIR}
        CONFIG_FILE ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile USE_STAMP_FILE
      COMMENT "Generate documents")
  endif()
endif()

if(BUILD_TESTS AND PROJECT_IS_TOP_LEVEL)
  include(CTest)
  add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tests)
endif()
