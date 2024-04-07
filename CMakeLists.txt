cmake_minimum_required(VERSION 3.12.0)
project(
  clib
  VERSION 1.0.0
  HOMEPAGE_URL "https://github.com/NilEis/clib"
  LANGUAGES C)

set(CLIB_SOURCE_FILES_LIST)

set(CLIB_MODULES_LIST)
set(CLIB_SELECTED_MODULES_NO_ANSI)
set(CLIB_CLEAN_FILES)
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
  list(APPEND CLIB_COMPILE_OPTIONS /W3 /WX)
  list(APPEND CLIB_COMPILE_DEFINITIONS _CRT_SECURE_NO_WARNINGS)
endif()

if(NOT TARGET clib)
  set(CLIB_ALL_MODULES ${CLIB_SELECTED_MODULES_NO_ANSI} ${CLIB_MODULES_LIST})
  if(CLIB_OBJECT_LIB)
    add_library(clib OBJECT ${CLIB_SOURCE_FILES_LIST} ${CLIB_HEADERS})
  else()
    add_library(clib ${CLIB_SOURCE_FILES_LIST} ${CLIB_HEADERS})
  endif()

  set_property(
    TARGET clib
    APPEND
    PROPERTY ADDITIONAL_CLEAN_FILES ${CLIB_CLEAN_FILES})

  list(APPEND CLIB_MODULES_LIST clib)

  foreach(module ${CLIB_ALL_MODULES})
    target_compile_definitions(${module} PRIVATE ${CLIB_COMPILE_DEFINITIONS})
    target_compile_definitions(${module} PUBLIC ${CLIB_COMPILE_DEFINITIONS_PUB})
    target_include_directories(${module} PUBLIC ${CLIB_HEADER_DIR})
    list(APPEND CLIB_LIBRARY_LIST "$<TARGET_OBJECTS:${module}>")
  endforeach(module ${CLIB_SELECTED_MODULES_NO_ANSI})

  target_link_libraries(clib PUBLIC ${CLIB_LIBRARY_LIST})
  target_compile_definitions(clib PRIVATE ${CLIB_COMPILE_DEFINITIONS})
  target_compile_definitions(clib PUBLIC ${CLIB_COMPILE_DEFINITIONS_PUB})
  target_include_directories(clib PUBLIC ${CLIB_HEADER_DIR})

  foreach(module ${CLIB_MODULES_LIST})
    get_target_property(clib_std ${module} C_STANDARD)
    if(PROJECT_IS_TOP_LEVEL)
      set_target_properties(
        ${module}
        PROPERTIES C_STANDARD 90
                   C_STANDARD_REQUIRED True
                   C_EXTENSIONS Off)
      target_compile_definitions(${module} PRIVATE USE_BUILTINS=0 CLIB_ANSI=1)
      if(clib_std EQUAL 90)
        if(CMAKE_C_COMPILER_ID MATCHES "Clang|GNU")
          list(APPEND CLIB_COMPILE_OPTIONS -ansi)
        elseif(CMAKE_C_COMPILER_ID STREQUAL "MSVC")
          list(APPEND CLIB_COMPILE_OPTIONS /permissive-)
        endif()
      endif()
    endif()
  endforeach(module ${CLIB_MODULES_LIST})
  message(STATUS "clib library created with:${CLIB_SELECTED_MODULES}")
endif()

if(PROJECT_IS_TOP_LEVEL)
  if(CLIB_OBJECT_LIB)
    add_executable(test_exe src/main.c $<TARGET_OBJECTS:clib>)
  else()
    add_executable(test_exe src/main.c)
  endif()
  target_link_libraries(test_exe clib)
  target_include_directories(test_exe
                             PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/)
endif()

target_compile_options(clib PRIVATE ${CLIB_COMPILE_OPTIONS})

if(BUILD_WITH_DOCS)
  find_package(Doxygen)
  if(DOXYGEN_FOUND)

    set(DOXYGEN_PREDEFINED_LIST ${CLIB_COMPILE_DEFINITIONS})
    list(APPEND DOXYGEN_PREDEFINED_LIST ${CLIB_COMPILE_DEFINITIONS_PUB})
    set(DOXYGEN_PREDEFINED "")

    # itertate through the list of preprocessor definitions and append them to
    # the DOXYGEN_PREDEFINED in the following format NAME=VALUE \\n
    foreach(def ${DOXYGEN_PREDEFINED_LIST})
      if(NOT "${def}" MATCHES "^[a-zA-Z0-9_]=[a-zA-Z0-9_]+$")
        string(APPEND DOXYGEN_PREDEFINED "\t${def}= \\\n")
      else()
        string(APPEND DOXYGEN_PREDEFINED "\t${def} \\\n")
      endif()
    endforeach()

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
