cmake_minimum_required(VERSION 3.0)

project(main)
set(CMAKE_CXX_STANDARD 11)

add_executable(main main.hpp functions.cpp main.cpp)