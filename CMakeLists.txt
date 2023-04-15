cmake_minimum_required(VERSION 3.12.0)
project(
    clib
    VERSION 1.0.0
    HOMEPAGE_URL "https://github.com/NilEis/clib"
    LANGUAGES C
    )
find_package(Doxygen)

set(SOURCE_FILES_LIST 
 ${CMAKE_CURRENT_SOURCE_DIR}/src/clib_io.c
 ${CMAKE_CURRENT_SOURCE_DIR}/src/clib_string.c
 ${CMAKE_CURRENT_SOURCE_DIR}/include/clib_constructor.h
)

set(LIBRARY_LIST)

option(INCLUDE_TERMINAL "Include support for terminal functions" TRUE)

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

add_library(clib ${SOURCE_FILES_LIST})

target_link_libraries(clib ${LIBRARY_LIST})

set_target_properties(clib PROPERTIES C_STANDARD 11 C_STANDARD_REQUIRED True C_EXTENSIONS Off)

target_compile_options(clib PRIVATE $<$<OR:$<C_COMPILER_ID:Clang>,$<C_COMPILER_ID:AppleClang>,$<C_COMPILER_ID:GNU>>:-Werror -Wall -Wextra -Wconversion -Wsign-conversion>$<$<C_COMPILER_ID:MSVC>:/W4>)

OPTION(BUILD_WITH_DOCS "Generate Docs" OFF)

OPTION(BUILD_TESTS "Build test exe" ON)

include_directories(clib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

if(DOXYGEN_FOUND)
    if(BUILD_WITH_DOCS)
        set(DOXYGEN_USE_MATHJAX YES)
        doxygen_add_docs(clib_doc "include/" ALL COMMENT "Generate documents")
    endif()
endif()

if(BUILD_TESTS)
    add_subdirectory(tests)
endif()
