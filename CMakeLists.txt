cmake_minimum_required(VERSION 4.1)
project(lr1)

set(CMAKE_CXX_STANDARD 20)

add_executable(lr1 main.cpp)
add_executable(task1 src/lr1/task1.cpp)
add_executable(mainlr6 src/lr6/mainlr6.cpp src/lr6/stroka.cpp)
