#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"
//
// Created by Aiden Williams on 29/04/2021.
//

#include "Token.h"

std::regex lexer::identifier("^[a-zA-Z_]*[a-zA-Z0-9_]*$");
std::regex lexer::string(R"(\"(\\.|[^"\\])*\")");
std::regex lexer::intLiteral("^[0-9]*$");
std::regex lexer::floatLiteral("^[+-]?([0-9]+([.][0-9]*)?|[.][0-9]+)$");
std::regex lexer::singleLineComment(R"(^\/\/[^\n\r]+(?:[\n\r]|\*\))$)");
std::regex lexer::multiLineComment(R"(\/\*(\*(?!\/)|[^*])*\*\/$)");

bool lexer::isFloatType(const std::string& s){
    return s == "float";
}

bool lexer::isIntType(const std::string& s){
    return s == "int";
}

bool lexer::isBoolType(const std::string& s){
    return s == "bool";
}

bool lexer::isStringType(const std::string& s){
    return s == "string";
}

bool lexer::isTrue(const std::string& s){
    return s == "true";
}

bool lexer::isFalse(const std::string& s){
    return s == "false";
}

bool lexer::isIdentifier(const std::string& s){
    return (std::regex_match(s, identifier));
}

bool lexer::isAnd(const std::string& s){
    return s == "and";
}

bool lexer::isOr(const std::string& s){
    return s == "or";
}

bool lexer::isNot(const std::string& s){
    return s == "not";
}

bool lexer::isLet(const std::string& s){
    return s == "let";
}

bool lexer::isPrint(const std::string& s){
    return s == "print";
}

bool lexer::isReturn(const std::string& s){
    return s == "return";
}

bool lexer::isIf(const std::string& s){
    return s == "if";
}

bool lexer::isElse(const std::string& s){
    return s == "else";
}

bool lexer::isFor(const std::string& s){
    return s == "for";
}

bool lexer::isWhile(const std::string& s){
    return s == "while";
}

bool lexer::isString(const std::string& s){
    return (std::regex_match(s, string));
}

bool lexer::isInt(const std::string& s) {
    return (std::regex_match(s, intLiteral));
}

bool lexer::isFloat(const std::string& s){
    return (std::regex_match(s, floatLiteral));
}

bool lexer::isDivide(const std::string& s){
    return s == "/";
}

bool lexer::isSingleLineComment(const std::string& s){
    return (std::regex_match(s, singleLineComment));
}

bool lexer::isMultiLineComment(const std::string& s){
    return (std::regex_match(s, multiLineComment));
}

bool lexer::isEnd(const std::string& s){
    return s.empty();
}

bool lexer::isOpeningCurly(const std::string& s){
    return s == "{";
}

bool lexer::isClosingCurly(const std::string& s){
    return s == "}";
}

bool lexer::isOpeningCurvy(const std::string& s){
    return s == "(";
}

bool lexer::isClosingCurvy(const std::string& s){
    return s == ")";
}

bool lexer::isComma(const std::string& s){
    return s == ",";
}

bool lexer::isColon(const std::string& s){
    return s == ":";
}

bool lexer::isSemiColon(const std::string& s){
    return s == ";";
}

bool lexer::isMinus(const std::string& s){
    return s == "-";
}

bool lexer::isAsterisk(const std::string& s){
    return s == "*";
}

bool lexer::isPlus(const std::string& s){
    return s == "+";
}

bool lexer::isMoreThan(const std::string& s){
    return s == ">";
}

bool lexer::isLessThan(const std::string& s){
    return s == "<";
}

bool lexer::isEquals(const std::string& s){
    return s == "=";
}

bool lexer::isMoreThanEqualTo(const std::string& s){
    return s == ">=";
}

bool lexer::isLessThanEqualTo(const std::string& s){
    return s == "<=";
}

bool lexer::isNotEqualTo(const std::string& s){
    return s == "!=";
}

bool lexer::isEqualTo(const std::string& s){
    return s == "==";
}

lexer::TOKEN_TYPE lexer::fromState1(const std::string& s){
    // Keywords
    if (isFloatType(s)) return TOK_FLOAT_TYPE;
    if (isIntType(s)) return TOK_INT_TYPE;
    if (isBoolType(s)) return TOK_BOOL_TYPE;
    if (isStringType(s)) return TOK_STRING_TYPE;
    if (isTrue(s)) return TOK_TRUE;
    if (isFalse(s)) return TOK_FALSE;
    if (isAnd(s)) return TOK_AND;
    if (isOr(s)) return TOK_OR;
    if (isNot(s)) return TOK_NOT;
    if (isLet(s)) return TOK_LET;
    if (isPrint(s)) return TOK_PRINT;
    if (isReturn(s)) return TOK_RETURN;
    if (isIf(s)) return TOK_IF;
    if (isElse(s)) return TOK_ELSE;
    if (isFor(s)) return TOK_FOR;
    if (isWhile(s)) return TOK_WHILE;
    // Identifier
    if (isIdentifier(s)) return TOK_IDENTIFIER;
    return TOK_INVALID;
}

lexer::TOKEN_TYPE lexer::fromState3(const std::string& s){
    // String
    if (isString(s)) return TOK_STRING;
    return TOK_INVALID;
}

lexer::TOKEN_TYPE lexer::fromState6(const std::string& s){
    // Integer
    if (isInt(s)) return TOK_INT;
    return TOK_INVALID;
}

lexer::TOKEN_TYPE lexer::fromState8(const std::string& s){
    // Float
    if (isFloat(s)) return TOK_FLOAT;
    return TOK_INVALID;
}

lexer::TOKEN_TYPE lexer::fromState9(const std::string& s){
    // Divide
    if (isDivide(s)) return TOK_DIVIDE;
    return TOK_INVALID;
}

lexer::TOKEN_TYPE lexer::fromState11(const std::string& s){
    // Single Line Comment
    if (isSingleLineComment(s)) return TOK_SINGLE_LINE_COMMENT;
    return TOK_INVALID;
}
lexer::TOKEN_TYPE lexer::fromState14(const std::string& s){
    // Multi Line Comment
    if (isMultiLineComment(s)) return TOK_MULTI_LINE_COMMENT;
    return TOK_INVALID;
}

lexer::TOKEN_TYPE lexer::fromState15(const std::string& s){
    // EOF
    if (isEnd(s)) return TOK_END;
    return TOK_INVALID;
}

lexer::TOKEN_TYPE lexer::fromState16(const std::string& s){
    // Punctuation
    if (isOpeningCurly(s)) return TOK_OPENING_CURLY;
    if (isClosingCurly(s)) return TOK_CLOSING_CURLY;
    if (isOpeningCurvy(s)) return TOK_OPENING_CURVY;
    if (isClosingCurvy(s)) return TOK_CLOSING_CURVY;
    if (isComma(s)) return TOK_COMMA;
    if (isColon(s)) return TOK_COLON;
    if (isSemiColon(s)) return TOK_SEMICOLON;
    return TOK_INVALID;
}

lexer::TOKEN_TYPE lexer::fromState17(const std::string& s){
    // Minus
    if (isMinus(s)) return TOK_MINUS;
    return TOK_INVALID;
}

lexer::TOKEN_TYPE lexer::fromState18(const std::string& s){
    // Asterisk
    if (isAsterisk(s)) return TOK_ASTERISK;
    return TOK_INVALID;
}

lexer::TOKEN_TYPE lexer::fromState19(const std::string& s){
    // Plus
    if (isPlus(s)) return TOK_PLUS;
    return TOK_INVALID;
}

lexer::TOKEN_TYPE lexer::fromState21(const std::string& s){
    // More Than
    if (isMoreThan(s)) return TOK_MORE_THAN;
    // Less Than
    if (isLessThan(s)) return TOK_LESS_THAN;
    return TOK_INVALID;
}

lexer::TOKEN_TYPE lexer::fromState22(const std::string& s){
    // Equals
    if (isEquals(s)) return TOK_EQUALS;
    return TOK_INVALID;
}

lexer::TOKEN_TYPE lexer::fromState23(const std::string& s){
    // More Than or Equal To
    if (isMoreThanEqualTo(s)) return TOK_MORE_THAN_EQUAL_TO;
    // Less Than or Equal To
    if (isLessThanEqualTo(s)) return TOK_LESS_THAN_EQUAL_TO;
    // Not Equal To
    if (isNotEqualTo(s)) return TOK_NOT_EQAUL_TO;
    // Equal To
    if (isEqualTo(s)) return TOK_EQAUL_TO;
    return TOK_INVALID;
}

lexer::TOKEN_TYPE lexer::fromState25(const std::string& s){
    // Can only be Closing Curly
    if (isClosingCurly(s)) return TOK_CLOSING_CURLY;
    return TOK_INVALID;
}

lexer::TOKEN_TYPE lexer::Token::determineTokenType(std::string& s, unsigned int state){
    switch (state) {
        case 1:
            return fromState1(s);
        case 3:
            return fromState3(s);
        case 6:
            return fromState6(s);
        case 8:
            return fromState8(s);
        case 9:
            return fromState9(s);
        case 11:
            return fromState11(s);
        case 14:
            return fromState14(s);
        case 15:
            return fromState15(s);
        case 16:
            return fromState16(s);
        case 17:
            return fromState17(s);
        case 18:
            return fromState18(s);
        case 19:
            return fromState19(s);
        case 21:
            return fromState21(s);
        case 22:
            return fromState22(s);
        case 23:
            return fromState23(s);
        case 25:
            return fromState25(s);
        default:
            return TOK_INVALID;
    }
}


#pragma clang diagnostic pop