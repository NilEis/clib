option(TCC "Generate tcc makefile in build" OFF)

option(BUILD_WITH_DOCS "Generate Docs" OFF)

option(BUILD_TESTS "Build test exe" OFF)

option(SUPPORT_CLANGD "Support clangd" ON)
if(SUPPORT_CLANGD)
  set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
  file(TOUCH ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json)
  file(CREATE_LINK ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json
       ${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json COPY_ON_ERROR)
endif()
