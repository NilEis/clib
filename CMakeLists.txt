cmake_minimum_required(VERSION 3.12.0)
project(
    clib
    VERSION 1.0.0
    HOMEPAGE_URL "https://github.com/NilEis/clib"
    LANGUAGES C
)

set(SOURCE_FILES_LIST
    ${CMAKE_CURRENT_SOURCE_DIR}/src/clib_error.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/clib_data_structures.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/clib_io.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/clib_math.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/clib_memory.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/clib_string.c
)

set(CLIB_HEADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
file(GLOB_RECURSE CLIB_HEADERS ${CLIB_HEADER_DIR}/*.h)

set(LIBRARY_LIST)

set(gnu_comp_options -Werror -Wall -Wextra -Werror=conversion -Wpedantic -pedantic -Werror=maybe-uninitialized -Werror=sign-conversion)

option(INCLUDE_TERMINAL "Include support for terminal functions" TRUE)

option(INCLUDE_SOCKETS "Include functionality for sockets" ON)

option(TCC "Generate tcc makefile in build" ON)

option(BUILD_WITH_DOCS "Generate Docs" OFF)

option(BUILD_TESTS "Build test exe" OFF)

if(INCLUDE_TERMINAL)
    include(FetchContent)
    set(EXTERNAL_INSTALL_LOCATION ${CMAKE_BINARY_DIR}/external)
    FetchContent_Declare(
        c_terminal_repo
        GIT_REPOSITORY https://github.com/NilEis/C-Terminal.git
    )
    FetchContent_MakeAvailable(c_terminal_repo)
    add_subdirectory(${c_terminal_repo_SOURCE_DIR})
    list(APPEND LIBRARY_LIST c_terminal)
endif()

if(INCLUDE_SOCKETS)
    list(APPEND SOURCE_FILES_LIST ${CMAKE_CURRENT_SOURCE_DIR}/src/clib_sockets.c)
    if(WIN32)
        list(APPEND LIBRARY_LIST Ws2_32)
    else()
    endif()
endif()

if(NOT TARGET clib)
add_library(clib ${SOURCE_FILES_LIST})
target_link_libraries(clib ${LIBRARY_LIST})
endif()

if(INCLUDE_SOCKETS)
    list(APPEND SOURCE_FILES_LIST ${CMAKE_CURRENT_SOURCE_DIR}/src/clib_sockets.c)
    if(WIN32)
        target_compile_definitions(clib PRIVATE CLIB_SOCKETS_WIN)
    else()
        target_compile_definitions(clib PRIVATE CLIB_SOCKETS_UNIX)
    endif()
    target_compile_definitions(clib PUBLIC CLIB_SOCKETS)
endif()


if(PROJECT_IS_TOP_LEVEL)
    set_target_properties(clib PROPERTIES C_STANDARD 90 C_STANDARD_REQUIRED True C_EXTENSIONS Off)
    target_compile_definitions(clib PRIVATE USE_BUILTINS=0)
    get_target_property(clib_std clib C_STANDARD)

    if(clib_std EQUAL 90)
        list(APPEND gnu_comp_options -ansi)
    endif()
    
    target_compile_options(clib PRIVATE $<$<OR:$<C_COMPILER_ID:Clang>,$<C_COMPILER_ID:AppleClang>,$<C_COMPILER_ID:GNU>>:${gnu_comp_options}>$<$<C_COMPILER_ID:MSVC>:/W4 /WX /permissive->)
endif()

include_directories(clib PUBLIC ${CLIB_HEADER_DIR})

if(BUILD_WITH_DOCS)
    find_package(Doxygen)
    if(DOXYGEN_FOUND)
        configure_file(${CMAKE_CURRENT_SOURCE_DIR}/doxygen/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
        doxygen_add_docs(clib_doc ${CLIB_HEADERS} ALL WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR} CONFIG_FILE ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile USE_STAMP_FILE COMMENT "Generate documents")
    endif()
endif()

if(BUILD_TESTS AND PROJECT_IS_TOP_LEVEL)
    include(CTest)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tests)
endif()

# add_executable(test_exe src/main.c)
# target_link_libraries(test_exe clib)
# target_include_directories(test_exe PRIVATE include/)

if(TCC)
    set(TCC_OBJECTS)
    set(TCC_OBJECTS_PATH ${CMAKE_CURRENT_BINARY_DIR}/tcc)
    string(REPLACE ";" " " SOURCE_FILES_LIST_STR "${SOURCE_FILES_LIST}")
    set(TCC_SOURCES)
    set(TCC_SOURCES_PATH_ABSOLUTE ${CMAKE_CURRENT_SOURCE_DIR}/src)
    cmake_path(RELATIVE_PATH TCC_SOURCES_PATH_ABSOLUTE BASE_DIRECTORY ${TCC_OBJECTS_PATH} OUTPUT_VARIABLE SRCS_PATH_RELATIVE)
    set(TCC_SOURCES_PATH ${SRCS_PATH_RELATIVE})
    set(TCC_INCLUDE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/include)
    set(TCC_BUILD_RULES)
    foreach(file ${SOURCE_FILES_LIST})
        cmake_path(GET file STEM filename)
        set(TCC_OBJECT ./${filename}.o)
        set(TCC_SOURCE ${TCC_SOURCES_PATH}/${filename}.c)
        list(APPEND TCC_OBJECTS ${TCC_OBJECT})
        list(APPEND TCC_SOURCES ${TCC_SOURCE})
        string(APPEND TCC_BUILD_RULES "${TCC_OBJETC}:")
    endforeach()
    string(REPLACE ";" " " TCC_OBJECTS "${TCC_OBJECTS}")
    string(REPLACE ";" " " TCC_SOURCES "${TCC_SOURCES}")
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/tcc/makefile.in ${CMAKE_CURRENT_BINARY_DIR}/tcc/Makefile)
endif()
