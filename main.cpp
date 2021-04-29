#include <iostream>
#include "Lexer/Lexer.h"
#include "Lexer/Token.h"


int main() {
    std::string x = "Monkey";
    std::cout << lexer::isIdentifier(x) << std::endl;
    return 0;
}