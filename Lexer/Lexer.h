//
// Created by aiden on 26/04/2021.
//

#ifndef TEALANG_COMPILER_CPP20_LEXER_H
#define TEALANG_COMPILER_CPP20_LEXER_H

namespace lexer {

    enum TRANSITION_TYPE {
        OTHER           =   0,
        DIGIT           =   1,
        LETTER          =   2,
        PLUS            =   3,
        EQUALS          =   4,
        NEWLINE         =   5,
        ENDOFFILE       =   6,
    };

    class Lexer {

    };
}

#endif //TEALANG_COMPILER_CPP20_LEXER_H
