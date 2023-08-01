cmake_minimum_required(VERSION 3.0)
project(json-parser)

set(CMAKE_CXX_STANDARD 11)

# 添加头文件
include_directories(./include)

# file(GLOB_RECURSE SOURCES "src/*.cpp")

# 需编译的源文件
add_executable(main ${SOURCES} main.cpp)