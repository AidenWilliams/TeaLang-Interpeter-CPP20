#include <iostream>
#include "Lexer/Lexer.h"
#include "Lexer/Token.h"


int main() {
    std::string x = "//this is a comment\n"
                    "string sean = \"inhobbok fuzzy\";\n"
                    "int z = 10 * 2;";
    lexer::Lexer lexer;
    std::vector<lexer::Token> y = lexer.extraxtLexemes(x);
    std::cout << "value: type" << std::endl;
    for (const auto& z: y){
        std::cout << z.value << " : " << z.type << std::endl;
    }
    return 0;
}
