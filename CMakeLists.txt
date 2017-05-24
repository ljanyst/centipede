project(centipede)
cmake_minimum_required(VERSION 3.8)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

find_package(CUDA)

if(CUDA_FOUND)
  list(APPEND CUDA_NVCC_FLAGS -gencode arch=compute_53,code=sm_53)
  list(APPEND CUDA_NVCC_FLAGS -Xcompiler -fPIC)
  set(CUDA_SEPARABLE_COMPILATION ON)
  add_definitions(-DHAVE_CUDA)
else()
  set(CUDA_LIBRARIES "")
endif()

find_package(CPPUnit)

list(APPEND CMAKE_CXX_FLAGS "-Wl,-z,defs -std=c++11")
include_directories(${PROJECT_SOURCE_DIR}/src)

add_subdirectory(src)

if(CPPUNIT_FOUND)
  add_subdirectory(tests)
endif()
