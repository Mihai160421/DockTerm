cmake_minimum_required(VERSION 3.10.0)
project(DockTerm VERSION 0.1.0 LANGUAGES C CXX)

file(GLOB_RECURSE SRC_FILES src/*.cpp)

add_executable(DockTerm ${SRC_FILES})

