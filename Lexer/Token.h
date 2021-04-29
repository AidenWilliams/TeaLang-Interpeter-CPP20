//
// Created by Aiden Williams on 29/04/2021.
//

#ifndef TEALANG_COMPILER_CPP20_TOKEN_H
#define TEALANG_COMPILER_CPP20_TOKEN_H


namespace lexer {
    // Defined according to pdf and state
    enum TOKEN_TYPE {
        // State 1
        // float
        FLOAT_TYPE          =  0,
        // int
        INT_TYPE            =  1,
        // bool
        BOOL_TYPE           =  2,
        //  string
        STRING_TYPE         =  3,
        // true
        TRUE                =  4,
        // false
        FALSE               =  5,
        // variable1 | _name
        IDENTIFIER          =  6,
        // and
        AND                 =  7,
        // or
        OR                  =  8,
        // not
        NOT                 =  9,
        // let
        LET                 =  10,
        // print
        PRINT               = 11,
        // return
        RETURN              =  12,
        // if
        IF                  =  13,
        // else
        ELSE                = 14,
        // for
        FOR                 = 15,
        // while
        WHILE               = 16,
        // State 3
        // "Printable"
        STRING              = 17,
        // State 6
        // 10, 12, 1
        INT                 = 18,
        // State 8
        // 10.12, 1.1
        FLOAT               = 19,
        // State 9
        // /
        DIVIDE              = 20,
        // State 11
        // //
        SINGLE_LINE_COMMENT = 21,
        // State 14
        // /* */
        MULTI_LINE_COMMENT  = 22,
        // State 15
        // EOF
        END                 = 23,
        // State 16
        // '{' | '}' | '(' | ')' | ',' | ':' | ';'
        // {
        OPENING_CURLY       = 24,
        // }
        CLOSING_CURLY       = 25,
        // (
        OPENING_CURVY       = 26,
        // )
        CLOSING_CURVY       = 27,
        // ,
        COMMA               = 28,
        // :
        COLON               = 29,
        // ;
        SEMICOLON           = 30,
        // State 17
        // -
        MINUS               = 31,
        // State 18
        // *
        ASTERISK            = 31,
        // State 19
        // +
        PLUS                = 32,
        // State 21
        // >
        MORE_THAN           = 33,
        // <
        LESS_THAN           = 34,
        // State 23
        // =
        EQUALS              = 35,
        // State 24
        // >=
        MORE_THAN_EQUAL_TO  = 36,
        // <=
        LESS_THAN_EQUAL_TO  = 37,
        // !=
        NOT_EQAUL_TO        = 38,
        // ==
        EQAUL_TO            = 39,
    };

    class Token {

    };
}


#endif //TEALANG_COMPILER_CPP20_TOKEN_H
