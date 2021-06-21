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

bool lexer::isClosingCurly(char c){
    return c == '}';
}

lexer::TRANSITION_TYPE lexer::determineTransitionType(char c){
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
    if (isClosingCurly(c)) return CLOSING_CURLY;
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

unsigned int lexer::delta(unsigned int fromState, char c){
    unsigned int current_state;
    switch (lexer::determineTransitionType(c)) {
        case LETTER:
            (fromState == 0 || fromState == 1)
            ? current_state = 1 : current_state = 24;
            break;
        case DIGIT:
            if (fromState == 1){
                current_state = 1;
            }else if (fromState == 0 || fromState == 6){
                current_state = 6;
            }else if (fromState == 7 || fromState == 8){
                current_state = 8;
            }else{
                current_state = 24;
            }
            break;
        case PRINTABLE:
            if (fromState == 2 || fromState == 4 || fromState == 5){
                if(!isBackSlash(c) and !isQuatiationMark(c)){
                    current_state = 2;
                }else{
                    current_state = 24;
                }
            }else if (fromState == 10){
                current_state = 10;
            }else if (fromState == 12){
                if(!isAsterisk(c)){
                    current_state = 12;
                }else{
                    current_state = 24;
                }
            }else if (fromState == 13){
                if(!isAsterisk(c) and !isForwardSlash(c)){
                    current_state = 12;
                }else{
                    current_state = 24;
                }
            }else{
                current_state = 24;
            }
            break;
        case FULLSTOP:
            (fromState == 6)
            ? current_state = 7 : current_state = 24;
            break;
        case UNDERSCORE:
            (fromState == 0 || fromState == 1)
            ? current_state = 1 : current_state = 24;
            break;
        case ASTERISK:
            if (fromState == 0){
                current_state = 18;
            }else if (fromState == 9){
                current_state = 12;
            }else if (fromState == 12){
                current_state = 13;
            }else{
                current_state = 24;
            }
            break;
        case PLUS:
            (fromState == 0)
            ? current_state = 19 : current_state = 24;
            break;
        case RELATIONAL:
            (fromState == 0)
            ? current_state = 21 : current_state = 24;
            break;
        case MINUS:
            (fromState == 0)
            ? current_state = 17 : current_state = 24;
            break;
        case FORWARD_SLASH:
            if (fromState == 0){
                current_state = 9;
            }else if (fromState == 9){
                current_state = 10;
            }else if (fromState == 13){
                current_state = 14;
            }else{
                current_state = 24;
            }
            break;
        case BACK_SLASH:
            (fromState == 2 || fromState == 4 || fromState == 5)
            ?    current_state = 4 : current_state = 24;
            break;
        case CLOSING_CURLY:
            (fromState == 0)
            ?    current_state = 25 : current_state = 24;
            break;
        case PUNCTUATION:
            (fromState == 0)
            ?    current_state = 16 : current_state = 24;
            break;
        case QUOTATION_MARK:
            if (fromState == 0){
                current_state = 2;
            }else if (fromState == 2 || fromState == 5){
                current_state = 3;
            }else if (fromState == 4){
                current_state = 5;
            }else{
                current_state = 24;
            }
            break;
        case NEWLINE:
            if (fromState == 10){
                current_state = 11;
            }else if (fromState == 12){
                current_state = 12;
            }else if (fromState == 13){
                current_state = 13;
            }else{
                current_state = 24;
            }
            break;
        case EQUALS:
            if (fromState == 0){
                current_state = 22;
            }else if (fromState == 22 || fromState == 21 || fromState == 20){
                current_state = 23;
            }else{
                current_state = 24;
            }
            break;
        case EXCLAMATION:
            (fromState == 0)
            ?    current_state = 20 : current_state = 24;
            break;
        case END:
            current_state = 15;
            break;
        case SPACE:
        case INVALID:
            current_state = 24;
    }
    // Check for printable again
    if (current_state == 24){
        if (fromState == 2 || fromState == 4 || fromState == 5){
            if(!isBackSlash(c) and !isQuatiationMark(c)){
                current_state = 2;
            }else{
                current_state = 24;
            }
        }else if (fromState == 10){
            current_state = 10;
        }else if (fromState == 12){
            if(!isAsterisk(c)){
                current_state = 12;
            }else{
                current_state = 24;
            }
        }else if (fromState == 13){
            if(!isAsterisk(c) and !isForwardSlash(c)){
                current_state = 12;
            }else{
                current_state = 24;
            }
        }else{
            current_state = 24;
        }
    }
    return current_state;
}

std::vector<lexer::Token> lexer::Lexer::extraxtLexemes(const std::string &text) {
    std::vector<Token> ret;
    std::string value;
    unsigned int previous_state, current_state = 0;
    unsigned int lineNumber = 1;

    for (auto c : text){
        previous_state = current_state;

        current_state = delta(previous_state, c);

        if (current_state == 24){

            if(!finalStates[previous_state]) throw std::runtime_error("Lexical error on line " + std::to_string(lineNumber) + ".");

            Token t(value, previous_state, lineNumber);
            ret.emplace_back(t);
            //reset
            current_state = delta(0, c);
            value = "";
            if (current_state == 24) current_state = 0;
            else value += c;
        }else{
            value += c;
        }

        if(isNewline(c)) lineNumber++;
    }
    // end
    if(!finalStates[current_state]) throw std::runtime_error("Lexical error on line " + std::to_string(lineNumber) + ".");
    ret.emplace_back(Token(value, current_state, lineNumber));
    ret.emplace_back(Token("", 15, lineNumber));
    tokens = ret;
    return ret;
}

#pragma clang diagnostic pop