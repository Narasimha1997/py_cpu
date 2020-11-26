cmake_minimum_required(VERSION 3.5)
project(pybind_example)

# when installing directly in CMake, redirect its intall root to dist dir
if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set (CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/dist" CACHE PATH "default install path" FORCE )
endif()

add_subdirectory(pybind11)
add_subdirectory(src)