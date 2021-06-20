#include <iostream>
#include "Lexer/Lexer.h"
#include "Lexer/Token.h"
#include "Parser/Parser.h"
#include "Parser/AST.h"


int main() {
//    std::string x = "//this is a comment\n"
//                    "string sean = \"inhobbok fuzzy;\"\n"
//                    "int z = 10 * 2;";
    std::string declaration = "let monkey : bool = foo(1,2,3);";
    lexer::Lexer lexer;
    lexer.extraxtLexemes(declaration);
    std::cout << "value: type" << std::endl;
    for (const auto& z: lexer.tokens){
        std::cout << z.value << " : " << z.type << std::endl;
    }

    parser::Parser parser(lexer.tokens);
    parser::ASTProgramNode* programNode = parser.parseProgram();
    return 0;
}
