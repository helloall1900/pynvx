cmake_minimum_required(VERSION 2.8.12)
project(pynvx)

add_subdirectory(pybind11)
pybind11_add_module(pynvx src/nvx.cpp)

# cuda header
find_package(CUDA 6.0 REQUIRED)
target_include_directories(pynvx PUBLIC ${CUDA_INCLUDE_DIRS})

# cuda lib
target_link_libraries(pynvx PUBLIC ${CUDA_LIBRARIES})
