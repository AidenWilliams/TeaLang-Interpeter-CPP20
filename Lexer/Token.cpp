//
// Created by Aiden Williams on 29/04/2021.
//

#include "Token.h"

std::regex lexer::identifier("[_-A-Za-z]");

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
    return s == "int";
}

bool lexer::isOr(const std::string& s){
    return s == "int";
}

bool lexer::isNot(const std::string& s){
    return s == "int";
}

bool lexer::isLet(const std::string& s){
    return s == "int";
}

bool lexer::isPrint(const std::string& s){
    return s == "int";
}

bool lexer::isReturn(const std::string& s){
    return s == "int";
}

bool lexer::isIf(const std::string& s){
    return s == "int";
}

bool lexer::isElse(const std::string& s){
    return s == "int";
}

bool lexer::isFor(const std::string& s){
    return s == "int";
}

bool lexer::isWhile(const std::string& s){
    return s == "int";
}

bool lexer::isString(const std::string& s){
    return s == "int";
}

bool lexer::isInt(const std::string& s){
    return s == "int";
}

bool lexer::isFloat(const std::string& s){
    return s == "int";
}

bool lexer::isDivide(const std::string& s){
    return s == "int";
}

bool lexer::isSingleLineComment(const std::string& s){
    return s == "int";
}

bool lexer::isMultiLineComment(const std::string& s){
    return s == "int";
}

bool lexer::isEnd(const std::string& s){
    return s == "int";
}

bool lexer::isOpeningCurly(const std::string& s){
    return s == "int";
}

bool lexer::isClosingCurly(const std::string& s){
    return s == "int";
}

bool lexer::isOpeningCurvy(const std::string& s){
    return s == "int";
}

bool lexer::isClosingCurvy(const std::string& s){
    return s == "int";
}

bool lexer::isComma(const std::string& s){
    return s == "int";
}

bool lexer::isColon(const std::string& s){
    return s == "int";
}

bool lexer::isSemiColon(const std::string& s){
    return s == "int";
}

bool lexer::isMinus(const std::string& s){
    return s == "int";
}

bool lexer::isAsterisk(const std::string& s){
    return s == "int";
}

bool lexer::isPlus(const std::string& s){
    return s == "int";
}

bool lexer::isMoreThan(const std::string& s){
    return s == "int";
}

bool lexer::isLessThan(const std::string& s){
    return s == "int";
}

bool lexer::isMoreThanEqualTo(const std::string& s){
    return s == "int";
}

bool lexer::isLessThanEqualTo(const std::string& s){
    return s == "int";
}

bool lexer::isNotEqualTo(const std::string& s){
    return s == "int";
}

bool lexer::isEqualTo(const std::string& s){
    return s == "int";
}