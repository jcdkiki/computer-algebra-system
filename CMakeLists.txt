cmake_minimum_required(VERSION 3.16)
project(cas)
set(CMAKE_CXX_STANDARD 17)

add_executable(cas)
target_include_directories(cas PRIVATE include)
add_subdirectory(src)
