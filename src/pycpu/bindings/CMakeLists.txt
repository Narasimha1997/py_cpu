get_filename_component(TARGET ${CMAKE_CURRENT_SOURCE_DIR} NAME)

option (BUILD_PIC "Build shared libraries" ON)
set(BUILD_PIC ON)

add_subdirectory(cpu_features)

pybind11_add_module(${TARGET} "binding.cc")
target_link_libraries(${TARGET} PRIVATE cpu_features)

get_filename_component(CURRENT_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)
if(${SRC_DIR} STREQUAL ${CURRENT_SRC_DIR}) 
    set(DST_DIR ".") # if parent is the base folder
else()
    file(RELATIVE_PATH DST_DIR ${SRC_DIR} ${CURRENT_SRC_DIR})
endif()
install(TARGETS ${TARGET} DESTINATION ${DST_DIR} COMPONENT "EXT")