#include <iostream>
#include "Lexer/Lexer.h"
#include "Lexer/Token.h"
#include "Parser/Parser.h"
#include "Parser/AST.h"
#include "TestCases.h"

int main() {
    lexer::Lexer lexer;
    lexer.extraxtLexemes(newlines);
    std::cout << "value: type" << std::endl;
    for (const auto& i: lexer.tokens){
        std::cout << i.value << " : " << i.type << std::endl;
    }

    parser::Parser parser(lexer.tokens);
    parser::ASTProgramNode* programNode = parser.parseProgram();
//    std::cout << "break" << std::endl;
    return 0;
}
