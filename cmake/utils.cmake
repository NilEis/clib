set(CLIB_x86_64_defines
    "defined(__x86_64)" "defined(__x86_64__)" "defined(__amd64__)"
    "defined(__amd64)" "defined(_M_X64)")
set(CLIB_x86_32_defines
    "defined(i386)"
    "defined(__i386__)"
    "defined(__i486__)"
    "defined(__i586__)"
    "defined(__i686__)"
    "defined(__i386)"
    "defined(_M_IX86)"
    "defined(_X86_)"
    "defined(__THW_INTEL__)"
    "defined(__I86__)"
    "defined(__INTEL__)")

function(clib_append_preprocessor_if outvar logical_operator)
  set(test_str "")
  string(REPLACE ";" " ${logical_operator} " test_str "${ARGN}")
  set(${outvar}
      ${test_str}
      PARENT_SCOPE)
endfunction()

function(clib_test_if_preprocessor_returns_true outvar logical_operator)
  set(res false)
  set(CLIB_TRY_COMPILE_DEFINE_VALUE "")
  set(TRY_FOLDER "try_run")
  clib_append_preprocessor_if(CLIB_TRY_COMPILE_DEFINE_VALUE
                              "${logical_operator}" ${ARGN})
  set(test_file_out_name "")
  string(MD5 test_file_out_name
             "try_compile_define_template_${CLIB_TRY_COMPILE_DEFINE_VALUE}")
  set(test_file_out_name "${test_file_out_name}")
  set(test_file_path_and_name
      ${CMAKE_CURRENT_BINARY_DIR}/${TRY_FOLDER}/${test_file_out_name}.c)
  configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/try_compile_define_template.c.in
    ${test_file_path_and_name} @ONLY)
  set(tmp_exe_type ${CMAKE_TRY_COMPILE_TARGET_TYPE})
  set(CMAKE_TRY_COMPILE_TARGET_TYPE EXECUTABLE)
  try_run(res compile_res SOURCES ${test_file_path_and_name})
  set(CMAKE_TRY_COMPILE_TARGET_TYPE ${tmp_exe_type})
  set(${outvar}
      ${res}
      PARENT_SCOPE)
endfunction()

function(clib_test_if_preprocessor_returns_true_AND outvar)
  set(res false)
  clib_test_if_preprocessor_returns_true(res "&&" ${ARGN})
  set(${outvar}
      ${res}
      PARENT_SCOPE)
endfunction()

function(clib_test_if_preprocessor_returns_true_OR outvar)
  set(res false)
  clib_test_if_preprocessor_returns_true(res "||" ${ARGN})
  set(${outvar}
      ${res}
      PARENT_SCOPE)
endfunction()

function(clib_test_if_x86_32 outvar)
  set(res false)
  clib_test_if_preprocessor_returns_true_or(res ${CLIB_x86_32_defines})
  if(${res} EQUAL 1)
    message(STATUS "Arch: x86_32")
  endif()
  set(${outvar}
      ${res}
      PARENT_SCOPE)
endfunction()

function(clib_test_if_x86_64 outvar)
  set(res false)
  clib_test_if_preprocessor_returns_true_or(res ${CLIB_x86_64_defines})
  if(${res} EQUAL 1)
    message(STATUS "Arch: x86_64")
  endif()
  set(${outvar}
      ${res}
      PARENT_SCOPE)
endfunction()

function(clib_test_if_any_x86 outvar)
  set(res false)
  clib_test_if_preprocessor_returns_true_or(
    res "${CLIB_x86_64_defines};${CLIB_x86_32_defines}")

  if(${res} EQUAL 1)
    message(STATUS "Arch: x86_undef")
    set(${outvar}
        ${res}
        PARENT_SCOPE)
  else()
    set(${outvar}
        false
        PARENT_SCOPE)
  endif()

endfunction()
