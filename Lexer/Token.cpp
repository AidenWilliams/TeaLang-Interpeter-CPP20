#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"
//
// Created by Aiden Williams on 29/04/2021.
//

#include "Token.h"

std::regex lexer::identifier("^[a-zA-Z_]*[a-zA-Z0-9_]*$");
std::regex lexer::intLiteral("^[0-9]*$");
std::regex lexer::floatLiteral("^[+-]?([0-9]+([.][0-9]*)?|[.][0-9]+)$");
std::regex lexer::singleLineComment(R"(^\/\/[^\n\r]+(?:[\n\r]|\*\))$)");
std::regex lexer::multiLineComment(R"(^/\\*[^*]*\\*+(?:[^/*][^*]*\\*+)*/$)");

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
    return s == "string";
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
#pragma clang diagnostic pop