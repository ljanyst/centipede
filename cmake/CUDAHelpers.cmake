
macro(cuda_build_objects objects target)
  cuda_compile(
    ${objects}
    ${ARGN})
  cuda_compute_separable_compilation_object_file_name(
    SEP_COMP_OBJ_TMP
    ${target}
    ${${objects}})
  cuda_link_separable_compilation_objects(
    ${SEP_COMP_OBJ_TMP}
    ${target}
    ""
    ${${objects}})
  list(APPEND ${objects} ${SEP_COMP_OBJ_TMP})
endmacro()
