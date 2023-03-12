cmake_minimum_required(VERSION 3.12.0)
project(
    clib
    VERSION 1.0.0
    HOMEPAGE_URL "https://github.com/NilEis/clib"
    LANGUAGES C
    )
find_package(Doxygen)

set(SOURCE_FILES_LIST ${CMAKE_CURRENT_SOURCE_DIR}/src/clib_io.c ${CMAKE_CURRENT_SOURCE_DIR}/src/clib_string.c)
option(BUILD_SHARED_LIBS "Build a shared libary" FALSE)

add_library(clib ${SOURCE_FILES_LIST})

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
