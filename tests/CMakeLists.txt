find_package(Boost REQUIRED COMPONENTS unit_test_framework)
include_directories(${Boost_INCLUDE_DIR} ${CMAKE_SOURCE_DIR}/src/OffObject/include)

link_directories(${Boost_LIBRARY_DIRS})

add_executable(testOffObject testOffObject.cpp)
target_link_libraries(testOffObject ${Boost_LIBRARIES} OffObject)
add_test(name OffObject_testing command testOffObject)