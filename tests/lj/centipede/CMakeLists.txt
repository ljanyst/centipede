
include_directories(${CPPUNIT_INCLUDE_DIRS})

if(CUDA_FOUND)
  cuda_build_objects(
    CENTIPEDE_TESTS_CUDA_OBJECTS
    centipede_tests
    operators.cu)
endif()


add_library(
  centipede_tests MODULE
  algorithms_test.cc
  operators.cc
  ${CENTIPEDE_TESTS_CUDA_OBJECTS}
)

target_link_libraries(
  centipede_tests
  centipede
  ${CUDA_LIBRARIES}
  ${CPPUNIT_LIBRARIES}
)
