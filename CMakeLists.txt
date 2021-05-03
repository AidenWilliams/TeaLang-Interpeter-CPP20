cmake_minimum_required(VERSION 3.16)
project(TeaLang_Compiler_CPP20)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}-march=native")

set(SOURCES main.cpp Parser/Lexer/Lexer.cpp Parser/Lexer/Token.cpp)
set(HEADERS Parser/Lexer/Lexer.h Parser/Lexer/Token.h)

add_executable(TeaLang ${SOURCES} ${HEADERS})
