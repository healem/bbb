cmake_minimum_required(VERSION 2.8.8)
project(bbb)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(src)
add_subdirectory(src)
