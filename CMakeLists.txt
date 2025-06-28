cmake_minimum_required(VERSION 3.10)
project(my_cpp_web_server CXX) # 项目名称改为 my_cpp_web_server

set(CMAKE_CXX_STANDARD 17) # 设置 C++ 标准为 C++17
set(CMAKE_CXX_STANDARD_REQUIRED ON) # 强制要求 C++17 标准

# 只有一个 add_executable 行
add_executable(my_cpp_web_server main.cpp)

# 关键修改：链接到线程库，使用 pthread
target_link_libraries(my_cpp_web_server PRIVATE pthread)