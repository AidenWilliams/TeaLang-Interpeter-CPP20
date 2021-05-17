//
// Created by Aiden Williams on 03/05/2021.
//

#include "Parser.h"


void parser::Parser::moveTokenWindow(int step){
    currentToken += step;
    nextToken += step;
}