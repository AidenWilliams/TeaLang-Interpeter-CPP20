#include <iostream>
#include "Lexer/Lexer.h"
#include "Lexer/Token.h"
#include "Parser/Parser.h"


int main() {
//    std::string x = "//this is a comment\n"
//                    "string sean = \"inhobbok fuzzy;\"\n"
//                    "int z = 10 * 2;";
    std::string declaration = "let monkey : bool = true;";
    lexer::Lexer lexer;
    lexer.extraxtLexemes(declaration);
    std::cout << "value: type" << std::endl;
    for (const auto& z: lexer.tokens){
        std::cout << z.value << " : " << z.type << std::endl;
    }
//    while (currentToken != lexer.tokens.end()){
//    std::vector<lexer::Token>::iterator currentToken = lexer.tokens.begin();
//        std::cout << (currentToken)->type << std::endl;
//        currentToken++;
//    }

//    auto currentToken = lexer.tokens.begin();
//    auto nextToken = currentToken + 1;
//    std::cout << (currentToken)->type << std::endl;
//    std::cout << (nextToken)->type << std::endl;

    parser::Parser parser(lexer.tokens);
    parser.parseProgram();
    return 0;
}
