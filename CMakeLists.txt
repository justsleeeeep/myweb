cmake_minimum_required(VERSION 3.10)
project(my_cpp_web_server CXX) # 将项目名称改为 my_cpp_web_server，如果之前不是的话

set(CMAKE_CXX_STANDARD 17) # 设置 C++ 标准为 C++17
set(CMAKE_CXX_STANDARD_REQUIRED ON) # 强制要求 C++17 标准

# 添加可执行文件。main.cpp 是你的主要源文件。
# httplib.h 是一个头文件，它会被 main.cpp 包含，不需要作为单独的编译单元添加到这里。
add_executable(my_cpp_web_server main.cpp)