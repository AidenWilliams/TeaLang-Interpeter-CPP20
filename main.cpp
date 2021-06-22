#include <iostream>
#include "Lexer/Lexer.h"
#include "Lexer/Token.h"
#include "Parser/Parser.h"
#include "Parser/AST.h"


int main() {
    std::string comment =   "//this is a comment\n"
                            "/* multi line comment\n"
                            " * new line\n"
                            " * new line\n"
                            " */"
                            "let sean : string = \"inhobbok fuzzy;\";\n";
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
    lexer::Lexer lexer;
    lexer.extraxtLexemes(comment);
    std::cout << "value: type" << std::endl;
    for (const auto& i: lexer.tokens){
        std::cout << i.value << " : " << i.type << std::endl;
    }

    parser::Parser parser(lexer.tokens);
    parser::ASTProgramNode* programNode = parser.parseProgram();
//    std::cout << "break" << std::endl;
    return 0;
}
