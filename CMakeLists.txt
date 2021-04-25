cmake_minimum_required(VERSION 3.16)
project(TeaLang_Compiler_CPP20)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}-march=native")

add_executable(TeaLang main.cpp)
