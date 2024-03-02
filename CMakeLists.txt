cmake_minimum_required(VERSION 2.8.12)
project(_pynvx)

add_subdirectory(pybind11)
pybind11_add_module(_pynvx src/nvx.cpp)

# cuda header
find_package(CUDA 6.0 REQUIRED)
target_include_directories(_pynvx PUBLIC ${CUDA_INCLUDE_DIRS})

# cuda lib
target_link_libraries(_pynvx PUBLIC ${CUDA_LIBRARIES})
