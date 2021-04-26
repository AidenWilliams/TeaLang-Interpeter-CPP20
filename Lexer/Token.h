//
// Created by aiden on 26/04/2021.
//

#ifndef TEALANG_COMPILER_CPP20_TOKEN_H
#define TEALANG_COMPILER_CPP20_TOKEN_H

#include <string>

namespace lexer {
    enum TOKEN {
        INT,
        REAL,
        ADDITIVE_OP,
        MULTIPLICATIVE_OP,
        RELATIONAL_OP,
        EQUALS,
        VAR,
        SET,
        DEF,
        RETURN,
        IF,
        ELSE,
        WHILE,
        PRINT,
        INT_TYPE,
        REAL_TYPE,
        BOOL_TYPE,
        STRING_TYPE,
        BOOL,
        NOT,
        IDENTIFIER,
        COMMENT,
        STRING,
        LEFT_CURLY,
        RIGHT_CURLY,
        LEFT_BRACKET,
        RIGHT_BRACKET,
        COMMA,
        SEMICOLON,
        COLON,
        END,
        ERROR
    }

    class Token {

    public:


    private:
    };
}


#endif //TEALANG_COMPILER_CPP20_TOKEN_H
