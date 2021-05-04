//
// Created by Aiden Williams on 25/04/2021.
//

#ifndef TEALANG_COMPILER_CPP20_LEXER_H
#define TEALANG_COMPILER_CPP20_LEXER_H

#include <string>
#include <vector>
#include <regex>
#include <stdexcept>
#include "Token.h"


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
        INVALID         = 17,
        SPACE         = 18
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
    bool isMinus(char c);
    bool isForwardSlash(char c);
    bool isBackSlash(char c);
    bool isPunctuation(char c);
    bool isQuatiationMark(char c);
    bool isNewline(char c);
    bool isEquals(char c);
    bool isExclamation(char c);
    bool isSpace(char c);

    static TRANSITION_TYPE determineTransitionType(char c);
    unsigned int delta(unsigned int fromState, char c);

    class Lexer {
    public:
        std::vector<Token> tokens;
        std::vector<bool> finalStates = {
                                            false, true, false, true, false, false, true, false, true, true, false, true,
                                            false, false, true, true, true, true, true, true, false, true, true, true,
                                            true
                                        };
        Lexer() = default;
        ~Lexer() = default;

        std::vector<Token> extraxtLexemes(const std::string& text);

    };
};




#endif //TEALANG_COMPILER_CPP20_LEXER_H
