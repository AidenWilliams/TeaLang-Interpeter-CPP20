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

bool lexer::isSpaceState(unsigned int state) {
    return state == 2 || state == 10 || state ==  11 || state ==  12 || state ==  13;
}

lexer::Lexer::Lexer() = default;

lexer::Lexer::~Lexer() = default;


lexer::TRANSITION_TYPE lexer::Lexer::determineTransitionType(char c){
    if (isLetter(c)) return LETTER;
    if (isDigit(c)) return DIGIT;
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
    if (isSpace(c)) return SPACE;
    // lastly
    if (isPrintable(c)) return PRINTABLE;
    return INVALID;
}

std::vector<lexer::TOKEN_TYPE> lexer::Lexer::extraxtLexemes(const std::string &text) {
    std::vector<TOKEN_TYPE> ret;
    std::string value;
    unsigned int previous_state, current_state = 0;
    bool not_printable;
    for (auto c : text){
        value += c;
        previous_state = current_state;

        switch (determineTransitionType(c)) {
            case LETTER:
                (previous_state == 0 || previous_state == 1)
                ? current_state = 1 : current_state = 26;
                break;
            case DIGIT:
                if (previous_state == 1){
                    current_state = 1;
                }else if (previous_state == 0 || previous_state == 6){
                    current_state = 6;
                }else if (previous_state == 7 || previous_state == 8){
                    current_state = 8;
                }else{
                    current_state = 26;
                }
                break;
            case PRINTABLE:
                if (previous_state == 2 || previous_state == 4 || previous_state == 5){
                    if(!isBackSlash(c) and !isQuatiationMark(c)){
                        current_state = 2;
                    }else{
                        current_state = 26;
                    }
                }else if (previous_state == 10){
                    current_state = 11;
                }else if (previous_state == 13){
                    if(!isAsterisk(c)){
                        current_state = 13;
                    }else{
                        current_state = 26;
                    }
                }else if (previous_state == 14){
                    if(!isAsterisk(c) and !isForwardSlash(c)){
                        current_state = 13;
                    }else{
                        current_state = 26;
                    }
                }else{
                    current_state = 26;
                }
                break;
            case FULLSTOP:
                (previous_state == 6)
                ? current_state = 7 : current_state = 26;
                break;
            case UNDERSCORE:
                (previous_state == 0 || previous_state == 1)
                ? current_state = 1 : current_state = 26;
                break;
            case ASTERISK:
                if (previous_state == 0){
                    current_state = 19;
                }else if (previous_state == 9){
                    current_state = 13;
                }else if (previous_state == 13){
                    current_state = 14;
                }else if (previous_state == 14){
                    current_state = 14;
                }else{
                    current_state = 26;
                }
                break;
            case PLUS:
                (previous_state == 0)
                ? current_state = 20 : current_state = 26;
                break;
            case RELATIONAL:
                (previous_state == 0)
                ? current_state = 22 : current_state = 26;
                break;
            case MINUS:
                (previous_state == 0)
                ? current_state = 18 : current_state = 26;
                break;
            case FORWARD_SLASH:
                if (previous_state == 0){
                    current_state = 9;
                }else if (previous_state == 9){
                    current_state = 10;
                }else if (previous_state == 14){
                    current_state = 15;
                }else{
                    current_state = 26;
                }
                break;
            case BACK_SLASH:
                (previous_state == 2 || previous_state == 4 || previous_state == 5)
                ?    current_state = 4 :     current_state = 26;
                break;
            case PUNCTUATION:
                (previous_state == 0)
                ?    current_state = 17 :     current_state = 26;
                break;
            case QUOTATION_MARK:
                if (previous_state == 0){
                    current_state = 2;
                }else if (previous_state == 2){
                    current_state = 3;
                }else if (previous_state == 4){
                    current_state = 5;
                }else if (previous_state == 5){
                    current_state = 3;
                }else{
                    current_state = 26;
                }
                break;
            case NEWLINE:
            case EQUALS:
            case EXCLAMATION:
            case SPACE:
            case END:
                break;
            case INVALID:
                break;
        }

    }
}

#pragma clang diagnostic pop