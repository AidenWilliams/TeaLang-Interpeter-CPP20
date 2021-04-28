//
// Created by Aiden Williams on 25/04/2021.
//

#ifndef TEALANG_COMPILER_CPP20_LEXER_H
#define TEALANG_COMPILER_CPP20_LEXER_H

#include <string>
#include <vector>

namespace lexer {

    enum TRANSITION_TYPE {
        // [A-Za-z]
        LETTER          =  0,
        // [0-9]
        DIGIT           =  1,
        // [\x20-\x7E]
        PRINTABLE       =  2,
        // '.'
        FULLSTOP        =  3,
        // '_'
        UNDERSCORE      =  4,
        // ‘*’
        ASTERISK        =  5,
        // ‘+’
        PLUS            =  6,
        // ‘<’ | ‘>’
        RELATIONAL      =  7,
        // ‘-’
        MINUS           =  8,
        // ‘/’
        FORWARD_SLASH   =  9,
        // ‘\’
        BACK_SLASH      =  10,
        // '{' | '}' | '(' | ')' | ',' | ':' | ';'
        PUNCTUATION     = 11,
        // '"'
        QUOTATION_MARK  = 12,
        // '\n'
        NEWLINE         = 13,
        // '='
        EQUALS          = 14,
        // '!'
        EXCLAMATION     = 15,
        END             = 16,
        INVALID         = 17
    };


    class Lexer {

    private:

        std::vector<std::vector<TRANSITION_TYPE>> transition_table = {
            /* LETTER           */ {},
            /* DIGIT            */ {},
            /* PRINTABLE        */ {},
            /* FULLSTOP         */ {},
            /* UNDERSCORE       */ {},
            /* ASTERISK         */ {},
            /* PLUS             */ {},
            /* RELATIONAL       */ {},
            /* MINUS            */ {},
            /* FORWARD_SLASH    */ {},
            /* BACK_SLASH       */ {},
            /* PUNCTUATION      */ {},
            /* QUOTATION_MARK   */ {},
            /* NEWLINE          */ {},
            /* EQUALS           */ {},
            /* EXCLAMATION      */ {},
            /* END              */ {},
            /* INVALID          */ {}
            };
    };
};




#endif //TEALANG_COMPILER_CPP20_LEXER_H
