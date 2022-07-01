cmake_minimum_required(VERSION 3.22)
project(BTree)

set(CMAKE_CXX_STANDARD 17)
add_executable(BTree main.cpp)
add_library(_BTree BTree.h BTree.cpp)
target_include_directories(_BTree PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(BTree PUBLIC _BTree)