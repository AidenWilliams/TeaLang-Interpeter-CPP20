cmake_minimum_required(VERSION 3.16)
project(TeaLang_Compiler_CPP20)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}-march=native")

set(SOURCES main.cpp Lexer/Lexer.cpp Lexer/Token.cpp Parser/Parser.cpp Parser/Parser.h Parser/AST.cpp Parser/AST.h)
set(HEADERS Lexer/Lexer.h Lexer/Token.h Parser/Parser.cpp Parser/Parser.h Parser/AST.cpp Parser/AST.h)

add_executable(TeaLang ${SOURCES} ${HEADERS})
