//
// Created by aiden on 26/04/2021.
//


#ifndef TEALANG_COMPILER_CPP20_LEXER_H
#define TEALANG_COMPILER_CPP20_LEXER_H

#include <string>

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
    public:
//        explicit Lexer(){
//            epsilon = -1;
//
//
//
//        };


    private:
        int epsilon;
        unsigned int len_states = 7;
        const bool is_final[7];


    };
}

#endif //TEALANG_COMPILER_CPP20_LEXER_H
