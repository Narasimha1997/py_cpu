# build external module
add_subdirectory("bindings")

# copy all the py modules to dist folder
file(RELATIVE_PATH DST_DIR ${SRC_DIR} ${CMAKE_CURRENT_SOURCE_DIR})
file(GLOB PYFILES LIST_DIRECTORIES false RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.py")
install(FILES ${PYFILES} DESTINATION ${DST_DIR} COMPONENT "PY") # copy all the py-files in dir