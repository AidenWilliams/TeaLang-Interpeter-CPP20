//
// Created by aiden on 26/04/2021.
//


#ifndef TEALANG_COMPILER_CPP20_LEXER_H
#define TEALANG_COMPILER_CPP20_LEXER_H

#include <string>

namespace lexer {

    enum TRANSITION_TYPE {
        DIGIT = 0,
        PERIOD = 1,
        ADDITIVE_OP = 2,
        ASTERISK = 3,
        EXCL_MARK = 4,
        ORDER_REL = 5,
        EQUALS = 6,
        UNDERSCORE = 7,
        FORWARDSLASH = 8,
        BACKSLASH = 9,
        QUOTATION_MARK = 10,
        PUNCTUATION = 11,
        NEWLINE = 12,
        END = 13,
        LETTER = 14,
        PRINTABLE = 15,
        OTHER = 16
    };

    class Lexer {
    public:
        explicit Lexer();


    private:

    };
}

#endif //TEALANG_COMPILER_CPP20_LEXER_H
