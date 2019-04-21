cmake_minimum_required(VERSION 3.13)
project(OffDisplay)

set (CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

add_subdirectory(src)

enable_testing()
add_subdirectory(tests)

