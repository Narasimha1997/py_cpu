
cmake_minimum_required(VERSION 3.0...3.16)

project(
    pycpu
)

#enable this to build position-independant-code for the libcpu_features.a
option (BUILD_PIC "Build shared libraries" ON)
set(BUILD_PIC ON)

add_subdirectory(cpu_features)
add_subdirectory(pybind11)

include_directories(cpu_features/include)

pybind11_add_module(pycpu binding.cc)
target_link_libraries(pycpu PRIVATE cpu_features)
#set_target_properties(pycpu 
#    PROPERTIES
#    LIBRARY_OUTPUT_DIRECTORY ${PIP_PACKAGE_PATH}
#)

add_custom_command(TARGET pycpu POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:pycpu> __init__.py
)
