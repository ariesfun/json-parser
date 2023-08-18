cmake_minimum_required(VERSION 3.0)
project(json-parser)

set(CMAKE_CXX_STANDARD 11)

# 添加头文件
include_directories(./include)

# 添加源文件
aux_source_directory(./src DIR_SRCS)

# 需编译的源文件
add_executable(main main.cpp ${DIR_SRCS})