
include(CUDAHelpers)

#-------------------------------------------------------------------------------
# Compile with CUDA
#-------------------------------------------------------------------------------
if(CUDA_FOUND)
  cuda_build_objects(
    CENTIPEDE_CUDA_OBJECTS
    centipede
    algorithms_impl.cu)
endif()

#-------------------------------------------------------------------------------
# Compile withoug CUDA
#-------------------------------------------------------------------------------
add_library(
  centipede SHARED
  algorithms_impl.cc
  ${CENTIPEDE_CUDA_OBJECTS})

target_link_libraries(
  centipede
  ${CUDA_LIBRARIES})
