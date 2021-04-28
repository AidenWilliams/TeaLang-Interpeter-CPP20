//
// Created by Aiden Williams on 25/04/2021.
//

#include "Lexer.h"


std::regex lexer::letter("[A-Za-z]");
std::regex digit("[0-9]");
std::regex printable("[\\x20-\\x7E]");

bool lexer::isLetter(const char c){
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

bool lexer::isExclamation(char c){
    return c == '!';
}