#include <iostream>
#include "Lexer/Lexer.h"
#include "Lexer/Token.h"
#include "Parser/Parser.h"
#include "Parser/AST.h"
#include "TestCases.h"

int main(int argc, char **argv) {
    if (std::string("-l") == argv[1]){
//        std::cout << "TESTING LEXER" << std::endl;
        lexer::Lexer lexer;
        lexer.extraxtLexemes(argv[2]);
        std::cout << "value: type" << std::endl;
        for (const auto& i: lexer.tokens){
            std::cout << i.value << " : " << i.type << std::endl;
        }
    }else if (std::string("-p") == argv[1]){
//        std::cout << "TESTING PARSER" << std::endl;
        lexer::Lexer lexer;
        lexer.extraxtLexemes(argv[2]);

        parser::Parser parser(lexer.tokens);
        parser::ASTProgramNode* programNode = parser.parseProgram();
    }

//    std::cout << "break" << std::endl;
    return 0;
}
