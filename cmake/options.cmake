option(TCC "Generate tcc makefile in build" OFF)

option(BUILD_WITH_DOCS "Generate Docs" OFF)

option(BUILD_TESTS "Build test exe" OFF)

option(CLIB_OBJECT_LIB "Makes Clib an object library" OFF)

option(SUPPORT_CLANGD "Support clangd" ON)
if(SUPPORT_CLANGD)
  set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
  set(CLANGD_SRC ${CMAKE_CURRENT_SOURCE_DIR}/cmake/.clangd.in)
  set(CLANGD_DEST ${CMAKE_CURRENT_SOURCE_DIR}/.clangd)
  configure_file(${CLANGD_SRC} ${CLANGD_DEST} @ONLY)
endif()
