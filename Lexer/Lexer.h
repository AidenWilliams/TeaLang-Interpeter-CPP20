//
// Created by Aiden Williams on 25/04/2021.
//

#ifndef TEALANG_COMPILER_CPP20_LEXER_H
#define TEALANG_COMPILER_CPP20_LEXER_H

#include <string>
#include <vector>
#include <regex>
#include <iostream>

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

    extern std::regex letter;
    extern std::regex digit;
    extern std::regex printable;

    bool isLetter(char c);
    bool isDigit(char c);
    bool isPrintable(char c);
    bool isFullstop(char c);
    bool isUnderscore(char c);
    bool isAsterisk(char c);
    bool isPlus(char c);
    bool isRelational(char c);
    bool isForwardSlash(char c);
    bool isBackSlash(char c);
    bool isPunctuation(char c);
    bool isQuatiationMark(char c);
    bool isNewline(char c);
    bool isExclamation(char c);

    class Lexer {

    private:
        std::vector<unsigned int> final_states = {1, 3, 6, 8, 9, 11, 14, 15, 16, 17, 18, 19, 21, 23, 24};
        std::vector<std::vector<unsigned int>> transition_table = {
            /* LETTER           */ {1},
            /* DIGIT            */ {1, 6, 8},
            /* PRINTABLE        */ {2, 10, 11, 12, 13},
            /* FULLSTOP         */ {7},
            /* UNDERSCORE       */ {1},
            /* ASTERISK         */ {18},
            /* PLUS             */ {19},
            /* RELATIONAL       */ {21},
            /* MINUS            */ {17},
            /* FORWARD_SLASH    */ {9, 10, 14},
            /* BACK_SLASH       */ {4},
            /* PUNCTUATION      */ {16},
            /* QUOTATION_MARK   */ {2, 3, 5},
            /* NEWLINE          */ {11, 12, 13},
            /* EQUALS           */ {23, 24},
            /* EXCLAMATION      */ {21},
            /* END              */ {15},
            /* INVALID          */ {}
            };
    };
};




#endif //TEALANG_COMPILER_CPP20_LEXER_H
