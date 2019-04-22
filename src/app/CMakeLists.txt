include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/src/OffObject/include)
add_executable(OffLoader main.cpp)
target_link_libraries(OffLoader ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} OffObject)
