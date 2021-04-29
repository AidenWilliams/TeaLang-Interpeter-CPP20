#include <iostream>
#include "Lexer/Lexer.h"
#include "Lexer/Token.h"


int main() {
    std::string x = "\"12345 \nasdasd";
    std::cout << lexer::isString(x) << std::endl;

    return 0;
}