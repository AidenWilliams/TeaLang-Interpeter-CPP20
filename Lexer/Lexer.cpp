#pragma clang diagnostic push
// ignores warning for declaring regex variables below
#pragma ide diagnostic ignored "cert-err58-cpp"
//
// Created by Aiden Williams on 25/04/2021.
//

#include "Lexer.h"

std::regex lexer::letter("[A-Za-z]");
std::regex lexer::digit("[0-9]");
std::regex lexer::printable("[\\x20-\\x7E]");

bool lexer::isLetter(char c){
    std::string _c;
    _c.push_back(c);
    return (std::regex_match(_c, letter));
}

bool lexer::isDigit(char c){
    std::string _c;
    _c.push_back(c);
    return (std::regex_match(_c, digit));
}

bool lexer::isPrintable(char c){
    std::string _c;
    _c.push_back(c);
    return (std::regex_match(_c, printable));
}
bool lexer::isFullstop(char c){
    return c == '.';
}

bool lexer::isUnderscore(char c){
    return c == '_';
}

bool lexer::isAsterisk(char c){
    return c == '*';
}

bool lexer::isPlus(char c){
    return c == '+';
}

bool lexer::isRelational(char c){
    return c == '<' || c ==  '>';
}

bool lexer::isMinus(char c){
    return c == '-';
}

bool lexer::isForwardSlash(char c){
    return c == '/';
}

bool lexer::isBackSlash(char c){
    return c == '\\';
}

bool lexer::isPunctuation(char c){
    return c == '{' || c ==  '}' || c ==  '(' || c ==  ')' || c ==  ',' || c ==  ':' || c ==  ';';
}
bool lexer::isQuatiationMark(char c){
    return c == '"';
}

bool lexer::isNewline(char c){
    return c == '\n';
}

bool lexer::isEquals(char c) {
    return c == '=';
}

bool lexer::isExclamation(char c){
    return c == '!';
}

bool lexer::isSpace(char c){
    return c == ' ';
}

lexer::Lexer::Lexer() = default;

lexer::Lexer::~Lexer() = default;


lexer::TRANSITION_TYPE lexer::Lexer::determineTransitionType(char c){
    if (isLetter(c)) return LETTER;
    if (isDigit(c)) return DIGIT;
    if (isPrintable(c)) return PRINTABLE;
    if (isFullstop(c)) return FULLSTOP;
    if (isUnderscore(c)) return UNDERSCORE;
    if (isAsterisk(c)) return ASTERISK;
    if (isPlus(c)) return PLUS;
    if (isRelational(c)) return RELATIONAL;
    if (isMinus(c)) return MINUS;
    if (isForwardSlash(c)) return FORWARD_SLASH;
    if (isBackSlash(c)) return BACK_SLASH;
    if (isPunctuation(c)) return PUNCTUATION;
    if (isQuatiationMark(c)) return QUOTATION_MARK;
    if (isNewline(c)) return NEWLINE;
    if (isEquals(c)) return EQUALS;
    if (isExclamation(c)) return EXCLAMATION;
    if (isExclamation(c)) return SPACE;
    return INVALID;
}

std::vector<lexer::TOKEN_TYPE> lexer::Lexer::extraxtLexemes(const std::string &text) {
    std::vector<TOKEN_TYPE> ret;
    std::string value;
    for (auto c : text){
        value += c;
        switch (determineTransitionType(c)) {


        }
    }
}

#pragma clang diagnostic pop