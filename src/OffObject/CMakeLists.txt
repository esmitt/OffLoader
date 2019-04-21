file(GLOB SOURCES "src/*.cpp")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")

add_library(OffObject SHARED ${SOURCES})
target_link_libraries(OffObject ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})

