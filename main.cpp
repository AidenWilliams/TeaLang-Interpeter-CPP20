#include <iostream>
#include "Lexer/Lexer.h"
#include "Lexer/Token.h"


int main() {
    std::string x = "\"12345 \nasdasd";
    unsigned int previous_state = 2, current_state = 0;
    bool check_printable = false;
    check_printable != (previous_state == 0 || previous_state == 1) ? current_state = 1 : current_state = current_state;
    std::cout << current_state << std::endl;
    std::cout << check_printable << std::endl;

    return 0;
}

/*

 */