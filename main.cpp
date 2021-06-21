#include <iostream>
#include "Lexer/Lexer.h"
#include "Lexer/Token.h"
#include "Parser/Parser.h"
#include "Parser/AST.h"


int main() {
    std::string x = "//this is a comment\n"
                    "string sean = \"inhobbok fuzzy;\"\n"
                    "int z = 10 * 2;";
    std::string y = "if (True) {\n"
                              "let monkey : bool = - (10);\n"
                              "}";
    std::string z = "let monkey : bool = - (10);\nx = 10;\nprint monkey;"; //let monkey : bool = foo(1,2,3);
    std::string f = "for (let i : int = 0; i < 10; i++){\n"
                    "   x = 10;\n"
                    "}";
    lexer::Lexer lexer;
    lexer.extraxtLexemes(f);
    std::cout << "value: type" << std::endl;
    for (const auto& i: lexer.tokens){
        std::cout << i.value << " : " << i.type << std::endl;
    }

    parser::Parser parser(lexer.tokens);
    parser::ASTProgramNode* programNode = parser.parseProgram();
//    std::cout << "break" << std::endl;
    return 0;
}
