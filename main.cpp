#include <iostream>
#include "Lexer/Lexer.h"


int main() {
    char x = 'c';
    std::cout << lexer::isLetter(x) << std::endl;
    return 0;
}