//
// Created by aiden on 22/06/2021.
//

#ifndef TEALANG_COMPILER_CPP20_TESTCASES_H
#define TEALANG_COMPILER_CPP20_TESTCASES_H

std::string comment =   "//this is a comment\n"
                        "/* multi line comment\n"
                        " * new line\n"
                        " * new line\n"
                        " */\n"
                        "let sean : string = \"inhobbok fuzzy;\";";
std::string newlines = "let sean : string = \"inhobbok fuzzy;\";\n\n\n";
std::string y = "if (True) {\n"
                "let monkey : bool = - (10);\n"
                "}";
std::string z = "let monkey : bool = - (10);\nx = 10;\nprint monkey;\nlet monkey : bool = foo(1,2,3);";
std::string f = "for (; i < 10; ){\n"
                "   x = 10;\n"
                "}";
std::string w = "while (True) {\n"
                + z +
                "}";
std::string r = "return 10;";
std::string d = "int plus(x : int, y : int){\n"
                "   return x + y;\n"
                "}";
#endif //TEALANG_COMPILER_CPP20_TESTCASES_H
