#include <iostream>
#include "Lexer/Lexer.h"
#include "Lexer/Token.h"


int main() {
    std::string x = "//this is a comment\n";
    lexer::Lexer lex;
    std::vector<lexer::Token> y = lex.extraxtLexemes(x);
    std::cout << "value: type" << std::endl;
    for (const auto& z: y){
        std::cout << z.value << " : " << z.type << std::endl;
    }
    return 0;
}
