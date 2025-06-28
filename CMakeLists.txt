cmake_minimum_required(VERSION 3.10) # 保持这个版本要求
project(my_simple_cpp_app CXX) # 定义项目名称和语言

# 添加可执行文件，你的C++源文件是 main.cpp
add_executable(my_simple_cpp_app main.cpp)
add_executable(my_simple_cpp_app main.cpp httplib.h) # 添加 httplib.h 作为源文件
set_property(TARGET my_simple_cpp_app PROPERTY CXX_STANDARD 17) # 保持 C++17 标准

# 设置 C++ 标准（可选，但推荐）
set_property(TARGET my_simple_cpp_app PROPERTY CXX_STANDARD 17)
set_property(TARGET my_simple_cpp_app PROPERTY CXX_STANDARD_REQUIRED ON)