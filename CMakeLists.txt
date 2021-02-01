cmake_minimum_required(VERSION 3.0)
project(my3d)
set(CMAKE_CXX_STANDARD 11)
add_subdirectory(gl)
include_directories(gl)

add_executable(my3d main.cpp)
target_link_libraries(my3d GL)