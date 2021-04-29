#include <iostream>
#include "Lexer/Lexer.h"
#include "Lexer/Token.h"


int main() {
    std::string x = "12345";
    std::cout << lexer::isInt(x) << std::endl;

    return 0;
}