cmake_minimum_required(VERSION 3.16)
project(TeaLang_Compiler_CPP20)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}-march=native")

set(Sources main.cpp Lexer/Lexer.cpp Lexer/Token.cpp)
set(Headers Lexer/Lexer.h Lexer/Token.h)

add_executable(TeaLang ${Sources} ${Headers})
