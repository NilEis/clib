add_library(clib_file_selector OBJECT
            ${CMAKE_CURRENT_SOURCE_DIR}/src/clib_file_selector.c)
list(APPEND SOURCE_FILES_LIST $<TARGET_OBJECTS:clib_file_selector>)
target_link_libraries(clib_file_selector PRIVATE nfd)
target_compile_definitions(clib_file_selector
                           PRIVATE ${CLIB_COMPILE_DEFINITIONS})
target_compile_definitions(clib_file_selector
                           PUBLIC ${CLIB_COMPILE_DEFINITIONS_PUB})
if(PROJECT_IS_TOP_LEVEL)
  set_target_properties(
    clib_file_selector
    PROPERTIES C_STANDARD 99
               C_STANDARD_REQUIRED True
               C_EXTENSIONS Off)
  target_compile_options(clib_file_selector PRIVATE ${CLIB_COMPILE_OPTIONS})

  target_include_directories(clib_file_selector PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
endif()
