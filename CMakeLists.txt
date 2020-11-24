
cmake_minimum_required(VERSION 3.0...3.16)

project(
    pycpu
)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

add_subdirectory(cpu_features)
add_subdirectory(pybind11)

include_directories(cpu_features/include)

pybind11_add_module(pycpu src/binding.cc)
