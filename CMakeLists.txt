cmake_minimum_required(VERSION 3.5)
project(ThreadPool)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp ThreadPool.cpp ThreadPool.h Thread.cpp Thread.h)

add_executable(ThreadPool ${SOURCE_FILES})
target_link_libraries(ThreadPool pthread)