find_package(Python REQUIRED)

set(CSV_SRC ${CMAKE_CURRENT_SOURCE_DIR}/cmake/cpuid/table.csv)
set(CSV_SRC_CLEAN ${CMAKE_CURRENT_SOURCE_DIR}/cmake/cpuid/table_clean.csv)
set(CSV_DEST ${CMAKE_CURRENT_SOURCE_DIR}/include/clib_cpuid_leafs.h)
set(CSV_SRC_DEST ${CMAKE_CURRENT_SOURCE_DIR}/src/cpuid/clib_cpuid_leafs.c)
set(CSV_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/cmake/cpuid/generate_header.py)

file(STRINGS ${CSV_SRC} LINES)
file(WRITE ${CSV_SRC_CLEAN} "")
foreach(LINE IN LISTS LINES)
  if(NOT ("${LINE}" MATCHES "^#") AND NOT ("${LINE}" MATCHES "^$"))
    file(APPEND ${CSV_SRC_CLEAN} "${LINE}\n")
  endif()
endforeach()

message(CONFIGURE_LOG "Generating header for cpuid")
set_property(
  DIRECTORY
  APPEND
  PROPERTY CMAKE_CONFIGURE_DEPENDS ${CSV_SCRIPT})

set_property(
  DIRECTORY
  APPEND
  PROPERTY CMAKE_CONFIGURE_DEPENDS ${CSV_SRC})

execute_process(COMMAND ${Python_EXECUTABLE} ${CSV_SCRIPT} ${CSV_SRC_CLEAN}
                        ${CSV_DEST} ${CSV_SRC_DEST})