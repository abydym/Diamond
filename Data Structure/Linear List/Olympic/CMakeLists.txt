cmake_minimum_required(VERSION 3.29)
project(Homework_1)

set(CMAKE_CXX_STANDARD 20)
link_libraries(libeasyx.a libgdi32.a libole32.a)
add_executable(Homework_1 main.cpp)
